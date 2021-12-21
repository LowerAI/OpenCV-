#pragma once


#include <opencv2/opencv.hpp>

#define picpath "F:/tr_12211734.png"
#define portraitpath "F:/È«ÂÌ±³¾°µÄÈËÏñ.jpg"

using namespace cv;

class QuickDemo
{
public:
	void colorSpace_Demo(Mat& image);
	void mat_creation_demo(Mat& image);
	void pixel_visit_demo(Mat& image);
	void operators_demo(Mat& image);
	void tracking_bar_demo7(Mat& image);
	void tracking_bar_demo8(Mat& image);
	void key_demo(Mat& image);
	void color_style_demo(Mat& image);
	void bitwise_demo(Mat& image);
	void channels_demo(Mat& image);
	void inrange_demo(Mat& image);
	void pixel_statistic_demo8(Mat& image);
	void drawing_demo(Mat& image);
	void random_drawing_demo(Mat& image);
	void polyline_drawing_demo(Mat& image);
	void mouse_drawing_demo(Mat& image);
//private:

};