#include <iostream>
#include <vector>
#include <fstream>
#include <omp.h>
using namespace std;

class PgmImage
{
public:
    string formatFlag;
    int width, height, maxPixelValue;
    vector<float> pixels;
    PgmImage();
    PgmImage(string formatFlag, int width, int height, int maxPixelValue, vector<float> pixels);
    void print();
    void printToFile(string path);
};