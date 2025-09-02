#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

#define ASCII_WIDTH 8

const std::string ASCII_CHARS = " .:-=+*#%@";

char luminanceToAscii(uchar pixelValue) {
    int index = (pixelValue * (ASCII_CHARS.size() - 1)) / 255;
    return ASCII_CHARS[index];
}

std::string rgbToAnsi(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

int main() {
    cv::Mat img = cv::imread("assets/treecko-main.webp", cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    };

    cv::resize(img, img, cv::Size(img.cols / ASCII_WIDTH, img.rows / ASCII_WIDTH), 0, 0, cv::INTER_AREA);

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    for (int i = 0; i < imgGray.rows; i++) {
        for (int j = 0; j < imgGray.cols; j++) {
            uchar pixelValue = imgGray.at<uchar>(i, j);
            char c = luminanceToAscii(pixelValue);

            cv::Vec3b color = img.at<cv::Vec3b>(i, j);
            int r = color[2];
            int g = color[1];
            int b = color[0];

            std::cout << rgbToAnsi(r, g, b) << c << c;
        }
        std::cout << "\033[0m" << std::endl;
    }

    return 0;
}