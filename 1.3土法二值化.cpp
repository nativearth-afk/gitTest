#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;

void main()
{
	Mat srcImage = imread("D:\\2.png");
	int height = srcImage.rows;
	int width = srcImage.cols;
	uchar threshold = 100;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			//��ʼ����ÿ������
			uchar average = (srcImage.at<Vec3b>(j, i)[0] + srcImage.at<Vec3b>(j, i)[1] +
				srcImage.at<Vec3b>(j, i)[2]) / 3;
			if (average > threshold) {
				average = 255;
			}
			else {
				average = 0;
			}
			srcImage.at<Vec3b>(j, i)[0] = average;
			srcImage.at<Vec3b>(j, i)[1] = average;
			srcImage.at<Vec3b>(j, i)[2] = average;
			//�������ش���
		}//���д������
	}
	imshow("����һ������", srcImage);
	waitKey(0);
}