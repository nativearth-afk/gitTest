#include<iostream>
#include<opencv2/opencv.hpp>
#define CellSize	16

using namespace cv;
using namespace std;

int Simple_Hog(Mat src_Img, float* List, int nAngle, int Size)
{
	Mat Img_x, Img_y;
	Mat mag, angle;
	int ny = src_Img.rows / CellSize;
	int nx = src_Img.cols / CellSize;
	int x, y;
	Sobel(src_Img, Img_x, CV_32F, 1, 0, 1);
	Sobel(src_Img, Img_y, CV_32F, 0, 1, 1);

	cartToPolar(Img_x, Img_y, mag, angle, true);	//得到这张图中每个像素点的方向和幅值

	for (y = 0; y < ny; y++) {
		for (x = 0; x < nx; x++) {
			Mat roiImg, roiMag, roiAngle;
			Rect roi = Rect(x * CellSize, y * CellSize, CellSize, CellSize);
			roiImg = src_Img(roi);
			roiMag = mag(roi);
			roiAngle = angle(roi);
			int Start = (y * nx + x) * nAngle;
			float step = 360 / nAngle;	//角度区域的大小
			//float step = 2.0 / (float)nAngle;
			for (int n = 0; n < roiImg.rows; n++) {
				float* Data_angle = roiAngle.ptr<float>(n);
				float* Data_mag = roiMag.ptr<float>(n);
				for (int m = 0; m < roiImg.cols; m++) {
					int Num = floor(roiAngle.at<float>(n, m) / step);	//算出这一点像素角度在第几个分区
					List[Start + Num] += roiMag.at<float>(n, m);
				}
			}
		}
	}
	return 0;
}

float Hist_Distance(float* Hist1, float* Hist2, int Num)
{
	int sum = 0;
	float result;
	for (int n = 0; n < Num; n++) {
		sum += (Hist1[n] - Hist2[n]) * (Hist1[n] - Hist2[n]);
	}
	result = sqrt(sum);
	return result;
}

int main()
{
	Mat Temp_Img, Test_Right, Test_Wrong;
	int nAngle = 8;
	Temp_Img = imread("E:\\opencv\\pictures\\hogTemplate.jpg", 0);
	Test_Right = imread("E:\\opencv\\pictures\\hogTest1.jpg", 0);
	Test_Wrong = imread("E:\\opencv\\pictures\\hogTest2.jpg", 0);
	int ny = Temp_Img.rows / CellSize;
	int nx = Temp_Img.cols / CellSize;
	int bin = ny * nx * nAngle;
	//float ref_Hist[1000];
	float* ref_Hist = new float[bin];
	memset(ref_Hist, 0, sizeof(float) * bin);
	float* r_Hist = new float[bin];
	memset(r_Hist, 0, sizeof(float) * bin);
	float* w_Hist = new float[bin];
	memset(w_Hist, 0, sizeof(float) * bin);
	int reCode = 0;
	reCode = Simple_Hog(Temp_Img, ref_Hist, nAngle, CellSize);
	cout << "step 1 finish" << endl;
	reCode = Simple_Hog(Test_Right, r_Hist, nAngle, CellSize);
	cout << "step 2 finish" << endl;
	reCode = Simple_Hog(Test_Wrong, w_Hist, nAngle, CellSize);
	cout << "Finish" << endl;
	float Dis1 = Hist_Distance(ref_Hist, r_Hist, bin);
	float Dis2 = Hist_Distance(ref_Hist, w_Hist, bin);  //计算两个直方图间的距离

	cout << "有人的图:" << Dis1 << endl;
	cout << "无人的图:" << Dis2 << endl;
	delete[] ref_Hist;
	delete[] r_Hist;
	delete[] w_Hist;		//释放内存

	return 0;
}