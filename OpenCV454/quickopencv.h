#pragma once


#include <opencv2/opencv.hpp>

#define picpath "F:/tr_12221053.png"
#define portraitpath "F:/美女演示图0.png"
#define portraitpath1 "F:/全绿背景的人像.jpg"

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
	void norm_demo(Mat& image);
	void resize_demo(Mat& image);
	void flip_demo(Mat& image);
	void rotate_demo(Mat& image);
	void viedo_demo1(Mat& image);
	void viedo_demo2(Mat& image);
	void histogram_demo(Mat& image);
	void histogram_2d_demo(Mat& image);
	void histogram_eq_demo(Mat& image);
	void blur_demo(Mat& image);
	void gaussian_blur_demo(Mat& image);
	void bifilter_demo(Mat& image);
};