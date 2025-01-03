#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

namespace InsShowImageTool {

	Mat ResizeToFit(const Mat& img, int windowWidth, int windowHeight) {
		int imgWidth = img.cols;
		int imgHeight = img.rows;
		double scale = min(static_cast<double>(windowWidth) / imgWidth, static_cast<double>(windowHeight) / imgHeight);
		int newWidth = static_cast<int>(imgWidth * scale);
		int newHeight = static_cast<int>(imgHeight * scale);

		Mat resizedImg;
		resize(img, resizedImg, Size(newWidth, newHeight));

		return resizedImg;
	}

	void ShowImage(Mat mat) {
		string windowName = "ShowImage";
		int initialWidth = 800;
		int initialHeigtht = 600;
		Mat resizedImg = ResizeToFit(mat, initialWidth, initialHeigtht);

		imshow(windowName, resizedImg);
		waitKey(0);
		destroyAllWindows();
	}
}