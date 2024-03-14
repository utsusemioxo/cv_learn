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
    help();
    if (argc < 3)
    {
        cout << "Not enough parameters" << endl;
        return -1;
    }

    Mat I, J;
    if (argc == 4 && !strcmp(argv[3], "G"))
        I = imread(argv[1], IMREAD_GRAYSCALE);
    else
        I = imread(argv[1], IMREAD_COLOR);

    if (I.empty())
    {
        cout << "The image" << argv[1] << " could not be loaded." << endl;
        return -1;
    }

    //! [dividewith]
    int divideWith = 0; // convert our input string to number - C++ style
    stringstream s;
    s << argv[2];
    s >> divideWith;
    if (!s || !divideWith)
    {
        cout << "Invalid number entered for dividing. " << endl;
        return -1;
    }

    uchar table[256];
    for (int i = 0; i < 256; i++)
    {
        table[i] = (uchar)(divideWith * (i / divideWith));
    }

    //! [dividewith]

    const int times = 100;
    double t;

    {
        t = (double)getTickCount();

        for (int i = 0; i < times; ++i)
        {
            Mat clone_i = I.clone();
            J = ScanImageAndReduceC(clone_i, table);
        }

        t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
        t /= times;

        cout << "Time of reducing with the C operator [] (averaged for " << times << " runs): " << t
             << " milliseconds." << endl;
    }
    {
        t = (double)getTickCount();

        for (int i = 0; i < times; ++i)
        {
            Mat clone_i = I.clone();
            J = ScanImageAndReduceIterator(clone_i, table);
        }

        t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
        t /= times;

        cout << "Time of reducing with the iterator (averaged for " << times << " runs): " << t
             << " milliseconds." << endl;
    }
    {
        t = (double)getTickCount();

        for (int i = 0; i < times; ++i)
        {
            Mat clone_i = I.clone();
            J = ScanImageAndReduceRandomAccess(clone_i, table);
        }

        t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
        t /= times;

        cout << "Time of reducing with the on-the-fly address generation (averaged for " << times
             << " runs): " << t << " milliseconds." << endl;
    }
    {
        Mat lookUpTable(1, 256, CV_8U);
        uchar* p = lookUpTable.ptr();
        for (int i = 0; i < 256; ++i)
        {
            p[i] = table[i];
        }

        t = (double)getTickCount();

        t = 1000 * ((double)getTickCount() - t) / getTickFrequency();

        LUT(I, lookUpTable, J);

        t /= times;
        cout << "Time of reducing with the cv::LUT function (averaged for " << times
             << " runs): " << t << " milliseconds." << endl;
    }
    return 0;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table)
{
    CV_Assert(I.depth() == CV_8U);

    int channels = I.channels();

    int nRows = I.rows;
    int nCols = I.cols * channels;

    if (I.isContinuous())
    {
        nCols = nCols * nRows;
        nRows = 1;
    }

    uchar* p;
    for (int i = 0; i < nRows; i++)
    {
        p = I.ptr<uchar>(i);
        for (int j = 0; j < nCols; j++)
        {
            p[j] = table[p[j]];
        }
    }

    return I;
}

Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);

    const int channels = I.channels();

    switch (channels)
    {
        case 1:
        {
            MatIterator_<uchar> it, end;
            for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
            {
                *it = table[*it];
            }
        }
        break;

        case 3:
        {
            MatIterator_<Vec3b> it, end;
            for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
            {
                (*it)[0] = table[(*it)[0]];
                (*it)[1] = table[(*it)[1]];
                (*it)[2] = table[(*it)[2]];
            }
        }
        break;

        default:
            break;
    }
    return I;
}

Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* table)
{
    // accept only char type matrices
    CV_Assert(I.depth() == CV_8U);
    const int channels = I.channels();
    switch (channels)
    {
        case 1:
        {
            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j)
                    I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
            break;
        }
        case 3:
        {
            Mat_<Vec3b> _I = I;
            for (int i = 0; i < I.rows; ++i)
                for (int j = 0; j < I.cols; ++j)
                {
                    _I(i, j)[0] = table[_I(i, j)[0]];
                    _I(i, j)[1] = table[_I(i, j)[1]];
                    _I(i, j)[2] = table[_I(i, j)[2]];
                }
            I = _I;
            break;
        }
    }
    return I;
}