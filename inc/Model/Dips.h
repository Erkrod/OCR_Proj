#ifndef DIPS_H
#define DIPS_H

#include <assert.h>
#include "Image.h"
#include "FileIO.h"
#include "Constants.h"

IMAGE *CropImage(IMAGE *image, int x1, int y1, int x2, int y2);
/*This function will crop the image into a smaller area between (x1,
y1) and (x2, y2). (x1,y1) is on top left and (x2, y2) is on lower
right. You can assume that the input is checked to be valid.
*/

IMAGE *Rotate(IMAGE *image, int ClockwiseDegree);
/*This function will rotate the image clockwise direction with given
degree.
*/

IMAGE *Resize(IMAGE *image, unsigned int percentage);
/*This function will resize the image into new size. Could use last
year solution.
*/

IMAGE *ColorFilter(IMAGE *image, int x, int y, int area_x1, int area_y1, int area_x2, int area_y2, int NewPixelValue, int threshold);

IMAGE *StainRemoval(IMAGE *image, int c_var1, int c_var2, int b_threshold, int darken_limiter);
#endif
