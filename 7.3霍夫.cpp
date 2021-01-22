#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int Flag = 1; //标记滑动条是否有动作
void Thre_Track(int a, void* data)
{
	Flag = 1;
}

void minLineLength_Track(int a, void* data)
{
	Flag = 1;
}

void maxLineGap_Track(int a, void* data)
{
	Flag = 1;
}

int main()
{
	Mat src_Img, Binary_Img;
	vector<Vec4i> lines;
	char key;
	double step = 1, step_theta = CV_PI / 180;
	Point2f pt1, pt2;
	int Threshold = 39, minLineLength = 52, maxLineGap = 12;
	namedWindow("Tools");
	createTrackbar("投票结果阈值", "Tools", &Threshold, 200, Thre_Track);
	createTrackbar("最小线长", "Tools", &minLineLength, 200, minLineLength_Track);
	createTrackbar("最大点距", "Tools", &maxLineGap, 200, maxLineGap_Track);
	src_Img = imread("E:\\opencv\\pictures\\Part.jpg", 0);
	int width = src_Img.cols, height = src_Img.rows;
	cv::threshold(src_Img, Binary_Img, 100, 255, 0);
	Canny(Binary_Img, Binary_Img, 100, 200);
	imshow("二值化", Binary_Img);
	while (1) {
		if (Flag) {
			Flag = 0;
			Mat Show_Img;
			src_Img.copyTo(Show_Img);
			HoughLinesP(Binary_Img, lines, step, step_theta, Threshold, minLineLength, maxLineGap);
			if (lines.size())
				cout << "Find lines" << endl;
			for (int j = 0; j < lines.size(); j++) {
				Vec4i P = lines[j];
				pt1.x = P[0];
				pt1.y = P[1];
				pt2.x = P[2];
				pt2.y = P[3];
				cout << pt1 << pt2 << endl;
				line(Show_Img, pt1, pt2, Scalar(255, 255, 255), 2, CV_AA);
			}
			imshow("霍夫", Show_Img);
		}
		key = waitKey(1);
		if (key == ' ')
			break;
	}

}