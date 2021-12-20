#include "quickopencv.h"

void QuickDemo::colorSpace_Demo(Mat& image)
{
    Mat gray, hsv;

    // HSV�� ɫ��(H:0~180)�����Ͷ�(S)������(V)
    // ת��
    cvtColor(image, hsv, COLOR_BGR2HSV);
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // ��ʾ
    imshow("HSV", hsv);
    imshow("�Ҷ�", gray);

    // ����
    imwrite("F:/hsv.png", hsv);
    imwrite("F:/gray.png", gray);
}

/// <summary>
/// ����ͼ��
/// </summary>
/// <param name="image"></param>
void QuickDemo::mat_creation_demo(Mat& image)
{
    Mat m1, m2;
    m1 = image.clone();
    image.copyTo(m2);

    // �����հ�ͼ��
    // Mat m3 = Mat::ones(Size(8, 8), CV_8UC3); // ע���ʱֻ�Ὣͨ��1�е�������Ϊ1
    Mat m3 = Mat::zeros(Size(400, 400), CV_8UC3); // CV_8UC1-8:8λ��U��usigned�޷��ŵģ�C��char�ַ���1�ǵ�ͨ���ġ��ۺ���������8λ��ͨ���޷��ŵ��ַ����飻Size(8, 8)��ʾ8��x8��
    m3 = Scalar(255, 0, 0);

    //std::cout << "width:" << m3.cols << " height:" << m3.rows << " channels:" << m3.channels() << std::endl;
    //std::cout << m3 << std::endl;
    imshow("ͼ��", m3);
}

/// <summary>
/// ��д��������
/// </summary>
/// <param name="image"></param>
void QuickDemo::pixel_visit_demo(Mat& image)
{
    int w = image.cols; // ��
    int h = image.rows; // ��
    int dims = image.channels(); // ͨ����

    // �������
    for (int row = 0; row < h; row++)
    {
        for (int col = 0; col < w; col++)
        {
            switch (dims)
            {
            case 1: // ��ͨ�� �Ҷ�ͼ��
            {
                int pv = image.at<uchar>(row, col);
                image.at<uchar>(row, col) = 255 - pv;
            }
            break;
            case 3: // 3ͨ�� ��ɫͼ��
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

    // ָ�����
    //for (int row = 0; row < h; row++)
    //{
    //    uchar* current_row = image.ptr<uchar>(row);
    //    for (int col = 0; col < w; col++)
    //    {
    //        switch (dims)
    //        {
    //        case 1: // ��ͨ�� �Ҷ�ͼ��
    //        {
    //            int pv = *current_row;
    //            *current_row++ = 255 - pv;
    //        }
    //        break;
    //        case 3: // 3ͨ�� ��ɫͼ��
    //        {
    //            *current_row++ = 255 - *current_row;
    //            *current_row++ = 255 - *current_row;
    //            *current_row++ = 255 - *current_row;
    //        }
    //        break;
    //        }
    //    }
    //}
    imshow("���ض�д��ʾ", image);
}

/// <summary>
/// ������
/// </summary>
/// <param name="image"></param>
void QuickDemo::operators_demo(Mat& image)
{
    Mat dst = Mat::zeros(image.size(), image.type());
    //dst = image + Scalar(50, 50, 50);
    Mat m = Mat::zeros(image.size(), image.type());
    m = Scalar(5, 5, 5);
    //multiply(image, m, dst); // ���

    int w = image.cols; // ��
    int h = image.rows; // ��
    int dims = image.channels(); // ͨ����

    // �ӷ�
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

    add(image, m, dst); // ���
    subtract(image, m, dst); // ���
    divide(image, m, dst); // ���

    imshow("��������", dst);
}

/// <summary>
/// ����ص��¼�
/// </summary>
/// <param name="pos">���鵱ǰֵ</param>
/// <param name="userdata">�û����ݵ�����</param>
static void on_track(int pos, void* userdata)
{
    // �ж��Ƿ�nullptr
    if (userdata == 0)
    {
        return;
    }
    Mat* src = (Mat*)userdata;
    Mat m, dst;
    m = Mat::zeros(src->size(), src->type());
    m = Scalar(pos, pos, pos); // ��ʱpos����createTrackbar�д����lightness(����ֵ)
    dst = Mat::zeros(src->size(), src->type());
    add(*src, m, dst);
    imshow("���ȵ���", dst);
}

/// <summary>
/// ���齻������
/// </summary>
/// <param name="image"></param>
void QuickDemo::tracking_bar_demo7(Mat& image)
{
    namedWindow("���ȵ���", WINDOW_AUTOSIZE);
    int max_value = 100;
    int lightness = 50;
    createTrackbar("Value Bar", "���ȵ���", &lightness, max_value, on_track, &image);
    on_track(50, 0);
}

/// <summary>
/// ���Ȼ���ص��¼�
/// </summary>
/// <param name="pos">��ǰ����ֵ</param>
/// <param name="userdata">�û����ݵ�����</param>
static void on_lightness(int pos, void* userdata)
{
    Mat* src = (Mat*)userdata;
    Mat m = Mat::zeros(src->size(), src->type());
    Mat dst = Mat::zeros(src->size(), src->type());
    addWeighted(*src, 1.0, m, 0, pos, dst);
    imshow("������Աȶȵ���", dst);
}

/// <summary>
/// �ԱȶȻ���ص��¼�
/// </summary>
/// <param name="pos">��ǰ�Աȶ�ֵ</param>
/// <param name="userdata">�û����ݵ�����</param>
static void on_contrast(int pos, void* userdata)
{
    Mat* src = (Mat*)userdata;
    Mat m = Mat::zeros(src->size(), src->type());
    Mat dst = Mat::zeros(src->size(), src->type());
    double contrast = pos / 100.0;
    addWeighted(*src, contrast, m, 0.0, 0, dst);
    imshow("������Աȶȵ���", dst);
}

/// <summary>
/// ���齻������
/// </summary>
/// <param name="image"></param>
void QuickDemo::tracking_bar_demo8(Mat& image)
{
    namedWindow("������Աȶȵ���", WINDOW_AUTOSIZE);
    int lightness = 50;
    int max_value = 100;
    int contrast_value = 100;
    createTrackbar("Value Bar", "������Աȶȵ���", &lightness, max_value, on_lightness, &image);
    createTrackbar("Contrast Bar", "������Աȶȵ���", &contrast_value, 200, on_contrast, &image);
    on_lightness(50, &image);
}

/// <summary>
/// �����涯
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
        case 27: // Esc �˳�
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
        imshow("������Ӧ", dst);
    }
}

/// <summary>
/// �ı���ɫ���
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
        imshow("��ɫ���", dst);
    }
}

/// <summary>
/// ���ص��߼�����
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
    //bitwise_and(m1, m2, dst); // ��
    //bitwise_or(m1, m2, dst); // ��
    //bitwise_not(image, dst); // ��(ȡ��)
    //dst = ~image; // ��(ȡ��)
    bitwise_xor(m1, m2, dst); // ���(�Ȼ���ȡ��)
    imshow("����λ����", dst);
}

/// <summary>
/// ͨ��������ϲ�
/// </summary>
/// <param name="image"></param>
void QuickDemo::channels_demo(Mat& image)
{
    std::vector<Mat> mv;
    split(image, mv);
    /*imshow("��ɫ", mv[0]);
    imshow("��ɫ", mv[1]);
    imshow("��ɫ", mv[2]);*/

    Mat dst;
    /*mv[1] = 0;
    mv[2] = 0;
    merge(mv, dst);
    imshow("��ɫ", dst);*/

    /*mv[0] = 0;
    mv[2] = 0;
    merge(mv, dst);
    imshow("��ɫ", dst);*/

    /*mv[0] = 0;
    mv[1] = 0;
    merge(mv, dst);
    imshow("��ɫ", dst);*/

    dst = Mat::zeros(image.size(), image.type());
    int from_to[] = { 0,2,1,1,2,0 };
    mixChannels(&image, 1, &dst, 1, from_to, 3);
    imshow("ͨ�����", dst);
}