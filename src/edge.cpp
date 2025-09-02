#include "edge.h"

float quantizeAngle(float angle) {
    angle = fmod(angle, 180.0f);

    if (angle < 22.5 || angle >= 157.5) return 0;   // '-'
    if (angle < 67.5) return 1;                     // '/'
    if (angle < 112.5) return 2;                    // '|'
    return 3;                                       // '\'
}

char angleToAscii(int qAngle) {
    switch(qAngle) {
        case 0: return '-';
        case 1: return '/';
        case 2: return '|';
        case 3: return '\\';
    }
    return ' ';
}

void downscaleEdges(const cv::Mat& magFull, const cv::Mat& angleFull,
                    cv::Mat& magSmall, cv::Mat& angleSmall,
                    int asciiWidth, int asciiHeight) {

    int blockW = magFull.cols / asciiWidth;
    int blockH = magFull.rows / asciiHeight;

    int minPixel = static_cast<int>(0.2 * asciiHeight * asciiWidth);

    magSmall.create(blockH, blockW, CV_32F);
    angleSmall.create(blockH, blockW, CV_8U);

    cv::Mat quantized(angleFull.size(), CV_8U);
    for (int y = 0; y < angleFull.rows; y++) {
        for (int x = 0; x < angleFull.cols; x++) {
            quantized.at<uchar>(y,x) = static_cast<uchar>(quantizeAngle(angleFull.at<float>(y,x)));
        }
    }

    for (int by = 0; by < blockH; by++) {
        for (int bx = 0; bx < blockW; bx++) {
            int x0 = bx * asciiWidth;
            int y0 = by * asciiHeight;
            int x1 = std::min(x0 + asciiWidth, magFull.cols);
            int y1 = std::min(y0 + asciiHeight, magFull.rows);

            cv::Mat blockMag = magFull(cv::Range(y0, y1), cv::Range(x0, x1));
            cv::Mat blockAngle = quantized(cv::Range(y0, y1), cv::Range(x0, x1));

            double minVal, maxVal;
            cv::Point maxLoc;
            cv::minMaxLoc(blockMag, &minVal, &maxVal, nullptr, &maxLoc);

            int counts[4] = {0,0,0,0};
            for (int y = 0; y < blockAngle.rows; y++) {
                for (int x = 0; x < blockAngle.cols; x++) {
                    int q = blockAngle.at<uchar>(y,x);
                    counts[q]++;
                }
            }
            int modeAngle = std::distance(counts, std::max_element(counts, counts+4));
            
            if (counts[modeAngle] < minPixel) {
                magSmall.at<float>(by,bx) = 0.0f;
            } else {
                magSmall.at<float>(by,bx) = static_cast<float>(maxVal);
            }

            angleSmall.at<uchar>(by,bx) = static_cast<uchar>(modeAngle);
        }
    }
}

std::vector<std::vector<char>> generateEdge(cv::Mat img, int asciiWidth) {
    std::vector<std::vector<char>> edgeAscii;

    cv::Mat blur1, blur2;
    double sigma, k;
    sigma = 1.0;
    k = 3.0;

    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(img, blur1, cv::Size(0, 0), sigma);
    cv::GaussianBlur(img, blur2, cv::Size(0, 0), k * sigma);
    cv::Mat dog = blur1 - blur2;

    double dogThreshold = 15.0;
    cv::threshold(dog, dog, dogThreshold, 255, cv::THRESH_TOZERO);

    cv::imshow("DoG", dog);
    cv::waitKey(0);

    cv::Mat gradX, gradY, sobel;
    cv::Sobel(dog, gradX, CV_32F, 1, 0, 3);
    cv::Sobel(dog, gradY, CV_32F, 0, 1, 3);
    
    cv::Mat magnitude, angle;
    cv::cartToPolar(gradX, gradY, magnitude, angle, true);

    cv::Mat magSmall, angleSmall;
    downscaleEdges(magnitude, angle, magSmall, angleSmall, asciiWidth, asciiWidth);

    for (int y = 0; y < magSmall.rows; y++) {
        std::vector<char> row;
        for (int x = 0; x < magSmall.cols; x++) {
            float mag = magSmall.at<float>(y,x);
            char c = (mag > 10) ? angleToAscii(angleSmall.at<uchar>(y,x)) : ' ';
            row.push_back(c);
        }
        edgeAscii.push_back(row);
    }
    return edgeAscii;
}