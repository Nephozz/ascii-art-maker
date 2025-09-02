#ifndef NAIVE_H
#define NAIVE_H

#include "utils.h"

const std::string ASCII_CHARS = " .:coPO?@#";

std::vector<std::vector<std::string>> generateNaive(cv::Mat img, int asciiWidth, bool useColor);

#endif