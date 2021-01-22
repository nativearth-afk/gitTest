#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>

#define N				1000
#define Frame_width		640
#define Frame_height	480

using namespace std;
using namespace cv;

struct Gaussion_data
{
	int Data[256] = { 0 };
	int L;
	int A;
}Img_Point[Frame_height][Frame_width];

void BackGround_Init(Mat* Input)
{
	for (int y = 0; y < Frame_height; y++) {
		uchar* data = (*Input).ptr<uchar>(y);
		for (int x = 0; x < Frame_width; x++) {
			data[x] = Img_Point[y][x].L;
		}
	}
}

void Gaussion_Threshold(Mat Input, Mat* Output)
{
	Input.copyTo(*Output);
	for (int y = 0; y < Frame_height; y++) {
		uchar* Input_data = Input.ptr<uchar>(y);
		uchar* Output_data = (*Output).ptr<uchar>(y);
		for (int x = 0; x < Frame_width; x++) {
			if (Input_data[x] > (Img_Point[y][x].A * 3))		//如果变化的值过大
				Output_data[x] = 255;						//就标记出来
			else
				Output_data[x] = 0;
		}
	}
}

int main()
{
	VideoCapture cap;
	Mat frame;
	Point Text_start, Text_end, Line_start, Line_end;
	Size ReImgSiz;
	int step = 0, sum = 0;	//step记录已经录入了多少帧
	cap.open(0);
	ReImgSiz.width = Frame_width;
	ReImgSiz.height = Frame_height;  //将摄像头读入的图像改小, 拍太大电脑处理不过来
	Text_start.x = Frame_width / 2 - 50;
	Text_start.y = 10;
	Text_end.x = Frame_width / 2 + 55;
	Text_end.y = 10;
	Line_start.x = Text_start.x + 5;
	Line_start.y = 8;
	Line_end.y = 8;
	waitKey(0);					//按任意键开始录入背景数据
	namedWindow("Video", WINDOW_NORMAL);
	Mat gray;
	while (cap.isOpened()) {
		bool ret = cap.read(frame);
		//resize(frame, frame, ReImgSiz, INTER_LINEAR);
		if (ret) {
			cvtColor(frame, gray, COLOR_BGR2GRAY);	//转为灰度图
			for (int y = 0; y < Frame_height; y++) {
				uchar* data = frame.ptr<uchar>(y);
				for (int x = 0; x < Frame_width; x++) {
					Img_Point[y][x].Data[data[x]] += 1;		//记录数据
				}
			}
			//在图上显示进度条
			putText(frame, "<", Text_start, FONT_HERSHEY_SIMPLEX, 0.3, Scalar(50, 0, 255), 2);
			Line_end.x = Line_start.x + step / (N / 100);
			line(frame, Line_start, Line_end, Scalar(255, 0, 50), 2);
			putText(frame, ">", Text_end, FONT_HERSHEY_SIMPLEX, 0.3, Scalar(50, 0, 255), 2);
			//一帧数据录入完毕
			step++;
			imshow("Video", frame);
			char key = waitKey(1);
			if (key == ' ') break;
			if (step == N)
				break;
		}
	}
	//背景录入完毕, 开始高斯建模
	for (int y = 0; y < Frame_height; y++) {
		for (int x = 0; x < Frame_width; x++) {
			for (int n = 0; n < 256; n++) {
				sum += Img_Point[y][x].Data[n] * n;
			}
			Img_Point[y][x].L = sum / N;
			sum = 0;
			for (int n = 0; n < 256; n++) {
				sum += ((n - Img_Point[y][x].L) * (n - Img_Point[y][x].L)) * Img_Point[y][x].Data[n];
			}
			Img_Point[y][x].A = ceil(sum / N);
			sum = 0;
		}
	}
	cout << "高斯建模完成" << endl;
	destroyAllWindows();
	//开始检测
	Mat Background, subMat, Binary_Mat;
	cvtColor(frame, frame, COLOR_BGR2GRAY);
	frame.copyTo(Background);		//将录入时的最后一帧作为背景
	BackGround_Init(&Background);
	while (cap.isOpened()) {
		bool ret = cap.read(frame);
		//resize(frame, frame, ReImgSiz, INTER_LINEAR);
		if (ret) {
			imshow("source", frame);
			cvtColor(frame, frame, COLOR_BGR2GRAY);
			absdiff(frame, Background, subMat);
			Gaussion_Threshold(subMat, &Binary_Mat);
			imshow("Binary", Binary_Mat);
			char key = waitKey(10);
			if (key == ' ') break;
		}
	}
	return 0;
}