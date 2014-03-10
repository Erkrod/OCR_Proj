#include "Model.h"


void CharProfile_free(void * profile_in){
	CharProfile * profile = (CharProfile *) profile_in;
	utarray_free(profile->CharChoices);
}

void postProcessingInitialize(UT_array * , UT_array *);
void postProcessingCleanUP(UT_array * , UT_array * );
UT_string * postProcessing(UT_array * );
//UT_string * postProcessing2(UT_array *);
//UT_array * getThreeKeyword(CharProfile *, UT_array *);

//char * getTopProb(UT_array *);
//char * getSecondProb(UT_array *);

#if 0
int main(void)
{
  UT_array * dictionary;
  UT_array * specialChar;
  
  UT_array * WholeString = NULL;
  CharProfile NewCharProfile;
  CharProbability NewCharProbability;
  
  utarray_new(dictionary, &ut_str_icd);
  utarray_new(specialChar, &ut_str_icd);
  postProcessingInitialize(dictionary, specialChar);
  
  /*initialize string profile*/
  UT_icd StringProfile_icd = {sizeof(CharProfile), NULL, NULL, CharProfile_free};
  utarray_new(WholeString, &StringProfile_icd);
  
  /*first char spot*/	
  UT_icd CharProbability_icd = {sizeof(CharProbability), NULL, NULL, NULL};
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  
  /*first possibility*/
  NewCharProbability.Char = 'a';
  NewCharProbability.Probability = 25;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  
  
  /*second probability*/
  NewCharProbability.Char = 'z';
  NewCharProbability.Probability = 75;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);


  /*second char spot*/	
  utarray_new(NewCharProfile.CharChoices, &CharProbability_icd);
  
  /*first possibility*/
  NewCharProbability.Char = 'B';
  NewCharProbability.Probability = 35;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  
  
  /*second probability*/
  NewCharProbability.Char = 'D';
  NewCharProbability.Probability = 85;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  postProcessing(WholeString);
  postProcessingCleanUP(dictionary, specialChar);
  return 0;
}
#endif

void postProcessingInitialize(UT_array * dictionary, UT_array * specialChar)
{
  char words[32][15];
	char specialCharacter[32][3];
  char *temp;
  char ** p;
  int i = 0;

  //all ansi c keyword 	
  strcpy(words[0],"auto");
  strcpy(words[1],"break");
  strcpy(words[2],"case");
  strcpy(words[3],"char");
  strcpy(words[4],"const");
  strcpy(words[5],"continue");
  strcpy(words[6],"default");
  strcpy(words[7],"do");
  strcpy(words[8],"double");
  strcpy(words[9],"else");
  strcpy(words[10],"enum");
  strcpy(words[11],"extern");
  strcpy(words[12],"float");
  strcpy(words[13],"for");
  strcpy(words[14],"goto");
  strcpy(words[15],"if");
  strcpy(words[16],"int");
  strcpy(words[17],"long");
  strcpy(words[18],"register");
  strcpy(words[19],"return");
  strcpy(words[20],"short");
  strcpy(words[21],"signed");
  strcpy(words[22],"sizeof");
  strcpy(words[23],"static");
  strcpy(words[24],"struct");
  strcpy(words[25],"switch");
  strcpy(words[26],"typedef");
  strcpy(words[27],"union");
  strcpy(words[28],"unsigned");
  strcpy(words[29],"void");
  strcpy(words[30],"volatile");
  strcpy(words[31],"while");

  // all the special characters
  strcpy(specialCharacter[0],"`");
  strcpy(specialCharacter[1],"~");
  strcpy(specialCharacter[2],"!");
  strcpy(specialCharacter[3],"@");
  strcpy(specialCharacter[4],"#");
  strcpy(specialCharacter[5],"$");
  strcpy(specialCharacter[6],"%");
  strcpy(specialCharacter[7], "^");
  strcpy(specialCharacter[8], "&");
  strcpy(specialCharacter[9], "*");
  strcpy(specialCharacter[10], "(");
  strcpy(specialCharacter[11], ")");
  strcpy(specialCharacter[12], "-");
  strcpy(specialCharacter[13], "_");
  strcpy(specialCharacter[14], "=");
  strcpy(specialCharacter[15], "+");
  strcpy(specialCharacter[16], "[");
  strcpy(specialCharacter[17], "{");
  strcpy(specialCharacter[18], "]");
  strcpy(specialCharacter[19], "}");
  strcpy(specialCharacter[20], "\\");
  strcpy(specialCharacter[21], "|");
  strcpy(specialCharacter[22], ";");
  strcpy(specialCharacter[23], ":");
  strcpy(specialCharacter[24], "\"");
  strcpy(specialCharacter[25], "\"");
  strcpy(specialCharacter[26], ",");
  strcpy(specialCharacter[27], "<");
  strcpy(specialCharacter[28], ".");
  strcpy(specialCharacter[29], ">");
  strcpy(specialCharacter[30], "/");
  strcpy(specialCharacter[31], "?");
	
  for (i = 0; i < 32; i++)
  {
    temp = words[i];
    utarray_push_back(dictionary, &temp);
  }
  
  for (i = 0; i < 32; i++)
  {
    temp = specialCharacter[i];
    utarray_push_back(specialChar, &temp);
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
    //printf("counter 1 = %d\n", count++);
    count2 = 0;
    currCharProbability = NULL;
    percentage = 0;
    
    while((currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability)))
    {
     // printf("counter 2 = %d\n", count2++);
      printf("Character is %c with probability %d\n", currCharProbability->Char, currCharProbability->Probability);
      
      /* found a character with a higher percentage */
      if (percentage < currCharProbability->Probability)
      {
	percentage = currCharProbability->Probability;
	chosen = currCharProbability->Char;

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

////////////////////////////////// MIGHT WORK //////////////////////// 
/*
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


*/

/* WORK IN PROGRESS 
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
	// NEED A LOOP HERE THAT SENDS CHARACTER UP TO SPECIAL CHARACTER 
  wordBank = getThreeKeyword(currCharProbability, charList);
	
	chosen = wordCompare(wordBank);
	utstring_new(temp);
	utstring_printf(temp, "%c", chosen);
	
	utstring_concat(output, temp);
    
  return output;
}
// NEED FIXING 
UT_array * getThreeKeyword(CharProfile *currCharProfile, UT_array * charList)
{
	char * top;
	char * second;
	char * concatWord;
	CharProfile * tempPosition = currCharProfile;
	
	UT_array * wordBank;
	utarray_new(wordBank, &ut_str_icd);
	
	int i, j;

	for (i = 0; i < 3; i++)
	{
		top = getTopProb(currCharProfile);
		second = getSecondProb(currCharProfile);
	
		for (j = 0; j < 3; j++)
		{
			if (j > 0)
			{
				tempPosition = utarray_next(charList, tempPosition);
			}
				
			top = getTopProb(tempPosition);
			second = getSecondProb(tempPositon);
			
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
char * getTopProb(UT_array * currCharProfile)
{
	CharProbability * currCharProbability = NULL;
	currCharProbability = utarray_front(currCharProfile);
	return currCharProbability->Char;
}
char * getSecondProb(UT_array * currCharProfile)
{
	CharProbability * currCharProbability = NULL;
	currCharProbability = utarray_next(utarray_front(currCharProfile), currCharProfile);
	return currCharProbability->Char;
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
*/
