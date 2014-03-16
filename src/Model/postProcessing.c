#include <stdio.h>
#include <stdlib.h>
#include "utstring.h"
#include "utarray.h"
#include "ModelStructure.h"

void CharProfile_free(void * profile_in){
	CharProfile * profile = (CharProfile *) profile_in;
	utarray_free(profile->CharChoices);
}

UT_string * postProcessing(UT_array * );

int main(void)
{
  UT_array * dictionary;
  UT_array * specialChar;
  
  UT_array * WholeString = NULL;
  CharProfile NewCharProfile;
  CharProbability NewCharProbability;
  
  utarray_new(dictionary, &ut_str_icd);
  utarray_new(specialChar, &ut_str_icd);
  
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
  NewCharProbability.Char = '\'';
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
  NewCharProbability.Char = '\'';
  NewCharProbability.Probability = 85;
  utarray_push_back(NewCharProfile.CharChoices, &NewCharProbability);
  
  /*push to the whole string*/
  utarray_push_back(WholeString, &NewCharProfile);
  
  postProcessing(WholeString);
  return 0;
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
  char quotation = 'a';
  char *tempCharacter;
  
  utstring_new(output);
  
  while((currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile)))
  {
    count2 = 0;
    currCharProbability = NULL;
    percentage = 0;
    
    while((currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability)))
    {
      /* found a character with a higher percentage */
      if (percentage < currCharProbability->Probability)
      {
	percentage = currCharProbability->Probability;
	chosen = currCharProbability->Char;
	
	/* it is 100% why bother searching for a a higher percentage */
	if (percentage == 100)
	{
	  break;
	}
      }
    }
    /* we had a problem with identifying " so this if statement should take care of it */
    /* instead of identifying ", we instead, identify two ' ' */
    if (chosen == '\'')
    {
      currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile);
      while((currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability)))
      {
	/* found a character with a higher percentage */
	if (percentage < currCharProbability->Probability)
	{
	  percentage = currCharProbability->Probability;
	  quotation = currCharProbability->Char;
	  
	  /* it is 100% why bother searching for a a higher percentage */
	  if (percentage == 100)
	  {
	    break;
	  }
	}
      }
      if (quotation == '\'')
      {
	chosen = '"';
      }
      else
      {
	tempCharacter = &chosen;
	strcat(tempCharacter, &quotation);
      }
    }
    
    /* adding the chosen character to a temp string */
    utstring_new(temp);
    utstring_printf(temp, "%c", chosen);
    
    /* concat the temp character to the real output string */
    utstring_concat(output, temp);
  }
    
  return output;
}