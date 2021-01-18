#include <iostream>
#include <vector>
#include "pgmImage.h"
using namespace std;

PgmImage convolute(PgmImage &resultImage, vector<float> kernel);
PgmImage invert(PgmImage &resultImage);
PgmImage pickFilter(PgmImage inputImage, int &filterNumber);