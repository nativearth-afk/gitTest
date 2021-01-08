#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main()
{
	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened())
	{
		std::cout << "���ܴ���Ƶ�ļ�" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		cv::Mat result;
		int ksize = 13;
		bool rSuccess = cap.read(frame);
		if (!rSuccess)
		{
			std::cout << "���ܴ���Ƶ�ļ���ȡ" << std::endl;
			break;
		}
		else
		{
			medianBlur(frame, result, ksize);
			cv::imshow("frame", frame);
			cv::imshow("result", result);
		}
		waitKey(30);
	}
	return 0;
}