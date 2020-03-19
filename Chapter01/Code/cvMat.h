#pragma once

#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>

cv::Mat function()
{
	//创建图像;
	cv::Mat ima(500, 500, CV_8U, 50);
	return ima;
}

void cvMatFun()
{
	//创建一个240行*320列的新图像;
	cv::Mat image1(240, 320, CV_8U, 100);
	cv::imshow("image", image1);//显示图像;
	cv::waitKey(0);//等待按键;

	//重新分配一个新图像;
	image1.create(200, 200, CV_8U);
	image1 = 200;
	cv::imshow("image", image1);
	cv::waitKey(0);

	//创建一个红色的图像，通道次序为BGR;
	cv::Mat image2(240, 320, CV_8UC3, cv::Scalar(0, 0, 255));

	//或者;
	//cv::Mat image2(240, 320, CV_8UC3);
	//image2 = cv::Scalar(0, 0, 255);
	cv::imshow("image", image2);
	cv::waitKey(0);

	//读入一幅图片;
	cv::Mat image3 = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\puppy.bmp");

	//所有这些这些图像都指向同一个数据块;
	cv::Mat image4(image3);
	image1 = image3;


	//这些图像是源图像副本;
	image3.copyTo(image2);
	cv::Mat image5 = image3.clone();

	//转换图像进行测试;
	cv::flip(image3, image3, 1);

	cv::imshow("image 3", image3);
	cv::imshow("image 1", image1);
	cv::imshow("image 2", image2);
	cv::imshow("image 4", image4);
	cv::imshow("image 5", image5);
	cv::waitKey(0);

	//从函数中获取一个灰度图像;
	cv::Mat gray = function();
	cv::imshow("image", gray);
	cv::waitKey(0);

	image1 = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\puppy.bmp", cv::IMREAD_GRAYSCALE);
	image1.convertTo(image2, CV_32F, 1 / 255, 0.0);
	cv::imshow("image", image2);
	cv::waitKey(0);

}
