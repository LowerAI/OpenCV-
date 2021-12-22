// OpenCV454.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2\opencv.hpp>
#include <iostream>
#include "quickopencv.h"

using namespace cv;
using namespace std;

int main21()
{
    Mat src = imread(picpath); // 以灰度模式加载图片
    if (src.empty())
    {
        printf("加载图片失败...");
        return -1;
    }
    //namedWindow("input", WINDOW_FREERATIO); // 让图片自适应系统桌面的大小
    imshow("input", src);

    QuickDemo qd;
    qd.flip_demo(src);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
