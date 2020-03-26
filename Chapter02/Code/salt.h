#pragma once
#include <iostream>
#include <random>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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

	const int64 start = cv::getTickCount();
	colorReduce(image, result, 64);
	double duraton = (cv::getTickCount() - start) / cv::getTickFrequency();
	std::cout << "耗时：" << duraton << std::endl;

	cv::namedWindow("image");
	cv::imshow("image", image);
	cv::imshow("result", result);
	cv::waitKey(0);

}

void sharpen(const cv::Mat &image, cv::Mat &result)
{
	result.create(image.size(), image.type());
	int nChannels = image.channels();

	for (int j=1;j<image.rows-1;j++)
	{
		const uchar *previous = image.ptr<const uchar>(j - 1);//上一行;
		const uchar *current = image.ptr<const uchar>(j);//上一行;
		const uchar *next = image.ptr<const uchar>(j + 1);//上一行;
		uchar  *output = result.ptr<uchar>(j);

		for (int i=nChannels;i<(image.cols-1)*nChannels;i++)
		{
			*output++ = cv::saturate_cast<uchar>(
				5 * current[i] - 
				current[i - nChannels] - 
				current[i + nChannels] - 
				previous[i] - next[i]);
		}
	}

	//将未处理的像素设置为0;
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows-1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));

}

void sharpen2D(const cv::Mat &image, cv::Mat &result)
{
	//构造内核;
	cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));

	//对内核赋值;
	kernel.at<float>(1, 1) = 5;
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(2, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 2) = -1;

	//对图像滤波;
	cv::filter2D(image, result, image.depth(), kernel);

}

void sharpenImage()
{
	cv::Mat image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\boldt.jpg", 0);
	cv::Mat result;

	const int64 start = cv::getTickCount();
	//sharpen(image, result);
	sharpen2D(image, result);
	double duraton = (cv::getTickCount() - start) / cv::getTickFrequency();
	std::cout << "耗时：" << duraton << std::endl;

	cv::namedWindow("image");
	cv::imshow("image", image);
	cv::imshow("result", result);
	cv::waitKey(0);

}

void addImage()
{
	cv::Mat boldt = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\boldt.jpg", 0);
	cv::Mat rain = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\rain.jpg", 0);
	cv::Mat result = 0.7*boldt + 0.9*rain;
	//cv::Mat result;
	//cv::addWeighted(boldt, 0.7, rain, 0.9, 0., result);


	cv::namedWindow("result");
	cv::imshow("result", result);
	cv::waitKey(0);
	
}

void split()
{
	std::vector<cv::Mat> planes;

	cv::Mat image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\boldt.jpg");
	cv::Mat rain = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\rain.jpg",0);
	cv::split(image, planes);

	planes[0] += rain;
	cv::Mat result;
	cv::merge(planes, result);

	//cv::Mat matAdd = planes[0] + rain;
	cv::namedWindow("result");
	//cv::imshow("planes", planes[0]);
	//cv::imshow("planes2", planes[1]);
	//cv::imshow("planes3", planes[2]);
	cv::imshow("result", result);
	//cv::imshow("matAdd", matAdd);

	cv::waitKey(0);
}

void wave(const cv::Mat &image, cv::Mat &result)
{
	//映射参数;
	cv::Mat srcX(image.rows, image.cols, CV_32F);
	cv::Mat srcY(image.rows, image.cols, CV_32F);

	//创建映射参数;
	for (int i=0;i<image.rows;i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			srcX.at<float>(i, j) = j;
			srcY.at<float>(i, j) = i + 5 * sin(j / 10.0);
		}
	}

	cv::remap(image, result, srcX, srcY, cv::INTER_LINEAR);
}

void wave()
{
	cv::Mat image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\boldt.jpg", 0);
	cv::Mat result;
	wave(image, result);

	cv::namedWindow("result");
	cv::imshow("result", result);
	cv::waitKey(0);
}