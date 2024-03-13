//! [includes]
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>

#include <iostream>
#include <sstream>
//! [includes]

using namespace std;
using namespace cv;

static void help()
{
    cout << "\n--------------------------------------------------------------------------" << endl
         << "This program shows how to scan image objects in OpenCV (cv::Mat). As use case"
         << " we take an input image and divide the native color palette (255) with the " << endl
         << "input. Shows C operator[] method, iterators and at function for on-the-fly item "
            "address calculation."
         << endl
         << "Usage:" << endl
         << "./how_to_scan_images <imageNameToUse> <divideWith> [G]" << endl
         << "if you add a G parameter the image is processed in gray scale" << endl
         << "--------------------------------------------------------------------------" << endl
         << endl;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* table);

int main(int argc, char const* argv[])
{
    /* code */
    return 0;
}
