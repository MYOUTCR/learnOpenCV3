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
	cv::Mat imageROI(image, cv::Rect(image.cols - logo.cols, image.rows - logo.rows,//坐标;
		logo.cols, logo.rows));//尺寸;

	logo.copyTo(imageROI);

	cv::imshow("Output Image", image);
	cv::waitKey(0);

	image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\puppy.bmp");
	imageROI=image(cv::Rect(image.cols - logo.cols, image.rows - logo.rows,//坐标;
		logo.cols, logo.rows));//尺寸;

	//把标志作为掩码（必须是灰度图像）;
	cv::Mat mask(logo);
	//插入掩码标志，只复制掩码不为0 的位置;

	logo.copyTo(imageROI, mask);

	cv::imshow("Output Image", image);
	cv::waitKey(0);
}