#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int num;

int main()
{
    for (int i = 0; i < 22; i++) {
        string file = "PATH\\TO\\Fuses\\Fuse ";
        file += to_string(i);
        file += ".bmp";

        String temp = "PATH\\TO\\Fuses\\Fuse1.jpg";

        Mat input = cv::imread(file);

        Mat gray;
        cvtColor(input, gray, cv::COLOR_BGRA2GRAY);

        Mat templ = cv::imread(temp);

        Mat img = input;
        Mat result;

        // Create result matrix
        int result_cols = img.cols - templ.cols + 1;
        int result_rows = img.rows - templ.rows + 1;

        result.create(result_cols, result_rows, CV_32FC1);

        int match_method = TM_CCOEFF_NORMED;

        matchTemplate(img, templ, result, match_method);

        double minVal; double maxVal; Point minLoc; Point maxLoc;
        Point matchLoc;

        minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
        matchLoc = maxLoc;

        double minMatchQuality = 0.73;
        if (maxVal > minMatchQuality) {
            cv::rectangle(input, matchLoc, cv::Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(255, 0, 0), 2, 8, 0);
            cv::rectangle(result, matchLoc, cv::Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(255, 0, 0), 2, 8, 0);
            num++;
        }

        string fuse = "Fuse: ";
        fuse += to_string(i);

        cv::imshow(fuse, input);
        cv::imshow("Template", templ);

        cv::waitKey(0);
        destroyAllWindows();
    }

    cout << endl;
    cout << "There are " << num << " good fuses.";
    cout << endl;

    return 0;
}