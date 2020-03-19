#pragma once

#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

void logo()
{
	cv::Mat image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\puppy.bmp");
	cv::Mat logo = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\smalllogo.png");

	// define image ROI at image bottom-right
	cv::Mat imageROI(image, cv::Rect(image.cols - logo.cols, image.rows - logo.rows,//����;
		logo.cols, logo.rows));//�ߴ�;

	logo.copyTo(imageROI);

	cv::imshow("Output Image", image);
	cv::waitKey(0);

	image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\puppy.bmp");
	imageROI=image(cv::Rect(image.cols - logo.cols, image.rows - logo.rows,//����;
		logo.cols, logo.rows));//�ߴ�;

	//�ѱ�־��Ϊ���루�����ǻҶ�ͼ��;
	cv::Mat mask(logo);
	//���������־��ֻ�������벻Ϊ0 ��λ��;

	logo.copyTo(imageROI, mask);

	cv::imshow("Output Image", image);
	cv::waitKey(0);
}