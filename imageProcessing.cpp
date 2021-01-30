#include "pgmImage.h"

// matrix kernels that are needed for the convolution process defined as std::vector because of easier function calls
const vector<float> edgeDetect1K({1, 0, -1, 0, 0, 0, -1, 0, 1});
const vector<float> edgeDetect2K({0, -1, 0, -1, 4, -1, 0, -1, 0});
const vector<float> edgeDetect3K({-1, -1, -1, -1, 8, -1, -1, -1, -1});
const vector<float> sharpenK({0, -1, 0, -1, 5, -1, 0, -1, 0});
const vector<float> embossK({-2, -1, 0, -1, 1, 1, 0, 1, 2});
const vector<float> boxBlurK({1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9, 1. / 9});
const vector<float> gaussian3K({1. / 16, 2. / 16, 1. / 16, 2. / 16, 4. / 16, 2. / 16, 1. / 16, 2. / 16, 1. / 16});
const vector<float> gaussian5K({
    1. / 256,
    4. / 256,
    6. / 256,
    4. / 256,
    1. / 256,
    4. / 256,
    16. / 256,
    24. / 256,
    16. / 256,
    4. / 256,
    6. / 256,
    24. / 256,
    36. / 256,
    24. / 256,
    6. / 256,
    4. / 256,
    16. / 256,
    24. / 256,
    16. / 256,
    4. / 256,
    1. / 256,
    4. / 256,
    6. / 256,
    4. / 256,
    1. / 256,
});

// function that multiplies the matricies
// the "&" is there to pass the image by refference and not make a new copy to save space
PgmImage convolute(PgmImage &resultImage, vector<float> kernel)
{
    // temporary vector for resulting matrix because the width and height of the image change
    vector<float> resultPixels = resultImage.pixels;
    // accumulator for saving the final pixel value
    float acc = 0;
    // checking the kernel size for correct looping
    int size = kernel.size() == 9 ? 3 : 5;

    double begin = omp_get_wtime();

#pragma omp parallel for firstprivate(acc, kernel)
    for (int i = 0; i < resultImage.height - size + 1; i++)
    {
        for (int j = 0; j < resultImage.width - size + 1; j++)
        {
            // set accumulator to zero before convolution
            acc = 0;
            // loop through the kernel and the corresponding matrix in the image
            for (int k = 0; k < size; k++)
            {
                for (int l = 0; l < size; l++)
                {
                    // multiply the elements and add them to the accumulator
                    acc += kernel[k * size + l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
                }
            }
            resultPixels[i * (resultImage.width - size + 1) + j] = acc;
        }
    }

    cout << "Time elapsed: " << omp_get_wtime() - begin << " [s]" << endl;

    // update the result image values
    resultImage.pixels = resultPixels;
    // we need to shrink the image by (size - 1) because of convolution
    resultImage.width -= (size - 1);
    resultImage.height -= (size - 1);

    return resultImage;
}

// function that returns the negative value (255 - pixel value) of the image
// the "&" is there to pass the image by refference and not make a new copy to save space
PgmImage invert(PgmImage &resultImage)
{
#pragma omp parallel for collapse(2)
    for (int i = 0; i < resultImage.height; i++)
    {
        for (int j = 0; j < resultImage.width; j++)
        {
            resultImage.pixels[i * resultImage.width + j] = 255 - resultImage.pixels[i * resultImage.width + j];
        }
    }
    return resultImage;
}

// function that picks the right kernel based on the input from the user
PgmImage pickFilter(PgmImage inputImage, int &filterNumber)
{
    switch (filterNumber)
    {
    case 1:
        return convolute(inputImage, edgeDetect1K);
    case 2:
        return convolute(inputImage, edgeDetect2K);
    case 3:
        return convolute(inputImage, edgeDetect3K);
    case 4:
        return convolute(inputImage, sharpenK);
    case 5:
        return convolute(inputImage, boxBlurK);
    case 6:
        return convolute(inputImage, gaussian3K);
    case 7:
        return convolute(inputImage, gaussian5K);
    case 8:
        return convolute(inputImage, embossK);
    case 9:
        return invert(inputImage);
    }

    return PgmImage();
}
