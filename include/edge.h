#ifndef EDGE_H
#define EDGE_H

#include "utils.h"

void edgeTerm(cv::Mat img);

std::vector<std::vector<char>> generateEdge(cv::Mat img);

#endif