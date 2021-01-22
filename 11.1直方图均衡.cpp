#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat src, result, B, G, R;
	vector<Mat> channels;
	src = imread("D:\\DARK.png");
	split(src, channels);
	equalizeHist(channels[0], channels[0]);
	equalizeHist(channels[1], channels[1]);
	equalizeHist(channels[2], channels[2]);
	merge(channels, result);
	imshow("DARK", src);
	imshow("RST", result);
	waitKey(0);
	return 0;
}