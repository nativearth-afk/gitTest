#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
int main()
{
	VideoCapture cap;

	cap.open(0);

	if (!cap.isOpened())
	{
		std::cout << "不能打开视频文件" << std::endl;
		return -1;
	}
	double fps = cap.get(CAP_PROP_FPS);
	std::cout << "fps" << fps << std::endl;
	while (1)
	{
		cv::Mat frame;
		cv::Mat result;
		cv::Size ksize;
		ksize.width = 9;
		ksize.height = 9;
		double sigmaY = 0;
		double sigmaX = 5;
		bool rSuccess = cap.read(frame);
		if (!rSuccess)
		{
			std::cout << "不能从视频文件读取" << std::endl;
			break;
		}
		else
		{
			cv::GaussianBlur(frame, result, ksize, sigmaX, sigmaY, BORDER_DEFAULT);
			cv::imshow("frame", frame);
			cv::imshow("result", result);
		}
		waitKey(30);
	}
	return 0;
}