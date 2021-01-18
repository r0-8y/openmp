#include "pgmImage.h"

// default constructor
PgmImage::PgmImage() : formatFlag(""), width(0), height(0), maxPixelValue(0), pixels(vector<float>()) {}
// constructor
PgmImage::PgmImage(string formatFlag, int width, int height, int maxPixelValue, vector<float> pixels) : formatFlag(formatFlag), width(width), height(height), maxPixelValue(maxPixelValue), pixels(pixels) {}

// function that prints an image to standard output
void PgmImage::print()
{
    cout << formatFlag << endl
         << width << " " << height << endl
         << maxPixelValue << endl;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cout << pixels[i * width + j];
            if (pixels[i * width + j] > 99)
            {
                cout << " ";
            }
            else if (pixels[i * width + j] < 10)
            {
                cout << "   ";
            }
            else
            {
                cout << "  ";
            }
        }
        cout << endl;
    }
}

// function that writes the result image to a file named "result.pgm"
void PgmImage::printToFile(string path)
{
    ofstream resultImage(path);
    if (resultImage)
    {
        // writing the header elements
        resultImage << this->formatFlag << endl;
        resultImage << "#" << endl;
        resultImage << this->width << " " << this->height << endl;
        // this shouldnt be the maxPixelValue because after every filter the maxValue changes,
        // i will fix this in the future
        resultImage << this->maxPixelValue << endl;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                resultImage << this->pixels[i * width + j];
                if (this->pixels[i * width + j] > 99)
                {
                    resultImage << " ";
                }
                else if (this->pixels[i * width + j] < 10)
                {
                    resultImage << "   ";
                }
                else
                {
                    resultImage << "  ";
                }
            }
            resultImage << endl;
        }
        resultImage.close();
    }
    else
    {
        cout << "The image couldn't be written!" << endl;
        exit(0);
    }
}