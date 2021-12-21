#include "quickopencv.h"

using namespace std;

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

    //cout << "width:" << m3.cols << " height:" << m3.rows << " channels:" << m3.channels() << endl;
    //cout << m3 << endl;
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
            cout << "you type key #1" << endl;
            cvtColor(image, dst, COLOR_BGR2GRAY);
            break;
        case 50: // key #2
            cout << "you type key #2" << endl;
            cvtColor(image, dst, COLOR_BGR2HSV);
            break;
        case 51: // key #3
            cout << "you type key #3" << endl;
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
    vector<Mat> mv;
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

/// <summary>
/// 像素值统计
/// </summary>
/// <param name="image"></param>
void QuickDemo::pixel_statistic_demo8(Mat& image)
{
    double minv, maxv;
    Point minLoc, maxLoc;
    vector<Mat> mv;
    split(image, mv);
    for (auto mat : mv)
    {
        minMaxLoc(mat, &minv, &maxv, &minLoc, &maxLoc, Mat());
        cout << "minValue:" << minv << " maxValue:" << maxv << endl;
    }
    Mat mean, stddev;
    meanStdDev(image, mean, stddev);
    cout << "mean:" << mean << endl;
    /*for (int i = 0; i < mean.rows; i++)
    {
        for (int j = 0; j < mean.cols; j++)
        {
            cout << "像素:" << mean.at<uchar>(i, j) << endl;
        }
    }*/
    cout << "stddev:" << stddev << endl;
}

/// <summary>
/// 图像几何形状绘制
/// </summary>
/// <param name="image"></param>
void QuickDemo::drawing_demo(Mat& image)
{
    Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.width = 250;
    rect.height = 300;

    Mat bg = Mat::zeros(image.size(), image.type());
    rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0); // 注意其中的thickness参数小于0为填充，大于0时表示线宽
    circle(bg, Point(350, 400), 15, Scalar(255, 0, 0), -1, 8, 0);
    line(bg, Point(100, 100), Point(350, 400), Scalar(0, 255, 0), 4, LINE_AA, 0);

    RotatedRect rrt;
    rrt.center = Point(200, 200);
    rrt.size = Size(100, 200);
    rrt.angle = 45.0;
    ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8);

    Mat dst;
    addWeighted(image, 0.7, bg, 0.3, 0, dst); // 加权计算
    imshow("绘制演示", dst);
}

/// <summary>
/// 随机数与随机颜色
/// </summary>
/// <param name="image"></param>
void QuickDemo::random_drawing_demo(Mat& image)
{
    Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
    int w = canvas.rows;
    int h = canvas.cols;
    RNG rng(12345);
    while (true)
    {
        int c = waitKey(500);
        if (c == 27)
        {
            break;
        }
        int x1 = rng.uniform(0, w);
        int y1 = rng.uniform(0, h);
        int x2 = rng.uniform(0, w);
        int y2 = rng.uniform(0, h);
        int b = rng.uniform(0, 255);
        int g = rng.uniform(0, 255);
        int r = rng.uniform(0, 255);
        canvas = Scalar(0, 0, 0); // 画布颜色复位
        line(canvas, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 1, LINE_AA, 0); // 其中的LINE_AA表示抗锯齿的线条
        imshow("随机绘制演示", canvas);
    }
}

/// <summary>
/// 绘制多边形
/// </summary>
/// <param name="image"></param>
void QuickDemo::polyline_drawing_demo(Mat& image)
{
    Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
    Point p1(100, 100);
    Point p2(350, 100);
    Point p3(450, 280);
    Point p4(320, 450);
    Point p5(80, 400);
    vector<Point> pts;
    pts.push_back(p1);
    pts.push_back(p2);
    pts.push_back(p3);
    pts.push_back(p4);
    pts.push_back(p5);
    //fillPoly(canvas, pts, Scalar(255, 0, 255), 8, 0); // 填充
    //polylines(canvas, pts, true, Scalar(0, 0, 255), 2, LINE_AA, 0); // 此函数只能绘制轮廓，无法通过把线宽置为-1来实现填充

    vector<vector<Point>> contours;
    contours.push_back(pts);
    drawContours(canvas, contours, -1, Scalar(255, 0, 0), -1, LINE_AA); // 此函数既可以绘制轮廓，也可以通过把线宽置为-1来实现填充
    
    imshow("多边形绘制", canvas);
}

Point sp(-1, -1);
Point ep(-1, -1);
Mat temp;
/// <summary>
/// 鼠标操作的事件回调
/// </summary>
/// <param name="event"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="flags"></param>
/// <param name="userdata"></param>
static void on_draw(int event, int x, int y, int flags, void* userdata)
{
    Mat* image = (Mat*)userdata; // 此时画布可能有上次绘制遗留的痕迹
    switch (event)
    {
        case EVENT_LBUTTONDOWN: // 左键按下
        {
            sp.x = x;
            sp.y = y;
            cout << "起点:" << sp << endl;
        }
            break;
        case EVENT_LBUTTONUP: // 左键松开
        {
            //temp.copyTo(*image);
            ep.x = x < 0 ? 0 : (x > image->cols ? image->cols : x);
            ep.y = y < 0 ? 0 : (y > image->rows ? image->rows : y);
            cout << "终点:" << ep << endl;
            
            int dx = ep.x - sp.x;
            if (dx < 0)
            {// 终点在起点左方，此时鼠标拖向第二或者第三象限
                sp.x = ep.x; // 由于Rect的宽必须大于0所以起点的横坐标必须重置，即新起点的横坐标必须与终点的横坐标相同
                dx = abs(dx);// 由于Rect的宽必须大于0所以此时dx必须取绝对值
            }
            int dy = ep.y - sp.y;
            if (dy < 0)
            {// 终点在起点上方，此时鼠标拖向第一或者第二象限
                sp.y = ep.y; // 由于Rect的宽必须大于0所以起点的横坐标必须重置，即新起点的纵坐标必须与终点的纵坐标相同
                dy = abs(dy);// 由于Rect的宽必须大于0所以此时dy必须取绝对值
            }
            
            Rect box(sp.x, sp.y, dx, dy); // 生成方框
            rectangle(*image, box, Scalar(0, 0, 255), 2, LINE_AA); // 将方框绘制到画布
            imshow("鼠标绘制", *image);
            temp.copyTo(*image); // 取得原始画布以避免截取后的内容残留方框痕迹
            imshow("ROI区域", (*image)(box)); // 从画布中截取方框内容并显示
            sp.x = -1;
            sp.y = -1;
        }
            break;
        case EVENT_MOUSEMOVE: // 鼠标拖动中
        {
            if (sp.x > 0 && sp.y > 0)
            {
                ep.x = x < 0 ? 0 : (x > image->cols ? image->cols : x);
                ep.y = y < 0 ? 0 : (y > image->rows ? image->rows : y);
                
                int dx = ep.x - sp.x;
                int dy = ep.y - sp.y;

                Rect box(sp.x, sp.y, dx, dy); // 生成方框
                temp.copyTo(*image); // 取得原始画布以避免画布出现方框拖拽过程中形成的残影
                rectangle(*image, box, Scalar(0, 0, 255), 2, LINE_AA); // 将方框绘制到画布
                imshow("鼠标绘制", *image);
            }
        }
            break;
    }
}

/// <summary>
/// 鼠标绘图
/// </summary>
/// <param name="image"></param>
void QuickDemo::mouse_drawing_demo(Mat& image)
{
    namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
    setMouseCallback("鼠标绘制", on_draw, &image);
    imshow("鼠标绘制", image);
    temp = image.clone(); // 缓存原图(没有上次绘制遗留的痕迹)
}
