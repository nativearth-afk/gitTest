
#include <opencv.hpp>
#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>


using namespace cv;
using namespace std;

void main()
{
	//ɸѡ
	int width_th = 50;
	int height_th = 50;

	//0-180
	//��ɫ
	//��һ��Hue�ķ�Χ
	double i_minH = 0;
	double i_maxH = 20;
	//�ڶ���Hue�ķ�Χ
	double i_minH2 = 160;
	double i_maxH2 = 180;

	//0-255
	double i_minS = 100;
	double i_maxS = 255;
	//0-255
	double i_minV = 50;
	double i_maxV = 255;

	Mat srcMat = imread("D:\\cup.jpg");
	//��ȡͼƬʧ��
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	Mat hsvMat;
	Mat disMat;
	Mat rangeMat1;
	Mat rangeMat2;
	Mat bnyMat;
	Mat lblMat, sttMat, cntMat;

	//ת����hsvģʽ
	cvtColor(srcMat, hsvMat, COLOR_BGR2HSV);
	srcMat.copyTo(disMat);

	cv::inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), rangeMat1);
	cv::inRange(hsvMat, Scalar(i_minH2, i_minS, i_minV), Scalar(i_maxH2, i_maxS, i_maxV), rangeMat2);

	//�����㣬�ϲ�������Χ��ɸѡ���
	bnyMat = rangeMat1 + rangeMat2;

	//��ͨ��
	int nComp = connectedComponentsWithStats(bnyMat, lblMat, sttMat, cntMat);

	//0��Ϊ������������i=1��ʼѭ��
	for (int i = 1; i < nComp; i++) {
		Rect bbox;
		//bounding box���Ͻ�����
		bbox.x = sttMat.at<int>(i, 0);
		bbox.y = sttMat.at<int>(i, 1);
		//bouding box�Ŀ�ͳ� 
		bbox.width = sttMat.at<int>(i, 2);
		bbox.height = sttMat.at<int>(i, 3);
		//����
		if (
			bbox.width > width_th
			&& bbox.height > height_th
			)
		{
			rectangle(disMat, bbox, CV_RGB(255, 255, 0), 2, 8, 0);
		}
	}

	imshow("source image", srcMat);
	imshow("binary image", bnyMat);
	imshow("hole image", disMat);

	waitKey(0);

}