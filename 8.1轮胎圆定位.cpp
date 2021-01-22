#include <opencv.hpp>
#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

using namespace cv;
using namespace std;

void main()
{

	float wh_ratio_high = 1.1;
	float wh_ratio_low = 0.9;
	float area_th = 100;

	//����ͼ������
	Mat srcMat;
	Mat bnyMat;
	Mat disMat;
	Mat sttMat;
	Mat cntMat;
	Mat lblMat;

	//��ȡͼƬ
	srcMat = imread("D:\\wheel.png");
	//��ȡͼƬʧ��
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}
	srcMat.copyTo(disMat);
	cvtColor(srcMat, srcMat, COLOR_BGR2GRAY);

	//��ֵ��
	threshold(srcMat, bnyMat, 100, 255, THRESH_OTSU);

	//��ɫ
	bnyMat = 255 - bnyMat;

	//��ͨ��
	int nComp = connectedComponentsWithStats(bnyMat, lblMat, sttMat, cntMat);

	int* flag = new int[nComp];
	memset(flag, 0, sizeof(int) * nComp);

	//�������
	//0��Ϊ������������i=1��ʼѭ��
	for (int i = 1; i < nComp; i++) {
		float width = (float)sttMat.at<int>(i, CC_STAT_WIDTH);
		float height = (float)sttMat.at<int>(i, CC_STAT_HEIGHT);
		float ratio = width / height;

		if (
			(ratio > wh_ratio_low)
			&& (ratio < wh_ratio_high)
			&& (sttMat.at<int>(i, CC_STAT_AREA) > area_th)
			)
		{
			//����bounding box
			Rect bbox;
			//bounding box���Ͻ�����
			bbox.x = sttMat.at<int>(i, 0);
			bbox.y = sttMat.at<int>(i, 1);
			//bouding box�Ŀ�ͳ� 
			bbox.width = sttMat.at<int>(i, 2);
			bbox.height = sttMat.at<int>(i, 3);
			//����
			rectangle(disMat, bbox, CV_RGB(255, 255, 0), 2, 8, 0);

			//��¼��ǩ
			flag[i] = 1;
		}
	}

	//ɸѡ����������ɫ
	for (int i = 0; i < srcMat.rows; i++)
	{
		for (int j = 0; j < srcMat.cols; j++)
		{
			int no = lblMat.at<int>(i, j);

			if (flag[no] == 1) {
				disMat.at<Vec3b>(i, j)[0] = 0;
				disMat.at<Vec3b>(i, j)[1] = 255;
				disMat.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}

	delete[] flag;

	imshow("source image", srcMat);
	imshow("binary image", bnyMat);
	imshow("hole image", disMat);

	waitKey(0);

	destroyAllWindows();

}