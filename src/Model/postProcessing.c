#include <stdio.h>
#include <stdlib.h>
#include "utstring.h"
#include "utarray.h"
#include "ModelStructure.h"

void CharProfile_free(void * profile_in){
	CharProfile * profile = (CharProfile *) profile_in;
	utarray_free(profile->CharChoices);
}

void postProcessingInitialize(void);
void postProcessingCleanUP(UT_array * , UT_array * );
UT_string * postProcessing2(UT_array *);
UT_array * getThreeKeyword(CharProfile *, UT_array *);

CharProbability * getTopProb(UT_array *);
CharProbability * getSecondProb(UT_array *);

void postProcessingInitialize(UT_array * dictionary, UT_array * specialChar)
{
  /* the actual dictionary */
  char words[32][15];
	char specialCharacter[32];
  int i = 0;
  
  /*all ansi c keyword */	
  words[0] = "auto";
  words[1] = "break";
  words[2] = "case";
  words[3] = "char";
  words[4] = "const";
  words[5] = "continue";
  words[6] = "default";
  words[7] = "do";
  words[8] = "double";
  words[9] = "else";
  words[10] = "enum";
  words[11] = "extern";
  words[12] = "float";
  words[13] = "for";
  words[14] = "goto";
  words[15] = "if";
  words[16] = "int";
  words[17] = "long";
  words[18] = "register";
  words[19] = "return";
  words[20] = "short";
  words[21] = "signed";
  words[22] = "sizeof";
  words[23] = "static";
  words[24] = "struct";
  words[25] = "switch";
  words[26] = "typedef";
  words[27] = "union";
  words[28] = "unsigned";
  words[29] = "void";
  words[30] = "volatile";
  words[31] = "while";
	
	/* all the special characters */
	specialCharacter[0] = '`';
	specialCharacter[1] = '~';
	specialCharacter[2] = '!';
	specialCharacter[3] = '@';
	specialCharacter[4] = '#';
	specialCharacter[5] = '$';
	specialCharacter[6] = '%';
	specialCharacter[7] = '^';
	specialCharacter[8] = '&';
	specialCharacter[9] = '*';
	specialCharacter[10] = '(';
	specialCharacter[11] = ')';
	specialCharacter[12] = '-';
	specialCharacter[13] = '_';
	specialCharacter[14] = '=';
	specialCharacter[15] = '+';
	specialCharacter[16] = '[';
	specialCharacter[17] = '{';
	specialCharacter[18] = ']';
	specialCharacter[19] = '}';
	specialCharacter[20] = '\\';
	specialCharacter[21] = '|';
	specialCharacter[22] = ';';
	specialCharacter[23] = ':';
	specialCharacter[24] = ''';
	specialCharacter[25] = '"';
	specialCharacter[26] = ',';
	specialCharacter[27] = '<';
	specialCharacter[28] = '.';
	specialCharacter[29] = '>';
	specialCharacter[30] = '/';
	specialCharacter[31] = '?';

 for (i = 0; i < 32; i++)
 {
   utarray_push_back(dictionary, &words[i]);
 }
 
 for (i = 0; i < 32; i++)
 {
   utarray_push_back(specialChar, &specialCharacter[i]);
 }
 
}

void postProcessingCleanUP(UT_array * dictionary, UT_array * specialCharacter)
{
	utarray_free(dictionary);
	utarray_free(specialCharacter);
}

/* part 1 of the post processing stage */
UT_string * postProcessing(UT_array * charList)
{
  UT_string * temp;
  UT_string * output;
  CharProfile * currCharProfile = NULL;
  CharProbability * currCharProbability = NULL;
  int count1 = 0, count2 = 0;
  int count = 0;
  int percentage = 0;
  char chosen = 'a';
  
  utstring_new(output);
  
  while((currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile)))
  {
    printf("counter 1 = %d\n", count++);
    count2 = 0;
    currCharProbability = NULL;
    
    while((currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability)))
    {
      printf("counter 2 = %d\n", count2++);
      printf("Character is %c with probability %d\n", currCharProbability->Char, currCharProbability->Probability);
      
      /* found a character with a higher percentage */
      if (percentage < currCharProbability->Probability)
      {
				percentage = currCharProbability->Probability;
				chosen = currCharProbability->Char;
	 
				if (percentage == 100)
				{
					break;
				}
			}
    }
    
    /* adding the chosen character to a temp string */
    utstring_new(temp);
    utstring_printf(temp, "%c", chosen);
    
    /* concat the temp character to the real output string */
    utstring_concat(output, temp);
  }
  
  /* print the string to test */
  printf("the chosen character is: %s\n", utstring_body(output));
    
  return output;
}

/* ///////////////////////////////// MIGHT WORK //////////////////////// */
UT_string * matchKeywords(UT_string *);
UT_string * matchKeywords(UT_string *output)
{
  int i = 0, j = 0, k = 0;
  int keyWordLen = 0;
  int outputLen = utString_len(output);
  char * convertedOutput = utstring_body(output);
  char * croppedWord = "";
  char * dictionaryWord = "";
  int characterMatched = 0;
  UT_string * newOutput;
  utstring_new(newOutput);
  
  for (i = 0; i < 32; i++)
  {
	keyWordLen=sizeof(dictionary[i]);
	dictionaryWord = dictionary[i];
	characterMatched = 0;
	for (j = 0; j < outputLen - keyWordLen; j++)
	{
	  strncopy(croppedWord, convertedOutput + j, keyWordLen);

	  for (k = 0; k < keyWordLen; k++)
	  {
		if (croppedWord[k] == dictionaryWord[k])
		{
		  characterMatched++;
		}
		if (keyWordLen > 2 && (keyWordLen - characterMatched) < 2)
		{
			utstring_renew(newOutput);
			utstring_printf(newOutput, convertedOutput(0, j));
			utstring_printf(newOutput, croppedWord);
			utstring_printf(newOutput, convertedOutput(j + keyWordLen));
			utstring_renew(output);
			utstring_printf(output, newOutput);
			j += keyWordLen - 1;
			break;
		}
	  }
	}
  }
}




/* WORK IN PROGRESS */
UT_string * postProcessing2(UT_array * charList)
{
	UT_string * temp;
  UT_string * output;
  CharProfile * currCharProfile = NULL;
  CharProbability * currCharProbability = NULL;
	UT_array * wordBank;
	utarray_new(wordBank, &ut_str_icd);
  int count2 = 0;
  int count = 0;
  char chosen = 'a';

  utstring_new(output);
	/* NEED A LOOP HERE THAT SENDS CHARACTER UP TO SPECIAL CHARACTER */
  wordBank = getThreeKeyword(currCharProbability, charList);
	
	chosen = wordCompare(wordBank);
	utstring_new(temp);
	utstring_printf(temp, "%c", chosen);
	
	utstring_concat(output, temp);
    
  return output;
}
/* NEED FIXING */
UT_array * getThreeKeyword(CharProfile *currCharProfile, UT_array * charList)
{
	char * top;
	char * second;
	char * concatWord;
	
	UT_array * wordBank;
	utarray_new(wordBank, &ut_str_icd);
	
	int i, j;

	top = getTopProb(currCharProfile)->Char;
	second = getSecondProb(currCharProfile)->Char;
	
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == j)
			{
				strcat(concatWord, second);
			}
			else
			{
				strcat(concatWord, top);
			}
		}
		utarray_push_back(wordBank, concatWord);
	}
}
CharProbability * getTopProb(UT_array * currCharProfile)
{
	return utarray_front(currCharProfile);
}
CharProbability * getSecondProb(UT_array * currCharProfile)
{
	return utarray_next(utarray_front(currCharProfile), currCharProfile);
}

char *wordCompare(UT_array *);
char *wordCompare(UT_array * charList)
{
	char * temp;
	int i;
	while((temp = utarray_next(charList, temp)))
	{
		for (i = 0; i < 32, i++)
		{
			if (strcmp(temp, dictionary[i]) == 0)
			{
				return temp;
			}
		}
	}
	return utarray_front(charList);
}
