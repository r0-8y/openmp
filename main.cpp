#include <iostream>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <chrono>
#include "imageProcessing.h"
// import needed for knowing the workspace path
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

using namespace std;
using namespace chrono;

PgmImage readFile(string path)
{
    string formatFlag, commentLine, width, height, maxPixelValue, pixel;
    vector<float> pixels;
    char hash;
    int pixelI, widthI, heightI, maxPixelValueI;

    ifstream inputImage(path);
    if (inputImage)
    {
        getline(inputImage, formatFlag);
        inputImage.get(hash);
        if (hash == '#')
        {
            getline(inputImage, commentLine);
        }
        else
        {
            inputImage.unget();
        }
        getline(inputImage, width, ' ');
        stringstream ssw(width);
        ssw >> widthI;
        getline(inputImage, height);
        stringstream ssh(height);
        ssh >> heightI;
        getline(inputImage, maxPixelValue);
        stringstream ssm(maxPixelValue);
        ssm >> maxPixelValueI;
        while (inputImage >> pixel)
        {
            stringstream ss(pixel);
            ss >> pixelI;
            pixels.push_back(pixelI);
        }
        inputImage.close();
    }

    else
    {
        cout << "The image doesn't exist!" << endl;
        return PgmImage();
    }
    return PgmImage(formatFlag, widthI, heightI, maxPixelValueI, pixels);
}

int main(void)
{
    int filterNumber = 5;
    // code needed to know the workspace path on any computer, not just mine
    char buff[FILENAME_MAX];
    GetCurrentDir(buff, FILENAME_MAX);
    string current_working_dir(buff), imageName, filter;

    // a simple application with input validation for avoiding potential errors 
    while (imageName != "stop")
    {
        cout << "Write the exact name of the image that you want to work with, or write stop to terminate the program: ";
        getline(cin, imageName);
        if (imageName == "stop")
            break;
        PgmImage inputImage = readFile(current_working_dir + "/images/" + imageName);
        if (inputImage.formatFlag == "")
            continue;
        cout << "Available filters:\n1. Edge detection 1\n2. Edge detection 2\n3. Edge detection 3\n";
        cout << "4. Sharpen\n5. Box blur\n6. Gaussian blur 3x3\n7. Gaussian blur 5x5\n8. Emboss\n9. Invert\n";
        while (1)
        {
            cout << "Choose a filter by typing its number: ";
            getline(cin, filter);
            stringstream ssf(filter);
            if (ssf >> filterNumber)
            {
                if (filterNumber < 1 || filterNumber > 9)
                    continue;
                break;
            }
            else
            {
                continue;
            }
        }

        // we measure the time needed for matrix multiplication
        steady_clock::time_point time = steady_clock::now();
        PgmImage resultImage = pickFilter(inputImage, filterNumber);
        cout << "Time elapsed: " << duration_cast<nanoseconds>(steady_clock::now() - time).count() << " [ns]" << endl;
        // printing the image to a file
        resultImage.printToFile(current_working_dir + "/result.pgm");
    }

    return 0;
}