#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void main()
{
	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened())
	{
		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
		return;
	}

	Mat frame;
	while (1)
	{
		cap.read(frame);

		Mat sobel_Mat;
		Sobel(frame, sobel_Mat, -1, 1, 0);

		imshow("frame", frame);
		imshow("sobel_Mat", sobel_Mat);
		waitKey(30);
	}
}