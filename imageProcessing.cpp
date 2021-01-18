#include "pgmImage.h"

const float edgeDetect1K[3][3] = {
    {1, 0, -1},
    {0, 0, 0},
    {-1, 0, 1}};

const float edgeDetect2K[3][3] = {
    {0, -1, 0},
    {-1, 4, -1},
    {0, -1, 0}};

const float edgeDetect3K[3][3] = {
    {-1, -1, -1},
    {-1, 8, -1},
    {-1, -1, -1}};

const float sharpenK[3][3] = {
    {0, -1, 0},
    {-1, 5, -1},
    {0, -1, 0}};

const float embossK[3][3] = {
    {-2, -1, 0},
    {-1, 1, 1},
    {0, 1, 2}};

const float boxBlurK[3][3] = {
    {1. / 9, 1. / 9, 1. / 9},
    {1. / 9, 1. / 9, 1. / 9},
    {1. / 9, 1. / 9, 1. / 9}};

const float gaussian3K[3][3] = {
    {1. / 16, 2. / 16, 1. / 16},
    {2. / 16, 4. / 16, 2. / 16},
    {1. / 16, 2. / 16, 1. / 16}};

const float gaussian5K[5][5] = {
    {1. / 256, 4. / 256, 6. / 256, 4. / 256, 1. / 256},
    {4. / 256, 16. / 256, 24. / 256, 16. / 256, 4. / 256},
    {6. / 256, 24. / 256, 36. / 256, 24. / 256, 6. / 256},
    {4. / 256, 16. / 256, 24. / 256, 16. / 256, 4. / 256},
    {1. / 256, 4. / 256, 6. / 256, 4. / 256, 1. / 256},
};

PgmImage edgeDetect1(PgmImage &resultImage)
{
    vector<float> resultPixels;
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
                    acc += edgeDetect1K[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
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

PgmImage edgeDetect2(PgmImage &resultImage)
{
    vector<float> resultPixels;
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
                    acc += edgeDetect2K[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
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

PgmImage edgeDetect3(PgmImage &resultImage)
{
    vector<float> resultPixels;
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
                    acc += edgeDetect3K[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
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

PgmImage sharpen(PgmImage &resultImage)
{
    vector<float> resultPixels;
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
                    acc += sharpenK[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
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

PgmImage boxBlur(PgmImage &resultImage)
{
    vector<float> resultPixels;
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
                    acc += boxBlurK[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
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

PgmImage gaussian3(PgmImage &resultImage)
{
    vector<float> resultPixels;
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
                    acc += gaussian3K[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
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

PgmImage gaussian5(PgmImage &resultImage)
{
    vector<float> resultPixels;
    float acc;

    for (int i = 0; i < resultImage.height - 4; i++)
    {
        for (int j = 0; j < resultImage.width - 4; j++)
        {
            acc = 0;
            for (int k = 0; k < 5; k++)
            {
                for (int l = 0; l < 5; l++)
                {
                    acc += gaussian5K[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
                }
            }
            resultPixels.push_back(acc);
        }
    }
    resultImage.pixels = resultPixels;
    resultImage.width -= 4;
    resultImage.height -= 4;

    return resultImage;
}

PgmImage emboss(PgmImage &resultImage)
{
    vector<float> resultPixels;
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
                    acc += embossK[k][l] * resultImage.pixels[i * resultImage.width + k * resultImage.width + l + j];
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

PgmImage invert(PgmImage &resultImage)
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
