#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat src_Mat, res_Mat, Matrix;
	float angle = -10.0, scale = 1;
	src_Mat = imread("D:\1.png");
	if (src_Mat.empty()) {
		cout << "empty" << endl;
		return -1;
	}
	Point2f center(src_Mat.cols * 0.5, src_Mat.rows * 0.5);
	Matrix = getRotationMatrix2D(center, angle, scale);
	warpAffine(src_Mat, res_Mat, Matrix, src_Mat.size());

	imshow("src", src_Mat);
	imshow("res", res_Mat);
	waitKey(0);
}