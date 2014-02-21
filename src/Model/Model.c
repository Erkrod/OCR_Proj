#include "model.h"

UT_string postProcessing(UT_array * charList)
{
  UT_string output;
  CharProfile * currCharProfile = NULL;
  CharProbability * currCharProbability = NULL;
  int count1 = 0, count2 = 0;
  
  while((currCharProfile = (CharProfile *) utarray_next(charList, currCharProfile)))
  {
    printf("counter 1 = %d\n", count++);
    count2 = 0;
    currCharProbability = NULL;
    while((currCharProbability = (CharProbability *) utarray_next(currCharProfile->CharChoices, currCharProbability)))
    {
      printf("counter 2 = %d\n", count2++);
      printf("Character is %c with probability %d\n", currCharProbability->Char, currCharProbability->Probability);
    }
  }
}
