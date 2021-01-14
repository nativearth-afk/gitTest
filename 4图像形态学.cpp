#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

void main()
{
	Mat srcImage = imread("D:\\coin.jpg", 0);
	Mat result;
	threshold(srcImage, result, 87, 255, THRESH_BINARY);

	Mat out1, out2, out3;
	Size ksize;
	ksize.width = 6;
	ksize.height = 6;
	Mat kernel = getStructuringElement(MORPH_RECT, ksize);
	erode(result, out1, kernel);
	imshow("∏Ø ¥", out1);
	dilate(result, out2, kernel);
	imshow("≈Ú’Õ", out2);

	imshow("original", result);

	waitKey(0);
}