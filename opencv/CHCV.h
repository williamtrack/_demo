#pragma once
#include "opencv2/opencv.hpp"

class CHCV
{
public:
	CHCV(cv::Mat& src,std::string windows);
	cv::Mat src;
	std::string winName;
	void f_paint();
	void f_change(); //change img model, save img file
	void f_mat(); //Mat using
	int f_camera(); //read camera data
	int f_histogram(); //��ͨ��ֱ��ͼ
	int f_histogram3(); //3ͨ��ֱ��ͼ
	int f_count(); //pixel count
	int f_koutu(); //��ͼ
	int f_work();
};

