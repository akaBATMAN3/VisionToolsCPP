#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

namespace InsShowImageTool {
	Mat ResizeToFit(const Mat& img, int windowWidth, int windowHeight);
	void ShowImage(Mat mat);
}