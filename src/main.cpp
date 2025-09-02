#include "utils.h"
#include "naive.h"
#include "edge.h"

int main(int argc, char** argv) {
    int asciiWidth = 4;
    bool useColor = true;
    if (argc > 1) {
        asciiWidth = std::stoi(argv[1]);
    }

    cv::Mat img = cv::imread("assets/treecko-main.webp", cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Error: Could not load image" << std::endl;
        return 1;
    };


    std::vector<std::vector<std::string>> naiveAscii = generateNaive(img.clone(), asciiWidth, useColor);
    std::vector<std::vector<char>> edgeAscii = generateEdge(img.clone(), asciiWidth);

    for (size_t y = 0; y < naiveAscii.size(); y++) {
        for (size_t x = 0; x < naiveAscii[y].size(); x++) {
            char e = edgeAscii[y][x];
            if (e != ' ') {
                std::cout << "\033[0m";
                if (e == '-') std::cout << e << e;
                else std::cout << e << " ";
            } else {
                std::cout << naiveAscii[y][x];
            }
        }
        std::cout << "\033[0m" << std::endl;

    }

    return 0;
}