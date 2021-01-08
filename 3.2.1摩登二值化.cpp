#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

void main()
{
	Mat srcImage = imread("D:\\2.png", 0);
	Mat result;
	threshold(srcImage, result, 100, 255, THRESH_BINARY);
	imshow("这是一个标题", result);
	waitKey(0);
}