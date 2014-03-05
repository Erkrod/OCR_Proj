/*this file will be used to test post processing

Input will be hard coded in the program: An array of CharProfile, each CharProfile contains an array of CharProbability

Output will be ut_string type, character after character includes newline character too

Phase 1: take only the character with the highest probability at one spot

Phase 2: The algorithm should be able to match C syntax as much as possible

*/

#include <stdio.h>
#include <stdlib.h>

#include "Model.h"
#include "View.h"
#include "Control.h"

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
