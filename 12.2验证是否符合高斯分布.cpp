#include<iostream>
#include<opencv2/opencv.hpp>
#include<stdlib.h>

#define Step			1
#define N				400
#define Frame_width		320
#define Frame_height	240

using namespace std;
using namespace cv;


int Select_x = 0;
int Select_y = 0;
int CallBack_Flag = 1;

void onMouse(int Event, int x, int y, int flags, void* userdata)
{
	if (flags == EVENT_LBUTTONDOWN && CallBack_Flag) { //如果左键双击
		Select_x = x;
		Select_y = y;
		CallBack_Flag = 0;								 //选定了就不再改了
	}
}

int main()
{
	VideoCapture cap;
	Mat frame;
	Mat Show(240, 512, CV_8UC3, Scalar(255, 255, 255));
	Point Text_start, Text_end, Line_start, Line_end;
	Size ReImgSiz;
	float Table[512] = { 0 };
	int step = 0, sum = 0;
	cap.open(0);
	namedWindow("Video", WINDOW_NORMAL);
	namedWindow("show", WINDOW_AUTOSIZE);
	setMouseCallback("Video", onMouse);
	imshow("show", Show);
	ReImgSiz.width = Frame_width;
	ReImgSiz.height = Frame_height;
	Text_start.x = Frame_width / 2 - 50;
	Text_start.y = 10;
	Text_end.x = Frame_width / 2 + 55;
	Text_end.y = 10;
	Line_start.x = Text_start.x + 5;
	Line_start.y = 8;
	Line_end.y = 8;
	while (cap.isOpened()) {
		bool ret = cap.read(frame);
		resize(frame, frame, ReImgSiz, INTER_LINEAR);
		if (ret) {
			if (CallBack_Flag == 0) {						//如果已经选好点了
				Mat gray;
				cvtColor(frame, gray, COLOR_BGR2GRAY);
				uchar* data = frame.ptr<uchar>(Select_y);
				Table[data[Select_x]] += Step;
				for (int n = 0; n < 256; n++) {
					Point Start, End;
					Start.x = n * 2;
					End.x = n * 2;
					Start.y = 240 - 1;
					End.y = 2 * (120 - floor(Table[n])) - 1;
					if (End.y <= 0)
						End.y = 0;
					line(Show, Start, End, Scalar(86, 156, 214), 2);
				}
				circle(frame, Point(Select_x, Select_y), 3, Scalar(214, 157, 133), -1);
				putText(frame, "<", Text_start, FONT_HERSHEY_SIMPLEX, 0.3, Scalar(50, 0, 255), 2);
				Line_end.x = Line_start.x + step / (N / 100);
				line(frame, Line_start, Line_end, Scalar(255, 0, 50), 2);
				putText(frame, ">", Text_end, FONT_HERSHEY_SIMPLEX, 0.3, Scalar(50, 0, 255), 2);
				imshow("show", Show);
				step++;
			}
			imshow("Video", frame);
			char key = waitKey(1);
			if (key == ' ') break;
			if (step == N) break;
		}
	}
	for (int n = 0; n < 256; n++) {
		sum += Table[n] * n;
	}
	int L = sum / N;
	sum = 0;
	for (int n = 0; n < 256; n++) {
		sum += ((n - L) * (n - L)) * Table[n];
	}
	int A = ceil(sum / N);
	cout << L << endl << A << endl;
	cout << step << endl;
	cout << frame.cols << frame.rows << endl;
	destroyAllWindows();
	system("pause");
}