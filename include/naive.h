#ifndef NAIVE_H
#define NAIVE_H

#include "utils.h"

const std::string ASCII_CHARS = " .:-=+*#%@";

void naiveTerm(cv::Mat img, bool useColor);

std::vector<std::vector<std::string>> generateNaive(cv::Mat img, bool useColor);

#endif