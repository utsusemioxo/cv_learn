//! [includes]
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"

#include <iostream>

using namespace cv;
//! [includes]

int main()
{
    //! [imread]
    std::string image_path =
        samples::findFile("C:/Users/niuti/Documents/Dev/cv_learn/image/Ditto_Concept_Photo_29.jpg");
    Mat img = imread(image_path, IMREAD_COLOR);
    //! [imread]

    //! [empty]
    if (img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    //! [empty]

    //! [imshow]
    imshow("Display window", img);
    int k = waitKey(0);
    //! [imshow]

    //! [imsave]
    if (k == 's')
    {
        imwrite("C:/Users/niuti/Documents/Dev/cv_learn/image/Ditto_Concept_Photo_29.jpg", img);
    }
    //! [imsave]

    return 0;
}