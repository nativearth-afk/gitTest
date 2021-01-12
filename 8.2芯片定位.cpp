#include <opencv.hpp>
#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>


using namespace cv;
using namespace std;


void main()
{
	//������ֵ
	float wh_ratio_high = 1.2;
	float wh_ratio_low = 0.9;

	//����ͼ������
	Mat srcMat;
	Mat bnyMat;
	Mat disMat;
	Mat sttMat;
	Mat cntMat;
	Mat lblMat;

	//��ȡͼƬ
	srcMat = imread("D:\\cpu.jpg");
	//��ȡͼƬʧ��
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}
	srcMat.copyTo(disMat);
	cvtColor(srcMat, srcMat, COLOR_BGR2GRAY);

	//��ֵ��
	threshold(srcMat, bnyMat, 100, 255, THRESH_OTSU);

	//��ʴ����
	cv::Mat element = cv::Mat::ones(3, 3, CV_8UC1);
	erode(bnyMat, bnyMat, element, cv::Point(-1, -1));


	vector<vector<Point>> contours;
	findContours(bnyMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


	//��������
	for (int i = 0; i < contours.size(); i++) {
		//�����С����ı���
		RotatedRect rbox = minAreaRect(contours[i]);

		//�������
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float ratio = width / height;

		//����ɸѡ
		if (
			(ratio > wh_ratio_low)
			&& (ratio < wh_ratio_high)
			)
		{

			drawContours(disMat, contours, i, Scalar(0, 255, 255), 1, 8);
			//��ȡ4������
			cv::Point2f vtx[4];
			rbox.points(vtx);
			//����4����
			for (int i = 0; i < 4; ++i) {
				cv::line(disMat, vtx[i], vtx[i < 3 ? i + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA);
			}
		}
	}

	imshow("source image", srcMat);
	imshow("binary image", bnyMat);
	imshow("hole image", disMat);

	waitKey(0);
}