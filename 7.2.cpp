#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Thre_Track(int a, void* data)
{
	;
}

int main()
{
	Mat src_Img, Binary_Img;
	Mat lines;
	char key;
	double step = 1, step_theta = CV_PI / 180;
	Point pt1, pt2;
	int Threshold = 93, last_Threshold = 0;
	namedWindow("Tools");
	createTrackbar("Threshold", "Tools", &Threshold, 200, Thre_Track);
	src_Img = imread("E:\\opencv\\pictures\\Part.jpg", 0);
	cv::threshold(src_Img, Binary_Img, 100, 255, 0);
	Canny(Binary_Img, Binary_Img, 100, 200);
	imshow("Binary_Img", Binary_Img);
	while (1) {
		if (Threshold != last_Threshold) {
			Mat Show_Img;
			src_Img.copyTo(Show_Img);
			last_Threshold = Threshold;
			HoughLines(Binary_Img, lines, step, step_theta, Threshold);
			int Num = lines.rows;
			for (int j = 0; j < Num; j++) {
				float* data = lines.ptr<float>(j);
				float rho, theta;
				rho = data[0];
				theta = data[1];
				double a = cos(theta);
				double b = sin(theta);
				double x0 = a * rho;
				double y0 = b * rho;
				pt1.x = saturate_cast<int>(x0 + 1000 * (-b));
				pt1.y = saturate_cast<int>(y0 + 1000 * (a));
				pt2.x = saturate_cast<int>(x0 - 1000 * (-b));
				pt2.y = saturate_cast<int>(y0 - 1000 * (a));
				line(Show_Img, pt1, pt2, Scalar(255, 255, 255), 1, CV_AA);
			}
			imshow("show", Show_Img);
		}
		key = waitKey(1);
		if (key == ' ')
			break;
	}

}