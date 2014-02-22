#include "model.h"

UT_string * postProcessing(UT_array * charList)
{
  UT_string * output;
  CharProfile * currCharProfile = currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile);
  CharProbability * currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability);
  int count1 = 1, count2 = 1;
  
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
