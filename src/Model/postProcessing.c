#include <stdio.h>
#include <stdlib.h>
#include "utstring.h"
#include "utarray.h"
#include "ModelStructure.h"

UT_string * postProcessing(UT_array * );

void CharProfile_free(void * profile_in){
	CharProfile * profile = (CharProfile *) profile_in;
	utarray_free(profile->CharChoices);
}

int main(void)
{
	
  UT_array * WholeString = NULL;
  CharProfile NewCharProfile;
  CharProbability NewCharProbability;
  
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
  NewCharProbability.Char = 'A';
  NewCharProbability.Probability = 35;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  
  
  /*second probability*/
  NewCharProbability.Char = 'Z';
  NewCharProbability.Probability = 85;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  
  postProcessing(WholeString);
  
  return 0;
}

UT_string * postProcessing(UT_array * charList)
{
  UT_string * output;
  CharProfile * currCharProfile = currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile);
  CharProbability * currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability);
  int count1 = 1, count2 = 1;
  int count = 0;
  int percentage = currCharProbability->Probability;
  char chosen = currCharProbability->Char;
  
  
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
/*      if (percentage < currCharProbability->Probability)
      {
	 percentage = currCharProbability->Probability;
	 chosen = currCharProbability->Char;
      }
*/    }
    
    /* adding the chosen character to the string */
/*    utstring_new(output);
    utstring_printf(output, chosen);
*/  }
/*  return output;
*/}
