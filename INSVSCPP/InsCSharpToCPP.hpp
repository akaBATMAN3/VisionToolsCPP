#include <iostream>
#include <core/mat.hpp>
#include "InsImageProcessingTool.hpp"
using namespace std;
using namespace cv;
using namespace InsImageProcessingTool;

namespace InsCSharpToCPP {

	extern "C" _declspec(dllexport) void FlipImage(
		uchar * inputData,
		uchar * outputData,
		int width,
		int height,
		int channels,
		FlipWay flipWay
	);
}