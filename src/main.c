#include "utils.h"
#include "naive.h"
#include "edge.h"

int main() {
    cv::Mat img = cv::imread("assets/treecko-main.webp", cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    };

    bool useColor = true;

    edge(img);

    return 0;
}