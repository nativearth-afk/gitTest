#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

void main()
{
	Mat srcImage = imread("D:\\2.png"，0);

	imshow("这是一个标题", srcImage);
	waitKey(0);
}