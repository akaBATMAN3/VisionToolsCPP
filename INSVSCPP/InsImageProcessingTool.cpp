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

	Mat Flip(InputArray src, FlipWay flipWay) {
		Mat dst;
		flip(src, dst, static_cast<int>(flipWay));
		
		return dst;
	}
}