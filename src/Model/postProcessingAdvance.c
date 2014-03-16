#include <stdio.h>
#include <stdlib.h>
#include "utstring.h"
#include "utarray.h"
#include "ModelStructure.h"

void CharProfile_free(void * profile_in){
	CharProfile * profile = (CharProfile *) profile_in;
	utarray_free(profile->CharChoices);
}

UT_array * postProcessingInitializeDictionary();
UT_array * postProcessingInitializeSpecialChar();
void postProcessingCleanUP(UT_array * , UT_array * );
UT_array * getThreeKeyword(CharProfile *, UT_array *, UT_array *);
UT_string * postProcessing(UT_array *, UT_array *, UT_array *);
char * getTopProb(CharProfile *);
char * getSecondProb(CharProfile *);
UT_string * wordCompare(UT_array *, UT_array *);
int compareChar(UT_string *, UT_array *);




UT_string * postProcessing(UT_array * charList, UT_array * dictionary, UT_array * specialCharacter)
{
  CharProfile * currCharProfile = NULL;
  CharProbability * currCharProbability = NULL;
  char chosen = 'a';
  char quotation = 'a';
  
  int isSpecialChar = 0;
  
  UT_array * wordBank;
  UT_string *temp;
  UT_string *temp2;
  UT_string *output;
  
  utstring_new(output);

  currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile);
  while(currCharProfile)
  {
    currCharProbability = NULL;
    utarray_new(wordBank, &ut_str_icd);
    wordBank = getThreeKeyword(currCharProfile, charList, specialCharacter);
    isSpecialChar = 0;
    /* highest posibility isn't a special character */
    while ((isSpecialChar == 0) && currCharProfile)
    {
      utstring_new(temp);
      currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability);
      chosen = currCharProbability->Char;
      utstring_printf(temp, "%c", chosen);
      isSpecialChar = compareChar(temp, specialCharacter);
      /*if (isSpecialChar)
      {
	(currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile));
      }*/
      (currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile));
    }
    utstring_concat(output, wordCompare(wordBank, dictionary));
    if (isSpecialChar == 1)
    {
      if (chosen == '\'')
      {
	if (currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile))
	{
	  currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability);
	  utstring_new(temp2);
	  quotation = currCharProbability->Char;
	  utstring_printf(temp2, "%c", quotation);
	  if (quotation == '\'')
	  {
	    chosen = '"';
	    utstring_new(temp);
	    utstring_printf(temp, "%c", chosen);
	  }
	  else
	  {
	    utstring_concat(temp, temp2);
	  }
	  utstring_concat(output, temp);
	  
	}
      }
      else
      {
	utstring_new(temp);
	utstring_printf(temp, "%c", chosen);
	utstring_concat(output, temp);
      }
    }
  }
  /*printf("output is: %s\n", utstring_body(output));*/
  
  return temp;
}


UT_array * getThreeKeyword(CharProfile *currCharProfile, UT_array * charList, UT_array * specialCharacter)
{
  char * top;
  char * top2;
  char * second;
  CharProfile * tempPosition = currCharProfile;
  CharProfile * tempPosition2 = currCharProfile;
  char chosen;
  char chosen2;
  UT_string *temp;
  UT_string *temp2;
  UT_string *output;

  UT_array * wordBank;
  utarray_new(wordBank, &ut_str_icd);

  int i, j;
  int wordLength = 8;
  int wordLengthFlag = 0;
  int specialCharFlag = 0;
  

  /* doesn't grab the highest probability.... */
  for (i = 0; i < wordLength; i++)
  {
    utstring_new(output);
    top = getTopProb(currCharProfile);
    second = getSecondProb(currCharProfile);
    tempPosition = currCharProfile;
    j = 0;
    while (tempPosition && j < 8)
    {
      if (j > 0)
      {
	tempPosition = (CharProfile *)utarray_next(charList, tempPosition);
	if (tempPosition)
	{
	  top = getTopProb(tempPosition);
	  second = getSecondProb(tempPosition);
	}
      }
      if (j == i)
      {
	chosen = *second;
      }
      else
      {
	chosen = *top;
      }
      utstring_new(temp);
      utstring_printf(temp, "%c", chosen);
      specialCharFlag = compareChar(temp, specialCharacter);
      
      if (specialCharFlag == 0)
      {
	utstring_concat(output,temp);
      }
      else
      {
	break;
      }
      j++;
    }
    if (wordLengthFlag == 0)
    {
      wordLength = j;
      wordLengthFlag = 1;
    }
    utarray_push_back(wordBank, &utstring_body(output));
  }
  
  
  /* grabbing highest prob */
  utstring_new(output);
  i = 0;
  while (i < wordLength && tempPosition2)
  {
    utstring_new(temp2);
    top2 = getTopProb(tempPosition2);
    chosen2 = *top2;
    tempPosition2 = (CharProfile *)utarray_next(charList, tempPosition2);
    utstring_printf(temp2, "%c", chosen2);
    utstring_concat(output, temp2);
    i++;
  } 
  utarray_push_back(wordBank, &utstring_body(output));
  currCharProfile = tempPosition;
  
  return wordBank;
}

char * getTopProb(CharProfile * currCharProfile)
{
  CharProbability * currCharProbability = NULL;
  currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability);
  return &currCharProbability->Char;
}
char * getSecondProb(CharProfile * currCharProfile)
{
	CharProbability * currCharProbability = NULL;
	currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability);
	currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability);
	return &currCharProbability->Char;
}

int compareChar(UT_string *chosen, UT_array * specialCharacter)
{
  char ** specialChar = NULL;
  int i;
  
  UT_string * temp;
  
  for (i = 0; i < 32; i++)
  {
    specialChar = (char **)utarray_next(specialCharacter, specialChar);
    utstring_new(temp);
    utstring_printf(temp, "%c", *(*specialChar));
    
    if (strcmp(utstring_body(temp), utstring_body(chosen)) == 0)
    {
      return 1;
    }
  }
  return 0;
  
}

UT_string *wordCompare(UT_array * wordBank, UT_array * dictionary)
{
  char ** tempWord1 = NULL;
  char ** tempWord2 = NULL;
  
  int i;
  
  UT_string *temp1;
  UT_string *temp2;
  
  while((tempWord1 = (char**)utarray_next(wordBank, tempWord1)))
  {
    utstring_new(temp1);
    utstring_printf(temp1, "%s", (*tempWord1));
    tempWord2 = NULL;
    //printf("check please: %s\n", utstring_body(temp1));
    for (i = 0; i < 32; i++)
    {
      tempWord2 = (char **)utarray_next(dictionary, tempWord2);
      utstring_new(temp2);
      utstring_printf(temp2, "%s", (*tempWord2));
      
      if (strcmp(utstring_body(temp1), utstring_body(temp2)) == 0)
      {
	return temp1;
      }
    }
  }
  tempWord1 = NULL;
  while (tempWord1 = (char**)utarray_next(wordBank,tempWord1))
  {
    utstring_new(temp1);
    utstring_printf(temp1, "%s", (*tempWord1)); 
  }
  
  return temp1; 
}

UT_array * postProcessingInitializeSpecialChar()
{
  char *specialCharacter;

  UT_array *specialChar;
  utarray_new(specialChar, &ut_str_icd);

  // all the special characters
  specialCharacter = "`";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "!";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "@";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "#";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "$";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "%";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "^";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "&";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "*";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "(";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = ")";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "-";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "_";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "=";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "+";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "[";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "{";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "]";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "}";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "\\";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "|";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = ";";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = ":";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "'";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "\"";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = ",";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "<";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = ".";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = ">";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "/";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "?";
  utarray_push_back(specialChar, &specialCharacter);
  specialCharacter = "~";
  utarray_push_back(specialChar, &specialCharacter);
  
  return specialChar;
  
}

UT_array * postProcessingInitializeDictionary()
{
  char * word;
  char ** p;

  UT_array *dictionary;
  utarray_new(dictionary, &ut_str_icd);

  //all ansi c keyword 	
  word = "auto";
  utarray_push_back(dictionary, &word);
  word = "break";
  utarray_push_back(dictionary, &word);
  word = "case";
  utarray_push_back(dictionary, &word);
  word = "char";
  utarray_push_back(dictionary, &word);
  word = "const";
  utarray_push_back(dictionary, &word);
  word = "continue";
  utarray_push_back(dictionary, &word);
  word = "default";
  utarray_push_back(dictionary, &word);
  word = "do";
  utarray_push_back(dictionary, &word);
  word = "double";
  utarray_push_back(dictionary, &word);
  word = "else";
  utarray_push_back(dictionary, &word);
  word = "enum";
  utarray_push_back(dictionary, &word);
  word = "extern";
  utarray_push_back(dictionary, &word);
  word = "float";
  utarray_push_back(dictionary, &word);
  word = "for";
  utarray_push_back(dictionary, &word);
  word = "goto";
  utarray_push_back(dictionary, &word);
  word = "if";
  utarray_push_back(dictionary, &word);
  word = "int";
  utarray_push_back(dictionary, &word);
  word = "long";
  utarray_push_back(dictionary, &word);
  word = "register";
  utarray_push_back(dictionary, &word);
  word = "return";
  utarray_push_back(dictionary, &word);
  word = "short";
  utarray_push_back(dictionary, &word);
  word = "signed";
  utarray_push_back(dictionary, &word);
  word = "sizeof";
  utarray_push_back(dictionary, &word);
  word = "static";
  utarray_push_back(dictionary, &word);
  word = "struct";
  utarray_push_back(dictionary, &word);
  word = "typedef";
  utarray_push_back(dictionary, &word);
  word = "union";
  utarray_push_back(dictionary, &word);
  word = "unsigned";
  utarray_push_back(dictionary, &word);
  word = "void";
  utarray_push_back(dictionary, &word);
  word = "volatile";
  utarray_push_back(dictionary, &word);
  word = "while";
  utarray_push_back(dictionary, &word);
  word = "switch";
  utarray_push_back(dictionary, &word);
  
  return dictionary;
  
}

void postProcessingCleanUP(UT_array * dictionary, UT_array * specialCharacter)
{
  utarray_free(dictionary);
  utarray_free(specialCharacter);
}


int main(void)
{
  UT_array * dictionary;
  UT_array * specialChar;
  
  UT_array * WholeString = NULL;
  CharProfile NewCharProfile;
  CharProbability NewCharProbability;
  
  utarray_new(dictionary, &ut_str_icd);
  utarray_new(specialChar, &ut_str_icd);
  dictionary = postProcessingInitializeDictionary();
  specialChar = postProcessingInitializeSpecialChar();

  
  /*initialize string profile*/
  UT_icd StringProfile_icd = {sizeof(CharProfile), NULL, NULL, CharProfile_free};
  utarray_new(WholeString, &StringProfile_icd);
  
  /*first char spot*/	
  UT_icd CharProbability_icd = {sizeof(CharProbability), NULL, NULL, NULL};
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 'f';
  NewCharProbability.Probability = 25;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 't';
  NewCharProbability.Probability = 75;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability); 
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*second char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 'o';
  NewCharProbability.Probability = 35;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = '0';
  NewCharProbability.Probability = 85;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*third char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 't';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 'r';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*third char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = '(';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = '=';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*fifth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 'm';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 'n';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*sixth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 'y';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 't';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*seventh char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = ' ';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 'u';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*eigth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 'h';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 'w';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*ninth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = ')';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = '}';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*tenth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = '\n';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 'u';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*sixth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = '{';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = '[';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*sixth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 'd';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 'a';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*sixth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 'u';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 'd';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  /*sixth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 't';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 'y';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
   /*sixth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = 'o';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = 't';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
   /*sixth char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  /*first possibility*/
  NewCharProbability.Char = '}';
  NewCharProbability.Probability = 50;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*second probability*/
  NewCharProbability.Char = ']';
  NewCharProbability.Probability = 100;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  
  
  postProcessing(WholeString,dictionary,specialChar);
  

  postProcessingCleanUP(dictionary, specialChar);
  return 0;
}