#include "iostream"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main() {
    for (int i = 1; i < 3; i++) {
        //Read image
        string path;
        if (i == 1) {
            path =
                "PATH\\TO\\300-JPEG-artifacts-original.bmp";
        }
        else if (i == 2) {
            path =
                "PATH\\TO\\jpeg-compression-artifacts.bmp";
        }
        Mat image = imread(path);

        if (image.empty()) {
            printf(" Error opening image\n");
            return EXIT_FAILURE;
        }

        // Filter noise
        Mat median_blurred;
        medianBlur(image, median_blurred, 5);

        // Show images
        imshow("Original", image);
        imshow("Filtered", median_blurred);

        waitKey(0);
        destroyAllWindows();
    }
    return 0;
}