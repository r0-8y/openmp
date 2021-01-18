#include <iostream>
#include <vector>
#include "pgmImage.h"
using namespace std;

PgmImage edgeDetect1(PgmImage &resultImage);
PgmImage edgeDetect2(PgmImage &resultImage);
PgmImage edgeDetect3(PgmImage &resultImage);
PgmImage sharpen(PgmImage &resultImage);
PgmImage boxBlur(PgmImage &resultImage);
PgmImage gaussian3(PgmImage &resultImage);
PgmImage gaussian5(PgmImage &resultImage);
PgmImage emboss(PgmImage &resultImage);
PgmImage invert(PgmImage &resultImage);