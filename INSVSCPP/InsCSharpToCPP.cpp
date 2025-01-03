#include <iostream>
#include <core/mat.hpp>
#include "InsImageProcessingTool.hpp"
#include "InsShowImageTool.hpp"
using namespace std;
using namespace cv;
using namespace InsImageProcessingTool;
using namespace InsShowImageTool;

namespace InsCSharpToCPP {

	Mat GetMatFromBitMap(uchar* data, int width, int height, int channels) {
		Mat image(height, width, (channels == 3 ? CV_8UC3 : CV_8UC1), data);

		return image.clone();
	}
	void GetPtrFromMat(Mat image, uchar* outputData) {
		memcpy(outputData, image.data, image.total() * image.elemSize());
	}
	extern "C" _declspec(dllexport) void FlipImage(
		uchar* inputData,
		uchar* outputData,
		int width,
		int height,
		int channels,
		FlipWay flipWay
	) {
		Mat image = GetMatFromBitMap(inputData, width, height, channels);
		Mat flippedImg = Flip(image.clone(), flipWay);
		GetPtrFromMat(flippedImg, outputData);
		//ShowImage(flippedImg);
	}
}