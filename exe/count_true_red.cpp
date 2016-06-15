#include <iostream>
#include "opencv2/opencv.hpp"

int main(int argc, char const* argv[])
{
    cv::Mat image;   
    cv::Mat mask;

    mask = cv::imread(argv[1], 0);
    //cv::imshow("mask", mask);
    std::cout << "{";
    for (int i = 0; i < argc - 2; i++){
        char const* filename = argv[i + 2];
        int len = strlen(filename);

        int j;
        for (j = len - 1; filename[j] != '/'; j--);
        j++;

        int count = 0;
        image = cv::imread(filename);

        std::ostringstream oss;
        std::cout << "\"" << filename + j << "\":";
        std::cout << "[";

        bool first = true;
        for (int y = 0; y < image.rows; y++){
            for (int x = 0; x < image.cols; x++){
                if (mask.data[y * image.cols + x] != 0 && image.data[(y * image.cols + x) * 3 + 2] == 255 && image.data[(y * image.cols + x) * 3 + 1] == 0 && image.data[(y * image.cols + x) * 3 + 0] == 0){
                    if (first) {
                        std::cout << "[" << x << "," << y << "]";
                        first = false;
                    }
                    else {
                        std::cout << ",[" << x << "," << y << "]";
                    }
                }
            }
        }
        std::cout << "],";
    }
    std::cout << "}";


    return 0;
}
