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
	/// ucharת��ΪMat
	/// </summary>
	/// <param name="data">ͼ��uchar��������ָ��</param>
	/// <param name="width">ͼ����</param>
	/// <param name="height">ͼ��߶�</param>
	/// <param name="channels">����ͨ������</param>
	/// <returns>��������ָ��ת�����Mat</returns>
	Mat ucharToMat(uchar* data, int width, int height, int channels) {
		try {
			Mat image(height, width, (channels == 3 ? CV_8UC3 : CV_8UC1), data);

			return image.clone();
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// Matת��Ϊuchar
	/// </summary>
	/// <param name="image">����ͼ��</param>
	/// <param name="outputData">ͼ��uchar��������ָ��</param>
	void MatTouchar(Mat image, uchar* outputData) {
		try {
			memcpy(outputData, image.data, image.total() * image.elemSize());
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// ͼ��ת
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="flipWay">��ת����</param>
	/// <returns>��ת���ͼ��</returns>
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
	/// ͼ��ԱȶȺ����ȴ���
	/// </summary>
	/// <param name="img">����ͼ��</param>
	/// <param name="gain">�Աȶ�</param>
	/// <param name="bias">������</param>
	/// <returns>������ͼ��</returns>
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
	/// ٤�����
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="gamma">٤��ֵ</param>
	/// <returns>٤��������ͼ��</returns>
	Mat GammaCorrection(Mat src, double gamma) {
		try {
			Mat lookUpTable(1, 256, CV_8U); // ���ز��ұ�
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
	/// ��̬ѧ����
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="morphType">��̬ѧ����</param>
	/// <param name="morphShape">�ṹԪ����</param>
	/// <param name="kernelWidth">�ṹԪ���</param>
	/// <param name="kernelHeight">�ṹԪ�߶�</param>
	/// <param name="anchor">�ṹԪԭ��</param>
	/// <returns>��̬ѧ�������ͼ��</returns>
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
	/// ͼ��������
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="kernel">�����</param>
	/// <returns>������ͼ��</returns>
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
	/// ͼ�����任
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="transX">X����ƽ��</param>
	/// <param name="transY">Y����ƽ��</param>
	/// <param name="angle">��ת�Ƕȣ�������ʱ����ת</param>
	/// <param name="scale">����</param>
	/// <returns>����任���ͼ��</returns>
	Mat AffineTrans(Mat src, double transX, double transY, double angle, double scale) {
		try {
			// ��ȡͼ��ߴ�
			int h = src.rows;
			int w = src.cols;

			// ����ͼ�����ĵ�
			Point2f center(w / 2.0 + transX, h / 2.0 + transY);

			// ��ȡ��ת����
			Mat rotationMatrix = getRotationMatrix2D(center, angle, scale);

			// ������ת���ͼ��߽�
			double cos = abs(rotationMatrix.at<double>(0, 0));
			double sin = abs(rotationMatrix.at<double>(0, 1));

			// ������ͼ��ĳߴ�
			int new_w = int((h * sin) + (w * cos));
			int new_h = int((h * cos) + (w * sin));

			// ������ת�����ƽ�Ʋ���
			rotationMatrix.at<double>(0, 2) += (new_w / 2.0) - center.x;
			rotationMatrix.at<double>(1, 2) += (new_h / 2.0) - center.y;

			// ִ����ת
			Mat rotatedImage;
			warpAffine(src, rotatedImage, rotationMatrix, Size(new_w, new_h));

			return rotatedImage;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// ��ֵ�˲�
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="kernelSize">����˴�С</param>
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
	/// ��ֵ�˲�
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="kernelSize">����˴�С</param>
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
	/// ��˹����
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="kernelSize">����˴�С</param>
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
	/// ͼ������
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="level">��������</param>
	/// <returns>�������ͼ��</returns>
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
	/// ���β���
	/// </summary>
	/// <param name="src">����ͼ��</param>
	/// <param name="scale">��������</param>
	/// <returns>�������ͼ��</returns>
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