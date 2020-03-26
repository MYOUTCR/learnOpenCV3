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
		//�������ͼ��λ��;
		i = randomCol(generator);
		j = randomRow(generator);

		if (image.type() == CV_8UC1)
		{
			image.at<uchar>(j, i) = 255;//��ͨ��;
		}
		else if (image.type() == CV_8UC3)
		{
			//��ͨ��;
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

	//ÿ��Ԫ������;
	int nc = image.cols*image.channels();

	for (int j = 0; j < nl; j++)
	{
		//��ȡj��ַ;
		uchar *data = image.ptr<uchar>(j);

		for (int i=0;i<nc;i++)
		{
			//����ÿһ������;
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

	//ÿ��Ԫ������;
	int nc = image.cols*image.channels();

	for (int j = 0; j < nl; j++)
	{
		//��ȡj��ַ;
		const uchar *data = image.ptr<uchar>(j);
		uchar *data_out = result.ptr<uchar>(j);

		for (int i = 0; i<nc; i++)
		{
			//����ÿһ������;
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
	std::cout << "��ʱ��" << duraton << std::endl;

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
		const uchar *previous = image.ptr<const uchar>(j - 1);//��һ��;
		const uchar *current = image.ptr<const uchar>(j);//��һ��;
		const uchar *next = image.ptr<const uchar>(j + 1);//��һ��;
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

	//��δ�������������Ϊ0;
	result.row(0).setTo(cv::Scalar(0));
	result.row(result.rows-1).setTo(cv::Scalar(0));
	result.col(0).setTo(cv::Scalar(0));
	result.col(result.cols - 1).setTo(cv::Scalar(0));

}

void sharpen2D(const cv::Mat &image, cv::Mat &result)
{
	//�����ں�;
	cv::Mat kernel(3, 3, CV_32F, cv::Scalar(0));

	//���ں˸�ֵ;
	kernel.at<float>(1, 1) = 5;
	kernel.at<float>(0, 1) = -1;
	kernel.at<float>(2, 1) = -1;
	kernel.at<float>(1, 0) = -1;
	kernel.at<float>(1, 2) = -1;

	//��ͼ���˲�;
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
	std::cout << "��ʱ��" << duraton << std::endl;

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
	//ӳ�����;
	cv::Mat srcX(image.rows, image.cols, CV_32F);
	cv::Mat srcY(image.rows, image.cols, CV_32F);

	//����ӳ�����;
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