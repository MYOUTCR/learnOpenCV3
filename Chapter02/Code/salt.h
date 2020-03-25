#pragma once
#include <iostream>
#include <random>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>


void salt(cv::Mat image, int n)
{
	std::default_random_engine generator;
	std::uniform_int_distribution<int> randomRow(0, image.rows - 1);
	std::uniform_int_distribution<int> randomCol(0, image.cols - 1);

	int i = 0, j = 0;

	for (int k = 0; k < n; k++)
	{
		//随机生成图形位置;
		i = randomCol(generator);
		j = randomRow(generator);

		if (image.type() == CV_8UC1)
		{
			image.at<uchar>(j, i) = 255;//单通道;
		}
		else if (image.type() == CV_8UC3)
		{
			//三通道;
			//image.at<cv::Vec3b>(j, i)[0] = 255;
			//image.at<cv::Vec3b>(j, i)[1] = 255;
			//image.at<cv::Vec3b>(j, i)[2] = 255;
			image.at<cv::Vec3b>(j, i) = cv::Vec3b(255, 255, 255);
		}
	}
}

void saltImage()
{
	cv::Mat image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\boldt.jpg", 1);
	salt(image, 3000);
	cv::namedWindow("image");
	cv::imshow("image",image);
	cv::waitKey(0);

}

void colorReduce(cv::Mat image, int div = 64)
{
	int  nl = image.rows;

	//每行元素数量;
	int nc = image.cols*image.channels();

	for (int j = 0; j < nl; j++)
	{
		//获取j地址;
		uchar *data = image.ptr<uchar>(j);

		for (int i=0;i<nc;i++)
		{
			//处理每一个像素;
			//data[i] = data[i] / div*div + div*0.5;
			//*data++ = *data / div*div + div*0.5;
			//data[i] = data[i] - data[i] % div + div*0.5;

			//uchar mask=0xFF<<2;
			//*data &= mask;
			//*data++ += div >> 1;
		}
	}
}

void colorReduce(const cv::Mat &image, cv::Mat &result, int div = 64)
{
	int  nl = image.rows;

	result.create(image.rows, image.cols, image.type());

	//每行元素数量;
	int nc = image.cols*image.channels();

	for (int j = 0; j < nl; j++)
	{
		//获取j地址;
		const uchar *data = image.ptr<uchar>(j);
		uchar *data_out = result.ptr<uchar>(j);

		for (int i = 0; i<nc; i++)
		{
			//处理每一个像素;
			data_out[i] = data[i] / div*div + div*0.5;
		}
	}
}

void colorReduceImage()
{
	cv::Mat image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\boldt.jpg", 1);
	colorReduce(image, 64);
	cv::namedWindow("image");
	cv::imshow("image", image);
	cv::waitKey(0);
}

void colorReduceImage1()
{
	cv::Mat image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\boldt.jpg", 1);
	cv::Mat result;
	colorReduce(image, result, 64);
	cv::namedWindow("image");
	cv::imshow("image", image);
	cv::imshow("result", result);
	cv::waitKey(0);

}

