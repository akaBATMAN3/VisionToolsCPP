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
	/// ��ͼ���������ݵ���ʽ��תͼ��
	/// </summary>
	/// <param name="inputData">����ͼ����������ָ��</param>
	/// <param name="outputData">���ͼ����������ָ��</param>
	/// <param name="width">ͼ����</param>
	/// <param name="height">ͼ��߶�</param>
	/// <param name="channels">����ͨ����</param>
	/// <param name="flipWay">��ת����</param>
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