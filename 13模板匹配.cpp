#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	VideoCapture cap;
	Mat frame, tempImg, return_Img;
	int match_method = 0;
	cap.open(0);
	if (cap.isOpened()) {
		cout << "打开摄像头成功" << endl;
	}
	else {
		cout << "未能打开摄像头" << endl;
	}
	while (cap.isOpened()) {
		bool ret = cap.read(frame);
		if (ret) {
			imshow("frame", frame);
			char key = waitKey(30);
			if (key == ' ') {
				Rect2d r;
				r = selectROI(frame, true);
				return_Img = frame(r);
				return_Img.copyTo(tempImg);
				destroyAllWindows();
				imshow("Selected", tempImg);
				waitKey(20);
				break;
			}
		}
	}
	while (cap.isOpened()) {
		bool ret = cap.read(frame);
		if (ret) {
			Mat resultMat;
			matchTemplate(frame, tempImg, resultMat, match_method);
			normalize(resultMat, resultMat, 0, 1, NORM_MINMAX, -1, Mat());
			double minVal, maxVal;
			Point  minLoc, maxLoc;
			minMaxLoc(resultMat, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
			Rect Match_rect;
			Match_rect.x = minLoc.x;
			Match_rect.y = minLoc.y;
			Match_rect.width = tempImg.cols;
			Match_rect.height = tempImg.rows;
			rectangle(frame, Match_rect, Scalar(82, 144, 67), 8);
			imshow("show", frame);
			char key = waitKey(10);
			if (key == ' ')
				break;
		}
	}
}