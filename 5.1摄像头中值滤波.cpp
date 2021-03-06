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
		int ksize = 13;
		bool rSuccess = cap.read(frame);
		if (!rSuccess)
		{
			std::cout << "不能从视频文件读取" << std::endl;
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