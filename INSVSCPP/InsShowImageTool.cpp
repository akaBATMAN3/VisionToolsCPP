#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

namespace InsShowImageTool {

	/// <summary>
	/// 指定窗口大小将图像等比例显示
	/// </summary>
	/// <param name="img">输入图像</param>
	/// <param name="windowWidth">窗口宽度</param>
	/// <param name="windowHeight">窗口高度</param>
	/// <returns>缩放后的图像</returns>
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
	/// 显示图像
	/// </summary>
	/// <param name="mat">输入图像</param>
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