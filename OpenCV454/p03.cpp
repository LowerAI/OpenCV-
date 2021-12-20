// OpenCV454.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <opencv2\opencv.hpp>
#include "quickopencv.h"
#include <iostream>

using namespace cv;
using namespace std;

int main3()
{
    Mat src = imread(picpath);
    if (src.empty())
    {
        printf("图片加载失败...");
        return -1;
    }
    namedWindow("input", WINDOW_FREERATIO); // 让图片自适应系统桌面的大小
    imshow("input", src);

    QuickDemo qd;
    qd.colorSpace_Demo(src);

    waitKey(0);
    destroyAllWindows();
    return 0;
}
