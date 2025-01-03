#include<opencv2/opencv.hpp>
#include "InsImageProcessingTool.hpp"
#include "InsShowImageTool.hpp"
using namespace cv;
using namespace InsImageProcessingTool;
using namespace InsShowImageTool;

void FlipTest() {
    Mat mat = imread(R"(D:\20241218\101210\NG3-”‡∏ﬂ.jpg)");
    Mat outMat = Flip(mat, VERTICAL);
    imshow("mat", outMat);
    waitKey(0);
}

void ShowImageTest() {
    Mat mat = imread(R"(D:\Data\OK.bmp)");
    ShowImage(mat);
}

int main(int argc, char* argv[])
{
    //FlipTest();
    ShowImageTest();
}
