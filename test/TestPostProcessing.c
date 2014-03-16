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
  UT_array * dictionary;
  UT_array * specialChar;
  
  UT_array * WholeString = NULL;
  CharProfile NewCharProfile;
  CharProbability NewCharProbability;
  
  /*utarray_new(dictionary, &ut_str_icd);
  utarray_new(specialChar, &ut_str_icd);*/
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
  
  
  
  UT_string * advance_string = postProcessingAdvance(WholeString,dictionary,specialChar);
  UT_string * normal_string = postProcessing(WholeString);
  
  printf("Result from highest probability catch is:\n%s\nResult from keyword match is:\n%s\n", utstring_body(normal_string), utstring_body(advance_string));
  
  utstring_free(advance_string);
  utstring_free(normal_string);
  

  postProcessingCleanUP(dictionary, specialChar);
  return 0;
}
