#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

#define ASCII_WIDTH 8

const std::string ASCII_CHARS = "@%#*+=-:. ";
const std::string REVERSED_ASCII_CHARS = " .:-=+*#%@";

char luminanceToAscii(uchar pixelValue) {
    int index = (pixelValue * (REVERSED_ASCII_CHARS.size() - 1)) / 255;
    return REVERSED_ASCII_CHARS[index];
}

int main() {
    cv::Mat img = cv::imread("assets/treecko-main.webp", cv::IMREAD_UNCHANGED);
    if (img.empty()) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    };

    cv::resize(img, img, cv::Size(img.cols / ASCII_WIDTH, img.rows / ASCII_WIDTH), 0, 0, cv::INTER_AREA);
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            uchar pixelValue = img.at<uchar>(i, j);
            char c = luminanceToAscii(pixelValue);
            std::cout << c << c;
        }
        std::cout << std::endl;
    }

    return 0;
}