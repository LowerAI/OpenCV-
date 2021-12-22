# 项目描述
+ 本项目根据B站视频《OpenCV4 C++ 快速入门视频30讲 - 系列合集》编写
+ 源连接[OpenCV4 C++ 快速入门视频30讲 - 系列合集](https://www.bilibili.com/video/BV1i54y1m7tw?p=3&spm_id_from=pageDriver)

# 引用参考


# 课程ppt
## P1 OpenCV4.5.1环境配置与搭建
+ C++项目属性页中“VC++目录”->“包含目录”中添加：
  + D:\SDK\opencv\build\include
  + D:\SDK\opencv\build\include\opencv2
+ C++项目属性页中“VC++目录”->“库目录”中添加：
  + D:\SDK\opencv\build\x64\vc15\lib
+ C++项目属性页中“链接器”->“输入”->“附加目录”中添加：
  + opencv_world454.lib
  + opencv_world454d.lib
  + 注意不能同时添加这两个文件字符串，否则将导致imread读不到图片，只能根据Debug/Release分别添加
+ 系统环境变量->path中添加：
  + D:\SDK\opencv\build\x64\vc15\bin
  + 添加完成后记得一定要重启VS

## P2 001-图像读取与显示

## P3 002-图像色彩空间转换
### 知识点：
+ 1、色彩空间转换函数-cvtColor
```
COLOR_BGR2GRAY = 6 彩色到灰度
COLOR_GRAY2BGR = 8 灰度到彩色
COLOR_BGR2HSV = 40 彩色到HSV
COLOR_GSV2BGR = 54 HSV到彩色
```

+ 2、图像保存-imwrite
```
第一个参数是图像保存路径
第二个参数是图像内存对象
```

```
HSV(Hue, Saturation, Value)是根据颜色的直观特性由A. R. Smith在1978年创建的一种颜色空间, 也称六角锥体模型(Hexcone Model)。

这个模型中颜色的参数分别是：色调（H），饱和度（S），明度（V）。

色调H
用角度度量，取值范围为0°～360°，从红色开始按逆时针方向计算，红色为0°，绿色为120°,蓝色为240°。它们的补色是：黄色为60°，青色为180°,紫色为300°；


饱和度S
饱和度S表示颜色接近光谱色的程度。一种颜色，可以看成是某种光谱色与白色混合的结果。其中光谱色所占的比例愈大，颜色接近光谱色的程度就愈高，颜色的饱和度也就愈高。饱和度高，颜色则深而艳。光谱色的白光成分为0，饱和度达到最高。通常取值范围为0%～100%，值越大，颜色越饱和。


明度V
明度表示颜色明亮的程度，对于光源色，明度值与发光体的光亮度有关；对于物体色，此值和物体的透射比或反射比有关。通常取值范围为0%（黑）到100%（白）。

RGB和CMY颜色模型都是面向硬件的，而HSV（Hue Saturation Value）颜色模型是面向用户的。
```

## P4 003-图像对象的创建与赋值
```
知识点：OpenCV中图像对象的创建与赋值

C++中Mat对象与创建
Python中Numpy数组对象
```

## P5 004-图像像素的读写操作
```
今日分享-知识点：
OpenCV中图像像素的读写操作

C++中的像素遍历与访问
- 数组遍历
- 指针方式遍历
Python中的像素遍历与访问
- 数组遍历
```

## P6 005-图像像素的算术操作

## P7 006-滚动条操作演示-调整图像亮度
`增加滑块调整亮度`

## P8 007-滚动条操作演示-参数传递度
`(修正P7中的回调函数内容)增加对比度滑块`

## P9 008-键盘响应操作

## P10 009-OpenCV自带颜色表操作
```
知识点：Look Up Table(LUT)查找表
解释了LUT查找表的作用与用法，代码实现与API介绍
```

+ applyColorMap(src,dst,COLORMAP)
  + src表示输入图像
  + dst表示输出图像
  + 匹配到的颜色LUT，OpenCV支持13中颜色风格的查找表映射

```
有一张是伪色彩增强的python运行颜色，大家可以自己下载代码尝试
图像是绳蝇！最后一张是OpenCV种支持13色彩风格！都可以运用到伪彩色增强上去！
```

## P11 010-图像像素的逻辑操作


## P12 011-通道分离与合并


## P13 012-图像色彩空间转换
```
知识点：色彩空间与色彩空间转换
+ RGB色彩空间
+ HSV色彩空间
+ YUV色彩空间
+ YCrCb色彩空间

API知识点
+ 色彩空间转换cvtColor
+ 提取指定色彩范围区域InRange
```

## P14 013-图像像素值统计
```
知识点：像素值统计
+ 最小(min)
+ 最大(max)
+ 均值(mean)
+ 标准方差(standard deviation)

API知识点
+ 最大最小值
+ 计算均值与标准方差meanStdDev
```

## P15 014-图像几何形状绘制

## P16 015-随机数与随机颜色

## P17 016-多边形填充与绘制

## P18 017-鼠标操作与响应

## P19 018-图像像素类型转换与归一化
```
归一化：把图像像素的值范围从0~255压缩到0~1之间(压缩图像大小？？)

OpenCV提供了四种归一化的方法
- NORM_MINMAX
- NORM_INF
- NORM_L1
- NORM_L2
最常用的就是NORM_MINMAX归一化方法

相关API函数
normalize(
	InputArray        src, // 输入图像
	InputOutputArray  dst, // 输出图像
	double            alpha = 1, // NORM_MINMAX时候低值
	double            beta = 0, // NORM_MINMAX时候高值
	int               norm_type = NORM_L2, // 只有alpha
	int               dttype, // 默认类型与src一致
	InputArray        mask = noArray() // mask默认值为空
)
```

## P20 019-图像放缩与插值
```
图像插值(Image Interpolation)
最常见的四种插值算法
INTER_NEAREST = 0
INTER_LINEAR = 1
INTER_CUBIC = 2
INTER_LANCZOS = 4
相关的应用场景
几何变换、透视变换、插值计算新像素
resize,
如果size有值，使用size坐缩放插值，否则根据fx与fy卷积。

关于这四种插值算法的详细代码实现与解释
图像处理之三种常见双立方插值算法 - CSDN博客
图像放缩之双立方插值 - CSDN博客
图像放缩之双线性内插值 - CSDN博客
图像处理之Lanczos4采样放缩算法 - CSDN博客
```

## P21 020-图像翻转

## P22 021-图像旋转

## P23 022-视频文件摄像头使用

## P24 023-视频处理与保存
```
SD 标准清晰度
HD 高清

UHD 超高清晰度
```

## P25 024-图像直方图
```
直方图的解释：
图像直方图时图像像素值的统计学特征、计算代价较小，具有图像平缓、旋转、缩放不变性等众多优点，广泛第应用了图像处理的各个领域，特别时灰度图像的阈值分割、基于颜色的图像检索以及图像分类，反向投影跟踪。常见的分为
- 灰度直方图
- 颜色直方图

Bins是指直方图的大小范围，对于像素值取值在0~255之间的，最少右256个bin，此外还可以有16，32，48，128等，256除以bin的大小应该是整数倍

OpenCV中相关API
calcHist(&bgr_plane[0],1,0,Mat(),b_hist,1,bins,ranges);
cv.calcHist([image],[i],None,[256],[0,256])
```

## P26 025-二维直方图


## P27 026-直方图均衡化
```
图像直方图均衡化

图像直方图均衡化可以用于图像增强，对输入图像进行直方图均衡化处理，提升后续对象检测得准确率。在OpenCV人脸检测得代码演示中已经很常见，此外对医学影响图像与卫星遥感图像也经常通过直方图均衡化来提升图像质量。

OpenCV中直方图均衡化得API很简单
- equalizeHist(src,dst)
```


## P28 027-图像卷积操作
```
图像卷积可以看成是一个窗口区域在另外一个大的图像上移动，对每个窗口覆盖的区域都进行点乘得到的值作为中心像素点的输出值。窗口的移动式从左到右，从上到下。窗口可以理解成一个指定大小的二维矩阵，里面有预先指定的值。

相关API(C++)
-blur(
	InputArray    src, // 输入
	OutputArray   dst, // 输出
	Size          ksize, // 窗口大小
	Point         anchor = Point(-1,-1), // 默认值
	int           borderType = BORDER_DEFAULT // 默认值
)
```

## P29 028-高斯模糊
