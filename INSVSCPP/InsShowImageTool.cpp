#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

namespace InsShowImageTool {

	/// <summary>
	/// ָ�����ڴ�С��ͼ��ȱ�����ʾ
	/// </summary>
	/// <param name="img">����ͼ��</param>
	/// <param name="windowWidth">���ڿ��</param>
	/// <param name="windowHeight">���ڸ߶�</param>
	/// <returns>���ź��ͼ��</returns>
	Mat ResizeToFit(const Mat& img, int windowWidth, int windowHeight) {
		try {
			int imgWidth = img.cols;
			int imgHeight = img.rows;
			double scale = min(static_cast<double>(windowWidth) / imgWidth, static_cast<double>(windowHeight) / imgHeight);
			int newWidth = static_cast<int>(imgWidth * scale);
			int newHeight = static_cast<int>(imgHeight * scale);

			Mat resizedImg;
			resize(img, resizedImg, Size(newWidth, newHeight));

			return resizedImg;
		}
		catch (exception e) {

		}
	}
	/// <summary>
	/// ��ʾͼ��
	/// </summary>
	/// <param name="mat">����ͼ��</param>
	void ShowImage(Mat mat) {
		try {
			string windowName = "ShowImage";
			int initialWidth = 800;
			int initialHeigtht = 600;
			Mat resizedImg = ResizeToFit(mat, initialWidth, initialHeigtht);

			imshow(windowName, resizedImg);
			waitKey(0);
			destroyAllWindows();
		}
		catch (exception e) {

		}
	}
}