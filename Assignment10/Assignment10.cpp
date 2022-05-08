/*
  CURRENT WARNING: "libpng warning: iCCP: known incorrect sRGB profile" only for
  dice 6. This is the only image without circles.
*/

#include "iostream"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main() {
    for (int j = 1; j < 7; j++) {
        string path =
            "PATH\\TO\\dice-";
        path += to_string(j);
        path += "-md.png";
        Mat src = imread(path, IMREAD_COLOR);
        // Check if image is loaded fine
        if (src.empty()) {
            printf(" Error opening image\n");
            return EXIT_FAILURE;
        }

        Mat gray;
        cvtColor(src, gray, COLOR_BGR2GRAY);
        medianBlur(gray, gray, 5);

        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 16, 100, 30, 1,
            30);

        size_t i;
        for (i = 0; i < circles.size(); i++) {
            Vec3i c = circles[i];
            Point center = Point(c[0], c[1]);
            int radius = c[2];
            circle(src, center, radius, Scalar(255, 0, 0), 2, LINE_AA);
        }

        printf("Dice %d: circles: %zu\n", j, i);
        string dice = "Dice ";
        dice += to_string(j);
        dice += " detected circles";
        imshow(dice, src);
        waitKey();
        destroyAllWindows();
    }
    return 0;
}