#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat Binary_Img, Gray_Img, kernel;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	Size size;
	size.height = 3;
	size.width = 3;
	int n = 0;
	RotatedRect rbox;
	Mat src_Img = imread("D:\\pin.jpg");
	cvtColor(src_Img, Gray_Img, CV_BGR2GRAY);
	threshold(Gray_Img, Binary_Img, 150, 255, 0);
	kernel = getStructuringElement(MORPH_RECT, size);
	morphologyEx(Binary_Img, Binary_Img, MORPH_OPEN, kernel);
	imshow("二值化", Binary_Img);
	waitKey(1);
	findContours(Binary_Img, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
	cout << contours.size() << endl;
	for (n = 0; n < contours.size(); n++) {
		if (contourArea(contours[n]) > 120) {
			rbox = minAreaRect(contours[n]);
			int Long = max(rbox.size.width, rbox.size.height);
			int Short = min(rbox.size.width, rbox.size.height);
			double C = (double)Short / (double)Long;
			if (C > 0.8) {
				drawContours(src_Img, contours, n, Scalar(0, 153, 255), 2, 8);
				rectangle(src_Img, rbox.boundingRect(), Scalar(110, 160, 39), 2);
			}
		}
		
	}
	imshow("结果", src_Img);
	waitKey(0);
	return 0;
}