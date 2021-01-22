#include <opencv.hpp>
#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>


using namespace cv;
using namespace std;


void main()
{
	//宽敞比阈值
	float wh_ratio_high = 1.2;
	float wh_ratio_low = 0.9;

	//定义图像容器
	Mat srcMat;
	Mat bnyMat;
	Mat disMat;
	Mat sttMat;
	Mat cntMat;
	Mat lblMat;

	//读取图片
	srcMat = imread("D:\\cpu.jpg");
	//读取图片失败
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}
	srcMat.copyTo(disMat);
	cvtColor(srcMat, srcMat, COLOR_BGR2GRAY);

	//二值化
	threshold(srcMat, bnyMat, 100, 255, THRESH_OTSU);

	//腐蚀降噪
	cv::Mat element = cv::Mat::ones(3, 3, CV_8UC1);
	erode(bnyMat, bnyMat, element, cv::Point(-1, -1));


	vector<vector<Point>> contours;
	findContours(bnyMat, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);


	//绘制轮廓
	for (int i = 0; i < contours.size(); i++) {
		//获得最小外界四边形
		RotatedRect rbox = minAreaRect(contours[i]);

		//计算宽敞比
		float width = (float)rbox.size.width;
		float height = (float)rbox.size.height;
		float ratio = width / height;

		//条件筛选
		if (
			(ratio > wh_ratio_low)
			&& (ratio < wh_ratio_high)
			)
		{

			drawContours(disMat, contours, i, Scalar(0, 255, 255), 1, 8);
			//获取4个顶点
			cv::Point2f vtx[4];
			rbox.points(vtx);
			//绘制4条边
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