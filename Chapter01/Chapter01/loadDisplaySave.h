#pragma once

#include <iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

void onMouse(int event, int x, int y, int flage, void *param)
{
	cv::Mat *im = reinterpret_cast<cv::Mat*>(param);
	switch (event)
	{
	case cv::EVENT_FLAG_LBUTTON:
	{
		std::cout << x << "  " << y << std::endl;
		cv::circle(*im, cv::Point(x, y), 65, 0, 3);
		cv::putText(*im, "This is dog", cv::Point(x, y), cv::FONT_HERSHEY_PLAIN, 2.0, 255, 2);
		cv::imshow("Original Image", *im);
	}break;
	default:
		break;
	}
}

void loadDisplaySave()
{
	//����һ����ͼ��;
	cv::Mat image;
	std::cout << "rows:" << image.rows << "cols" << image.cols;
	//image = cv::imread("E:\\Professionals\\OpenCV3\\images\\puppy.bmp");
	//����һ���ļ� ����ת��Ϊ�Ҷ�ͼ��;
	image = cv::imread("E:\\Professionals\\OpenCV\\learnOpenCV3\\trunk\\images\\puppy.bmp", cv::IMREAD_GRAYSCALE);
	if (image.empty())
	{
		std::cout << "Error reading image..." << std::endl;
		return;
	}

	//���崰��;
	cv::namedWindow("Original Image");
	cv::setMouseCallback("Original Image", onMouse, reinterpret_cast<void*>(&image));

	//��ʾͼ��;
	cv::imshow("Original Image", image);
	cv::waitKey(0);//0��ʾ��Զ�ĵȴ�����;�����������ʾ�ȴ��ĺ�����;

	cv::Mat result;//������һ����ͼ��;
	cv::flip(image, result, 1);//������ʾˮƽ,0��ʾ��ֱ,������ʾˮƽ�ʹ�ֱ;

	cv::namedWindow("Output Image");
	cv::imshow("Output Image", result);
	cv::waitKey(0);

	cv::imwrite("E:\\output.bmp", result); // save result
	cv::waitKey(0);

}