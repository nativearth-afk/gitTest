#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

void main()
{
	Mat srcImage = imread("D:\\2.png");
	int height = srcImage.rows;
	int width = srcImage.cols;
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				//开始处理每个像素
				uchar average = (srcImage.at<Vec3b>(j, i)[0] + srcImage.at<Vec3b>(j, i)[1] +
					srcImage.at<Vec3b>(j, i)[2]) / 3;
				srcImage.at<Vec3b>(j, i)[0] = average;
				srcImage.at<Vec3b>(j, i)[1] = average;
				srcImage.at<Vec3b>(j, i)[2] = average;
				//结束像素处理
			}//单行处理结束
		}
	imshow("这是一个标题", srcImage);
	waitKey(0);
}
