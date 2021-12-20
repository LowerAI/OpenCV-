#include "quickopencv.h"

void QuickDemo::colorSpace_Demo(Mat& image)
{
    Mat gray, hsv;

    // HSV： 色调(H:0~180)，饱和度(S)，明度(V)
    // 转换
    cvtColor(image, hsv, COLOR_BGR2HSV);
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // 显示
    imshow("HSV", hsv);
    imshow("灰度", gray);

    // 保存
    imwrite("F:/hsv.png", hsv);
    imwrite("F:/gray.png", gray);
}

/// <summary>
/// 创建图像
/// </summary>
/// <param name="image"></param>
void QuickDemo::mat_creation_demo(Mat& image)
{
    Mat m1, m2;
    m1 = image.clone();
    image.copyTo(m2);

    // 创建空白图像
    // Mat m3 = Mat::ones(Size(8, 8), CV_8UC3); // 注意此时只会将通道1中的数字置为1
    Mat m3 = Mat::zeros(Size(400, 400), CV_8UC3); // CV_8UC1-8:8位，U是usigned无符号的，C是char字符，1是单通道的。综合起来就是8位单通道无符号的字符数组；Size(8, 8)表示8行x8列
    m3 = Scalar(255, 0, 0);

    //std::cout << "width:" << m3.cols << " height:" << m3.rows << " channels:" << m3.channels() << std::endl;
    //std::cout << m3 << std::endl;
    imshow("图像", m3);
}

/// <summary>
/// 读写单个像素
/// </summary>
/// <param name="image"></param>
void QuickDemo::pixel_visit_demo(Mat& image)
{
    int w = image.cols; // 宽
    int h = image.rows; // 高
    int dims = image.channels(); // 通道数

    // 数组遍历
    for (int row = 0; row < h; row++)
    {
        for (int col = 0; col < w; col++)
        {
            switch (dims)
            {
            case 1: // 单通道 灰度图像
            {
                int pv = image.at<uchar>(row, col);
                image.at<uchar>(row, col) = 255 - pv;
            }
            break;
            case 3: // 3通道 彩色图像
            {
                Vec3b bgr = image.at<Vec3b>(row, col);
                image.at<Vec3b>(row, col)[0] = 255 - bgr[0];
                image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
                image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
            }
            break;
            }
        }
    }

    // 指针遍历
    //for (int row = 0; row < h; row++)
    //{
    //    uchar* current_row = image.ptr<uchar>(row);
    //    for (int col = 0; col < w; col++)
    //    {
    //        switch (dims)
    //        {
    //        case 1: // 单通道 灰度图像
    //        {
    //            int pv = *current_row;
    //            *current_row++ = 255 - pv;
    //        }
    //        break;
    //        case 3: // 3通道 彩色图像
    //        {
    //            *current_row++ = 255 - *current_row;
    //            *current_row++ = 255 - *current_row;
    //            *current_row++ = 255 - *current_row;
    //        }
    //        break;
    //        }
    //    }
    //}
    imshow("像素读写演示", image);
}

/// <summary>
/// 操作数
/// </summary>
/// <param name="image"></param>
void QuickDemo::operators_demo(Mat& image)
{
    Mat dst = Mat::zeros(image.size(), image.type());
    //dst = image + Scalar(50, 50, 50);
    Mat m = Mat::zeros(image.size(), image.type());
    m = Scalar(5, 5, 5);
    //multiply(image, m, dst); // 相乘

    int w = image.cols; // 宽
    int h = image.rows; // 高
    int dims = image.channels(); // 通道数

    // 加法
    /*for (int row = 0; row < h; row++)
    {
        for (int col = 0; col < w; col++)
        {
            Vec3b p1 = image.at<Vec3b>(row, col);
            Vec3b p2 = m.at<Vec3b>(row, col);
            for (int chan = 0; chan < dims; chan++)
            {
                dst.at<Vec3b>(row, col)[chan] = saturate_cast<uchar>(p1[chan] + p2[chan]);
            }
        }
    }*/

    add(image, m, dst); // 相加
    subtract(image, m, dst); // 相减
    divide(image, m, dst); // 相除

    imshow("算数操作", dst);
}

/// <summary>
/// 滑块回调事件
/// </summary>
/// <param name="pos">滑块当前值</param>
/// <param name="userdata">用户传递的数据</param>
static void on_track(int pos, void* userdata)
{
    // 判断是否nullptr
    if (userdata == 0)
    {
        return;
    }
    Mat* src = (Mat*)userdata;
    Mat m, dst;
    m = Mat::zeros(src->size(), src->type());
    m = Scalar(pos, pos, pos); // 此时pos就是createTrackbar中传入的lightness(亮度值)
    dst = Mat::zeros(src->size(), src->type());
    add(*src, m, dst);
    imshow("亮度调整", dst);
}

/// <summary>
/// 滑块交互调整
/// </summary>
/// <param name="image"></param>
void QuickDemo::tracking_bar_demo7(Mat& image)
{
    namedWindow("亮度调整", WINDOW_AUTOSIZE);
    int max_value = 100;
    int lightness = 50;
    createTrackbar("Value Bar", "亮度调整", &lightness, max_value, on_track, &image);
    on_track(50, 0);
}

/// <summary>
/// 亮度滑块回调事件
/// </summary>
/// <param name="pos">当前亮度值</param>
/// <param name="userdata">用户传递的数据</param>
static void on_lightness(int pos, void* userdata)
{
    Mat* src = (Mat*)userdata;
    Mat m = Mat::zeros(src->size(), src->type());
    Mat dst = Mat::zeros(src->size(), src->type());
    addWeighted(*src, 1.0, m, 0, pos, dst);
    imshow("亮度与对比度调整", dst);
}

/// <summary>
/// 对比度滑块回调事件
/// </summary>
/// <param name="pos">当前对比度值</param>
/// <param name="userdata">用户传递的数据</param>
static void on_contrast(int pos, void* userdata)
{
    Mat* src = (Mat*)userdata;
    Mat m = Mat::zeros(src->size(), src->type());
    Mat dst = Mat::zeros(src->size(), src->type());
    double contrast = pos / 100.0;
    addWeighted(*src, contrast, m, 0.0, 0, dst);
    imshow("亮度与对比度调整", dst);
}

/// <summary>
/// 滑块交互调整
/// </summary>
/// <param name="image"></param>
void QuickDemo::tracking_bar_demo8(Mat& image)
{
    namedWindow("亮度与对比度调整", WINDOW_AUTOSIZE);
    int lightness = 50;
    int max_value = 100;
    int contrast_value = 100;
    createTrackbar("Value Bar", "亮度与对比度调整", &lightness, max_value, on_lightness, &image);
    createTrackbar("Contrast Bar", "亮度与对比度调整", &contrast_value, 200, on_contrast, &image);
    on_lightness(50, &image);
}

/// <summary>
/// 按键随动
/// </summary>
/// <param name="image"></param>
void QuickDemo::key_demo(Mat& image)
{
    Mat dst = Mat::zeros(image.size(), image.type());
    while (true)
    {
        char c = waitKey(100);
        switch (c)
        {
        case 27: // Esc 退出
            break;
            break;
        case 49: // key #1
            std::cout << "you type key #1" << std::endl;
            cvtColor(image, dst, COLOR_BGR2GRAY);
            break;
        case 50: // key #2
            std::cout << "you type key #2" << std::endl;
            cvtColor(image, dst, COLOR_BGR2HSV);
            break;
        case 51: // key #3
            std::cout << "you type key #3" << std::endl;
            dst = Scalar(50, 50, 50);
            add(image, dst, dst);
            break;
        default:
            break;
        }
        imshow("键盘相应", dst);
    }
}

/// <summary>
/// 改变颜色风格
/// </summary>
/// <param name="image"></param>
void QuickDemo::color_style_demo(Mat& image)
{
    int colormap[] = {
        COLORMAP_AUTUMN,
        COLORMAP_BONE,
        COLORMAP_JET,
        COLORMAP_WINTER,
        COLORMAP_RAINBOW,
        COLORMAP_OCEAN,
        COLORMAP_SUMMER,
        COLORMAP_SPRING,
        COLORMAP_COOL,
        COLORMAP_PINK,
        COLORMAP_HOT,
        COLORMAP_PARULA,
        COLORMAP_MAGMA,
        COLORMAP_INFERNO,
        COLORMAP_PLASMA,
        COLORMAP_VIRIDIS,
        COLORMAP_CIVIDIS,
        COLORMAP_TWILIGHT,
        COLORMAP_TWILIGHT_SHIFTED
    };

    Mat dst;
    int index = 0;
    while (true)
    {
        int c = waitKey(500);
        if (c == 27)
        {
            break;
        }
        applyColorMap(image, dst, colormap[index % 19]);
        index++;
        imshow("颜色风格", dst);
    }
}

/// <summary>
/// 像素的逻辑操作
/// </summary>
/// <param name="image"></param>
void QuickDemo::bitwise_demo(Mat& image)
{
    Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
    Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
    rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
    rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
    imshow("m1", m1);
    imshow("m2", m2);
    Mat dst;
    //bitwise_and(m1, m2, dst); // 与
    //bitwise_or(m1, m2, dst); // 或
    //bitwise_not(image, dst); // 非(取反)
    //dst = ~image; // 非(取反)
    bitwise_xor(m1, m2, dst); // 异或(先或再取反)
    imshow("像素位操作", dst);
}

/// <summary>
/// 通道分离与合并
/// </summary>
/// <param name="image"></param>
void QuickDemo::channels_demo(Mat& image)
{
    std::vector<Mat> mv;
    split(image, mv);
    /*imshow("蓝色", mv[0]);
    imshow("绿色", mv[1]);
    imshow("红色", mv[2]);*/

    Mat dst;
    /*mv[1] = 0;
    mv[2] = 0;
    merge(mv, dst);
    imshow("蓝色", dst);*/

    /*mv[0] = 0;
    mv[2] = 0;
    merge(mv, dst);
    imshow("绿色", dst);*/

    /*mv[0] = 0;
    mv[1] = 0;
    merge(mv, dst);
    imshow("红色", dst);*/

    dst = Mat::zeros(image.size(), image.type());
    int from_to[] = { 0,2,1,1,2,0 };
    mixChannels(&image, 1, &dst, 1, from_to, 3);
    imshow("通道混合", dst);
}

/// <summary>
/// 色彩空间转换
/// </summary>
/// <param name="image"></param>
void QuickDemo::inrange_demo(Mat& image)
{
#pragma region    背景全白，人像全黑(针对背景全绿的图片有效)
    Mat hsv;
    cvtColor(image, hsv, COLOR_BGR2HSV);
    Mat mask;
    inRange(hsv, Scalar(35,43,46), Scalar(77,255,255), mask);
    imshow("mask", mask);
#pragma endregion

    Mat redback = Mat::zeros(image.size(), image.type());
    redback = Scalar(40, 40, 200);
    bitwise_not(mask, mask); // 把上面的结果变成背景全黑，人像全白
    imshow("mask", mask);
    image.copyTo(redback, mask); // 把红色背景替换白色背景
    imshow("roi区域提权", redback);
}
