#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;


using namespace std;


Mat gammaTransform(Mat& srcImage, float kFactor)
{

	unsigned char LUT[256];
	for (int i = 0; i < 256; i++)
	{
		float f = (i + 0.5f) / 255;
		f = (float)(pow(f, kFactor));
		LUT[i] = saturate_cast<uchar>(f * 255.0f - 0.5f);
	}
	Mat resultImage = srcImage.clone();

	if (srcImage.channels() == 1)
	{

		MatIterator_<uchar> iterator = resultImage.begin<uchar>();
		MatIterator_<uchar> iteratorEnd = resultImage.end<uchar>();
		for (; iterator != iteratorEnd; iterator++)
		{
			*iterator = LUT[(*iterator)];
		}
	}
	else
	{


		MatIterator_<Vec3b> iterator = resultImage.begin<Vec3b>();
		MatIterator_<Vec3b> iteratorEnd = resultImage.end<Vec3b>();
		for (; iterator != iteratorEnd; iterator++)
		{
			(*iterator)[0] = LUT[((*iterator)[0])];//b
			(*iterator)[1] = LUT[((*iterator)[1])];//g
			(*iterator)[2] = LUT[((*iterator)[2])];//r
		}
	}
	return resultImage;
}

void callback(int th, void* data)//����
{
	//ǿ������ת��
	cv::Mat src = *((cv::Mat*) data);
	float kFactor1 = 1 / (((float)th) / 20);//���Զ�ʮ�þ�׼�ȸ���

	//�������ͼƬ����
	cv::Mat dst = gammaTransform(src, kFactor1);

	//��ֵ������

	cv::imshow("bar", dst);
}

void main()
{
	cv::Mat srcMat;

	//��ȡͼƬ
	srcMat = imread("D:\\gamma.jpg");

	//�ж϶�ȡͼƬ�Ƿ�ʧ��
	if (srcMat.empty()) {
		cout << "fail to read pic!" << endl;
		return;
	}

	//���ڷ�Χ
	int lowth = 0;
	int maxth = 70;


	//��ʾ�Ҷ�ͼ
	namedWindow("bar");
	cv::imshow("bar", srcMat);

	//��������������
	createTrackbar("th*20", "bar", &lowth, maxth, callback, &srcMat);
	cv::waitKey(0);
}
