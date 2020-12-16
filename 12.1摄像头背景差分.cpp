#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;


int main()
{
	Mat bgMat;
	Mat frame;
	Mat subMat;
	Mat bny_subMat;
	VideoCapture cap;
	cap.open(0);
	int cnt = 0;

	while (1) {

		cap.read(frame);
		cvtColor(frame, frame, COLOR_BGR2GRAY);


		if (cnt == 0) {
			frame.copyTo(bgMat);
			cnt++;
		}
		else {
			//第二帧开始背景差分
			absdiff(frame, bgMat, subMat);
			threshold(subMat, bny_subMat, 50, 255, CV_THRESH_BINARY);

			imshow("b_subMat", bny_subMat);
			imshow("subMat", subMat);
			waitKey(30);
		}

	}

	return(0);
}