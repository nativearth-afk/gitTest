#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat src_Img, result_Img, rot;
	double angle, scale;
	Rect bbox;
	src_Img = imread("E:\\opencv\\pictures\\Buliding_Class.jpg");
	angle = 60;
	scale = 1;
	Point2f center(src_Img.cols / 2.0, src_Img.rows / 2.0);
	rot = getRotationMatrix2D(center, angle, scale);
	bbox = RotatedRect(center, src_Img.size(), angle).boundingRect();
	rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
	rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;
	//cout << rot << endl;
	warpAffine(src_Img, result_Img, rot, bbox.size());
	imshow("src", src_Img);
	imshow("?res", result_Img);
	waitKey(0);
}