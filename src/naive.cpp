#include "naive.h"

char luminanceToAscii(uchar pixelValue) {
    int index = (pixelValue * (ASCII_CHARS.size() - 1)) / 255;
    return ASCII_CHARS[index];
}

std::string rgbToAnsi(int r, int g, int b) {
    return "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
}

std::vector<std::vector<std::string>> generateNaive(cv::Mat img, int asciiWidth, bool useColor) {
    std::vector<std::vector<std::string>> naiveAscii;

    cv::resize(img, img, cv::Size(img.cols / asciiWidth, img.rows / asciiWidth), 0, 0, cv::INTER_AREA);

    cv::Mat imgGray;
    cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

    for (int i = 0; i < imgGray.rows; i++) {
        std::vector<std::string> row;
        for (int j = 0; j < imgGray.cols; j++) {
            uchar pixelValue = imgGray.at<uchar>(i, j);
            char c = luminanceToAscii(pixelValue);

            if (useColor) {
                cv::Vec3b color = img.at<cv::Vec3b>(i, j);
                int r = color[2];
                int g = color[1];
                int b = color[0];

                row.push_back(rgbToAnsi(r, g, b) + c + c);
            } else {
                row.push_back(std::string(2, c));
            }
        }
        naiveAscii.push_back(row);
    }

    return naiveAscii;
}