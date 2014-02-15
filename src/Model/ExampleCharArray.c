#include "ModelStructure.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void CharProfile_free(void * profile_in){
	CharProfile * profile = (CharProfile *) profile_in;
	utarray_free(profile->CharChoices);
}

int main(void){
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
	
	/*push to the whole string*/
	utarray_push_back(WholeString, &NewCharProfile);
	
	
	/*does some iteration and display the structure*/
	CharProfile * CurrCharProfile = NULL;
	CharProbability * CurrCharProbability = NULL;
	int counter1 = 0, counter2 = 0;
	while( (CurrCharProfile=(CharProfile *)utarray_next(WholeString,CurrCharProfile))) {
	 	printf("counter 1 = %d\n", counter1++);
		counter2 = 0;
		CurrCharProbability = NULL;
		while( (CurrCharProbability = (CharProbability *) utarray_next(CurrCharProfile->CharChoices, CurrCharProbability))){
			printf("counter 2 = %d\n", counter2++);
			printf("Character is %c with probability %d\n", CurrCharProbability->Char, CurrCharProbability->Probability);
		}
	 
		
	}
	
	/*free them all*/
	/*CurrCharProfile = NULL;
	CurrCharProbability = NULL;
	while( (CurrCharProfile=(CharProfile*)utarray_next(WholeString,CurrCharProfile))) {	 	
		utarray_free(CurrCharProfile->CharChoices);		
	}*/
	utarray_free(WholeString);
	
	
	return 0;
}