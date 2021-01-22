#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;
float Lammda = 0.5;
int Track_Flag = 1;
void Gamma(float* A, float Lammda)
{
	for (int n = 0; n < 256; n++) {
		A[n] = pow((float)n / 255.0, Lammda);
	}
}

void GetLammda(int a, void* dat)
{
	Lammda = (float)a / 100.0;
	Track_Flag = 1;
}

int main()
{
	Mat src;
	float B_src[256], G_src[256], R_src[256];
	src = imread("D:\\Trash.jpg");
	int wight = src.cols, y, x, Track = 50;
	int heigth = src.rows;
	int flag = 0;
	//归一化, 然后放到数组里
	namedWindow("Tool");
	createTrackbar("λ", "Tool", &Track, 200, GetLammda);
	imshow("src", src);
	namedWindow("biaoti", WINDOW_NORMAL);
	while (1) {
		Mat result;
		if (Track_Flag) {
			float F[256];
			//进行Gamma处理
			Gamma(F, Lammda);
			//再还原到0-255
			src.copyTo(result);
			for (y = 0; y < heigth; y++) {
				for (x = 0; x < wight; x++) {
					result.at<Vec3b>(y, x)[0] = ceil(F[result.at<Vec3b>(y, x)[0]] * 255.0);
					result.at<Vec3b>(y, x)[1] = ceil(F[result.at<Vec3b>(y, x)[1]] * 255.0);
					result.at<Vec3b>(y, x)[2] = ceil(F[result.at<Vec3b>(y, x)[2]] * 255.0);
				}
			}
			imshow("biaoti", result);
			Track_Flag = 0;
		}
		char key = waitKey(50);
		if (key == ' ') {
			imwrite("OKTrash.jpg", result);
			break;
		}
	}
	waitKey(0);
	return 0;
}