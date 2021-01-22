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

	//定义图像容器
	Mat srcMat;
	Mat bnyMat;
	Mat disMat;
	Mat sttMat;
	Mat cntMat;
	Mat lblMat;

	//读取图片
	srcMat = imread("D:\\wheel.png");
	//读取图片失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}
	srcMat.copyTo(disMat);
	cvtColor(srcMat, srcMat, COLOR_BGR2GRAY);

	//二值化
	threshold(srcMat, bnyMat, 100, 255, THRESH_OTSU);

	//反色
	bnyMat = 255 - bnyMat;

	//连通域
	int nComp = connectedComponentsWithStats(bnyMat, lblMat, sttMat, cntMat);

	int* flag = new int[nComp];
	memset(flag, 0, sizeof(int) * nComp);

	//计算宽长比
	//0号为背景，跳过，i=1开始循环
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
			//绘制bounding box
			Rect bbox;
			//bounding box左上角坐标
			bbox.x = sttMat.at<int>(i, 0);
			bbox.y = sttMat.at<int>(i, 1);
			//bouding box的宽和长 
			bbox.width = sttMat.at<int>(i, 2);
			bbox.height = sttMat.at<int>(i, 3);
			//绘制
			rectangle(disMat, bbox, CV_RGB(255, 255, 0), 2, 8, 0);

			//记录标签
			flag[i] = 1;
		}
	}

	//筛选出的像素上色
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