#include "pgmImage.h"

PgmImage edgeDetect1(PgmImage resultImage)
{
    vector<float> resultPixels;
    /* const float edgeDetection[5][5] = {
        {1. / 256, 4. / 256, 6. / 256, 4. / 256, 1. / 256},
        {4. / 256, 16. / 256, 24. / 256, 16. / 256, 4. / 256},
        {6. / 256, 24. / 256, 36. / 256, 24. / 256, 6. / 256},
        {4. / 256, 16. / 256, 24. / 256, 16. / 256, 4. / 256},
        {1. / 256, 4. / 256, 6. / 256, 4. / 256, 1. / 256},
    };  */
    float edgeDetect[3][3] = {
        {1, 0, -1},
        {0, 0, 0},
        {-1, 0, 1}};
    float acc;

    for (int i = 0; i < resultImage.height - 2; i++)
    {
        for (int j = 0; j < resultImage.width - 2; j++)
        {
            acc = 0;
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    acc += edgeDetect[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
                }
            }
            resultPixels.push_back(acc);
        }
    }
    resultImage.pixels = resultPixels;
    resultImage.width -= 2;
    resultImage.height -= 2;

    return resultImage;
}

PgmImage invert(PgmImage resultImage)
{
    for (int i = 0; i < resultImage.height; i++)
    {
        for (int j = 0; j < resultImage.width; j++)
        {
            resultImage.pixels[i * resultImage.width + j] = 255 - resultImage.pixels[i * resultImage.width + j];
        }
    }
    return resultImage;
}