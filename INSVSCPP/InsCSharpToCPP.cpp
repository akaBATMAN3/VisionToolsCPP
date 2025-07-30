#include <iostream>
#include <core/mat.hpp>
#include "InsImageProcessingTool.hpp"
#include "InsShowImageTool.hpp"
using namespace std;
using namespace cv;
using namespace InsImageProcessingTool;
using namespace InsShowImageTool;

namespace InsCSharpToCPP {
	/// <summary>
	/// 以图像数组数据的形式翻转图像
	/// </summary>
	/// <param name="inputData">输入图像数组数据指针</param>
	/// <param name="outputData">输出图像数组数据指针</param>
	/// <param name="width">图像宽度</param>
	/// <param name="height">图像高度</param>
	/// <param name="channels">像素通道数</param>
	/// <param name="flipWay">翻转方向</param>
	extern "C" _declspec(dllexport) void FlipImage(
		uchar* inputData,
		uchar* outputData,
		int width,
		int height,
		int channels,
		FlipWay flipWay
	) {
		try {
			Mat image = ucharToMat(inputData, width, height, channels);
			Mat flippedImg = Flip(image.clone(), flipWay);
			MatTouchar(flippedImg, outputData);
		}
		catch (exception) {

		}
	}
}