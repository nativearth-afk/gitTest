#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

void main()
{
	Mat srcImage = imread("D:\\2.png", 0);
	Mat result;
	int C = 5;
	adaptiveThreshold(srcImage, result, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY_INV, 25, 10);
	imshow("����һ������", result);
	waitKey(0);
}