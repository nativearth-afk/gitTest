#include<opencv2/opencv.hpp>
#include<iostream>
#include<stdio.h>
using namespace cv;

CV_EXPORTS int creatTrackbar(const String& trackbarname,
	const String& winname, int* value, int count,
	TrackbarCallback onChange = 0,
	void* userdata = 0);
std::string window_name = "binaryMat";
void threshod_Mat(int th, void* data)
{

	Mat src = *(Mat*)(data);

	Mat dst;
	//∂˛÷µªØ
	threshold(src, dst, th, 255, 0);
	imshow(window_name, dst);
}
int main()
{

	Mat srcMat;
	Mat gryMat;
	int lowTh = 30;
	int maxTh = 255;

	srcMat = imread("D:\\2.png");
	if (!srcMat.data)//≈–∂œÕºœÒ «∑Ò‘ÿ»Î
	{
		cout << "ÕºœÒ‘ÿ»Î ß∞‹" << endl;
		return 0;
	}
	//
	cvtColor(srcMat, gryMat, CV_BGR2GRAY);
	imshow(window_name, gryMat);
	createTrackbar("threshold", window_name, &lowTh, maxTh, threshod_Mat, &gryMat);
	waitKey(0);

	return 0;
}