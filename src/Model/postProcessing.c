#include <stdio.h>
#include <stdlib.h>
#include "utstring.h"
#include "utarray.h"
#include "ModelStructure.h"

void CharProfile_free(void * profile_in){
	CharProfile * profile = (CharProfile *) profile_in;
	utarray_free(profile->CharChoices);
}

/* call function to populate the dictionary */
void populateDictionary(void);

/* the actual dictionary */
UT_array * dictionary = NULL;

UT_string * matchKeywords(UT_string *);

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
  
  populateDictionary();
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

void populateDictionary(void)
{
  char words[32][15];
  int i = 0;
  
  /*initialize string profile*/
  utarray_new(dictionary, &ut_str_icd);
  
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

 for (i = 0; i < 32; i++)
 {
   utarray_push_back(dictionary, &words[i]);
 }
}
