#ifndef NAIVE_H
#define NAIVE_H

#include "utils.h"

const std::string ASCII_CHARS = " .:-=+*#%@";

char luminanceToAscii(uchar pixelValue);

std::string rgbToAnsi(int r, int g, int b);

void naive(cv::Mat img, bool useColor);

#endif