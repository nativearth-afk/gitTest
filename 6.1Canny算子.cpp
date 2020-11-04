#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	cv::Mat dstMat;
	cv::Mat gray;
	cv::Mat srcMat = cv::imread("D:\\1.png");
	cvtColor(dstMat, gray, CV_BGR2GRAY);
	Canny(gray, result, 150, 100);
	cv::imshow("src", srcMat);
	cv::imshow("res", dstMat);
	waitKey(0);
	return 0;
}