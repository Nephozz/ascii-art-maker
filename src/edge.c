#include "edge.h"

char angleToAscii(float angle) {
    angle = fmod(angle, 180.0f);
    if (angle < 22.5 || angle >= 157.5) return '-';
    if (angle < 67.5) return '/';
    if (angle < 112.5) return '|';
    return '\\';
}

void edge(cv::Mat img) {
    cv::Mat blur1, blur2;
    double sigma1 = 1.0;
    double sigma2 = 4.0;

    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);

    cv::GaussianBlur(img, blur1, cv::Size(0, 0), sigma1);
    cv::GaussianBlur(img, blur2, cv::Size(0, 0), sigma2);
    cv::Mat dog = blur1 - blur2;

    cv::Mat gradX, gradY, sobel;
    cv::Sobel(dog, gradX, CV_32F, 1, 0, 3);
    cv::Sobel(dog, gradY, CV_32F, 0, 1, 3);
    
    cv::Mat magnitude, angle;
    cv::cartToPolar(gradX, gradY, magnitude, angle, true);

    cv::resize(img, img, cv::Size(img.cols / ASCII_WIDTH, img.rows / ASCII_WIDTH), 0, 0, cv::INTER_AREA);
    cv::resize(magnitude, magnitude, img.size());
    cv::resize(angle, angle, img.size());

    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            float mag = magnitude.at<float>(y,x);
            char c = (mag > 50) ? angleToAscii(angle.at<float>(y,x)) : ' ';

            std::cout << c;
        }
        std::cout << "\033[0m" << std::endl;
    }
}