#include "stdio.h"
#include "opencv2/highgui/highgui.hpp"
#include "iostream"
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
//#include "opencv2/nonfree/nonfree.hpp"
//#include <opencv/cv.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc/types_c.h>

using namespace cv;
using namespace std;


void fastMatchTemplate(cv::Mat& srca,  // Imagen  de referencia
    cv::Mat& srcb,  // Imagen original
    cv::Mat& dst,   // Imagen teplate resultante
    int maxlevel)   // Numero de niveles
{
    std::vector<cv::Mat> refs, tpls, results;

    cv::buildPyramid(srca, refs, maxlevel);
    cv::buildPyramid(srcb, tpls, maxlevel);

    cv::Mat ref, tpl, res;

    for (int level = maxlevel; level >= 0; level--)
    {
        ref = refs[level];
        tpl = tpls[level];
        res = cv::Mat::zeros(ref.size() + cv::Size(1, 1) - tpl.size(), CV_32FC1);

        if (level == maxlevel)
            cv::matchTemplate(ref, tpl, res, CV_TM_CCORR_NORMED);
        else
        {
            cv::Mat mask;
            cv::pyrUp(results.back(), mask);

            cv::Mat mask8u;
            mask.convertTo(mask8u, CV_8U);

            std::vector<std::vector<cv::Point> > contours;
            cv::findContours(mask8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

            for (int i = 0; i < contours.size(); i++)
            {
                cv::Rect r = cv::boundingRect(contours[i]);

                cv::matchTemplate(
                    ref(r + (tpl.size() - cv::Size(1, 1))),
                    tpl,
                    res(r),
                    CV_TM_CCORR_NORMED
                );
            }
        }

        cv::threshold(res, res, 0.80, 1., CV_THRESH_TOZERO);
        results.push_back(res);
    }

    res.copyTo(dst);
}


int main()
{
    /*cv::Mat ref = cv::imread("C:\\Template_Matching_Original_Image.jpg");
    cv::Mat tpl = cv::imread("C:\\Template_Matching_Template_Image.jpg");*/
    Mat ref = cv::imread("C:\\Template_Matching_Original_Image.jpg");
    Mat tpl = cv::imread("C:\\Template_Matching_Template_Image.jpg");
    if (ref.empty() || tpl.empty())
    {
        cout << "Error reading file(s)!" << endl;
        return -1;
    }

    imshow("file", ref);
    imshow("template", tpl);

    Mat res_32f(ref.rows - tpl.rows + 1, ref.cols - tpl.cols + 1, CV_32FC1);
    matchTemplate(ref, tpl, res_32f, CV_TM_CCOEFF_NORMED);

    Mat res;
    res_32f.convertTo(res, CV_8U, 255.0);
    imshow("result", res);

    int size = ((tpl.cols + tpl.rows) / 4) * 2 + 1; //force size to be odd
    adaptiveThreshold(res, res, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, size, -128);
    imshow("result_thresh", res);

    while (true)
    {
        double minval, maxval, threshold = 0.8;
        Point minloc, maxloc;
        minMaxLoc(res, &minval, &maxval, &minloc, &maxloc);

        if (maxval >= threshold)
        {
            rectangle(ref, maxloc, Point(maxloc.x + tpl.cols, maxloc.y + tpl.rows), CV_RGB(0, 255, 0), 2);
            floodFill(res, maxloc, 0); //mark drawn blob
        }
        else
            break;
    }

    imshow("final", ref);
    waitKey(0);

    return 0;
}