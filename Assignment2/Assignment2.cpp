#include "iostream"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main() {
    for (int j = 1; j < 7; j++) {
        string path =
            "PATH\\TO\\bracket";
        path += to_string(j);
        path += ".jpg";
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

        const Point c1 = Point(circles[0][0], circles[0][1]);
        const Point c2 = Point(circles[1][0], circles[1][1]);
        line(src, c1, c2, Scalar(255, 0, 0), 2);

        // Calculate distance, and put in input image.
        double dist = norm(c1 - c2);
        putText(src, to_string(dist),
            Point((c1.x + c2.x) / 2 + 20, (c1.y + c2.y) / 2 + 20),
            FONT_HERSHEY_COMPLEX, 1.0, Scalar(255, 0, 0));

        printf("Distance for bracket %d: %f\n", j, dist);
        string distance = "Bracket";
        distance += to_string(j);
        imshow(distance, src);
        waitKey();
        destroyAllWindows();
    }
    return 0;
}