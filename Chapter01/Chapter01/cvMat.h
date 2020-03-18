#pragma once

#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>

cv::Mat function()
{
	//����ͼ��;
	cv::Mat ima(500, 500, CV_8U, 50);
	return ima;
}

void cvMatFun()
{
	//����һ��240��*320�е���ͼ��;
	cv::Mat image1(240, 320, CV_8U, 100);
	cv::imshow("image", image1);//��ʾͼ��;
	cv::waitKey(0);//�ȴ�����;

	//���·���һ����ͼ��;
	image1.create(200, 200, CV_8U);
	image1 = 200;
	cv::imshow("image", image1);
	cv::waitKey(0);

	//����һ����ɫ��ͼ��ͨ������ΪBGR;
	cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));

	//����;
	//cv::Mat image2(240, 320, CV_8UC3);
	//image2 = cv::Scalar(0, 0, 255);
	cv::imshow("image", image2);
	cv::waitKey(0);

	//����һ��ͼƬ;
	cv::Mat image3 = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\puppy.bmp");

	//������Щ��Щͼ��ָ��ͬһ�����ݿ�;
	cv::Mat image4(image3);
	image1 = image3;


	//��Щͼ����Դͼ�񸱱�;
	image3.copyTo(image2);
	cv::Mat image5 = image3.clone();

	//ת��ͼ����в���;
	cv::flip(image3, image3, 1);

	cv::imshow("image 3", image3);
	cv::imshow("image 1", image1);
	cv::imshow("image 2", image2);
	cv::imshow("image 4", image4);
	cv::imshow("image 5", image5);
	cv::waitKey(0);

	//�Ӻ����л�ȡһ���Ҷ�ͼ��;
	cv::Mat gray = function();
	cv::imshow("image", gray);
	cv::waitKey(0);

	image1 = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\puppy.bmp", cv::IMREAD_GRAYSCALE);
	image1.convertTo(image2, CV_32F, 1 / 255, 0.0);
	cv::imshow("image", image2);
	cv::waitKey(0);

}
