#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace InsImageProcessingTool {
	
	enum FlipWay {
		HORIZONTAL_AND_VERTICAL = -1,
		VERTICAL = 0,
		HORIZONTAL = 1
	};

	/// <summary>
	/// uchar转换为Mat
	/// </summary>
	/// <param name="data">图像uchar数组数据指针</param>
	/// <param name="width">图像宽度</param>
	/// <param name="height">图像高度</param>
	/// <param name="channels">像素通道数量</param>
	/// <returns>数组数据指针转换后的Mat</returns>
	Mat ucharToMat(uchar* data, int width, int height, int channels) {
		try {
			Mat image(height, width, (channels == 3 ? CV_8UC3 : CV_8UC1), data);

			return image.clone();
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// Mat转换为uchar
	/// </summary>
	/// <param name="image">输入图像</param>
	/// <param name="outputData">图像uchar数组数据指针</param>
	void MatTouchar(Mat image, uchar* outputData) {
		try {
			memcpy(outputData, image.data, image.total() * image.elemSize());
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 图像翻转
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="flipWay">翻转方向</param>
	/// <returns>翻转后的图像</returns>
	Mat Flip(InputArray src, FlipWay flipWay) {
		try {
			Mat dst;
			flip(src, dst, static_cast<int>(flipWay));

			return dst;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 图像对比度和亮度处理
	/// </summary>
	/// <param name="img">输入图像</param>
	/// <param name="gain">对比度</param>
	/// <param name="bias">明亮度</param>
	/// <returns>处理后的图像</returns>
	Mat GainAndBias(Mat img, double gain, double bias) {
		try {
			Mat outImg;
			img.convertTo(outImg, -1, gain, bias);

			return outImg;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 伽马矫正
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="gamma">伽马值</param>
	/// <returns>伽马矫正后的图像</returns>
	Mat GammaCorrection(Mat src, double gamma) {
		try {
			Mat lookUpTable(1, 256, CV_8U); // 像素查找表
			uchar* p = lookUpTable.ptr();
			for (int i = 0; i < 256; ++i) p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);

			Mat dst;
			LUT(src, lookUpTable, dst);

			return dst;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 形态学操作
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="morphType">形态学类型</param>
	/// <param name="morphShape">结构元类型</param>
	/// <param name="kernelWidth">结构元宽度</param>
	/// <param name="kernelHeight">结构元高度</param>
	/// <param name="anchor">结构元原点</param>
	/// <returns>形态学操作后的图像</returns>
	Mat MorphologyOperation(Mat src, MorphTypes morphType, MorphShapes morphShape, int kernelWidth, int kernelHeight, Point anchor) {
		try {
			Mat kernel = getStructuringElement(morphShape, Size(kernelWidth, kernelHeight), anchor);
			Mat dst;
			morphologyEx(src, dst, morphType, kernel);

			return dst;
		}
		catch (exception e) {
		}
	}
	/// <summary>
	/// 图像卷积操作
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="kernel">卷积核</param>
	/// <returns>卷积后的图像</returns>
	Mat Convolution(Mat src, Mat kernel) {
		try {
			Mat dst;
			filter2D(src, dst, src.depth(), kernel);

			return dst;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 图像仿射变换
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="transX">X方向平移</param>
	/// <param name="transY">Y方向平移</param>
	/// <param name="angle">旋转角度，负数逆时针旋转</param>
	/// <param name="scale">缩放</param>
	/// <returns>仿射变换后的图像</returns>
	Mat AffineTrans(Mat src, double transX, double transY, double angle, double scale) {
		try {
			// 获取图像尺寸
			int h = src.rows;
			int w = src.cols;

			// 计算图像中心点
			Point2f center(w / 2.0 + transX, h / 2.0 + transY);

			// 获取旋转矩阵
			Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);

			// 计算旋转后的图像边界
			double cos = abs(rotationMatrix.at<double>(0, 0));
			double sin = abs(rotationMatrix.at<double>(0, 1));

			// 计算新图像的尺寸
			int new_w = int((h * sin) + (w * cos));
			int new_h = int((h * cos) + (w * sin));

			// 调整旋转矩阵的平移部分
			rotationMatrix.at<double>(0, 2) += (new_w / 2.0) - center.x;
			rotationMatrix.at<double>(1, 2) += (new_h / 2.0) - center.y;

			// 执行旋转
			Mat rotatedImage;
			warpAffine(src, rotatedImage, rotationMatrix, Size(new_w, new_h));

			return rotatedImage;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 均值滤波
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="kernelSize">卷积核大小</param>
	/// <returns></returns>
	Mat Blur(Mat src, int kernelSize) {
		try {
			Mat dst;
			blur(src, dst, Size(kernelSize, kernelSize));

			return dst;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 中值滤波
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="kernelSize">卷积核大小</param>
	/// <returns></returns>
	Mat MedianBlur(Mat src, int kernelSize) {
		try {
			Mat dst;
			medianBlur(src, dst, kernelSize);

			return dst;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 高斯采样
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="kernelSize">卷积核大小</param>
	/// <returns></returns>
	Mat Gaussian(Mat src, int kernelSize) {
		try {
			Mat dst;
			GaussianBlur(src, dst, Size(kernelSize, kernelSize), 0);

			return dst;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 图像量化
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="level">量化级别</param>
	/// <returns>量化后的图像</returns>
	Mat Quantization(Mat src, int level) {
		try {
			Mat quantized = src.clone();
			int step = level / 2;
			for (int i = 0; i < quantized.rows; ++i) {
				for (int j = 0; j < quantized.cols; ++j) {
					uchar pixel = src.at<uchar>(i, j);
					quantized.at<uchar>(i, j) = (pixel / step) * step;
				}
			}

			return quantized;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// 二次采样
	/// </summary>
	/// <param name="src">输入图像</param>
	/// <param name="scale">采样比例</param>
	/// <returns>采样后的图像</returns>
	Mat SubSampling(Mat src, int scale) {
		try {
			Mat dst;
			resize(src, dst, Size(src.rows / scale, src.cols / scale), 0, 0, INTER_LINEAR);

			return dst;
		}
		catch (exception e) {

		}
	}
}