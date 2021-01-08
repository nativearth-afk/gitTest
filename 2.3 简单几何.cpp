#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
void main()
{
	Mat dispMat = imread("D:\\2.png");
	cv::Point pt;
	pt.x = 100;
	pt.y = 100;
	circle(dispMat, pt, 100, CV_RGB(255, 0, 0), 2, 8, 0);
	cv::Point pt1;
	pt1.x = 100;
	pt1.y = 100;
	cv::Point pt2;
	pt2.x = 500;
	pt2.y = 500;
	line(dispMat, pt1, pt2, CV_RGB(255, 0, 0), 4, 8, 0);
	cv::Rect rect;
	rect.x = 100;
	rect.y = 100;
	rect.width = 70;
	rect.height = 70;
	rectangle(dispMat, rect, CV_RGB(255, 0, 0), 1, 8, 0);
	imshow("这是一个标题", dispMat);
	waitKey(0);
}