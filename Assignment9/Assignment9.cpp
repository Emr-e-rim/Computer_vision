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
        // Check if image is loaded
        if (src.empty()) {
            printf(" Error opening image\n");
            return EXIT_FAILURE;
        }

        // Create blob detector
        std::vector<KeyPoint> keypoints;
        Ptr<SimpleBlobDetector> detector = SimpleBlobDetector::create();
        detector->detect(src, keypoints);

        // Draw blobs
        Mat src_with_keypoints;
        drawKeypoints(src, keypoints, src_with_keypoints, Scalar(255, 0, 0),
            DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

        // Show blobs
        imshow("keypoints", src_with_keypoints);
        waitKey();
        destroyAllWindows();
    }
}