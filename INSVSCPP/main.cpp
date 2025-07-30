#include<opencv2/opencv.hpp>
#include "InsImageProcessingTool.hpp"
#include "InsShowImageTool.hpp"
using namespace cv;
using namespace InsImageProcessingTool;
using namespace InsShowImageTool;

void FlipTest() {
    Mat mat = imread(R"(D:\Data\OK.bmp)");
    Mat outMat = Flip(mat, VERTICAL);
    imshow("mat", outMat);
    waitKey(0);
}
void ShowImageTest() {
    Mat mat = imread(R"(D:\Data\OK.bmp)");
    ShowImage(mat);
}
void GammaTest() {
    Mat mat = imread(R"(D:\Data\OK.bmp)");
    Mat outMat = MorphologyOperation(mat, MORPH_ERODE, MORPH_ELLIPSE, 11, 11, Point(-1, -1));
    ShowImage(outMat);
}
void Rotatetest() {
    Mat mat = imread(R"(E:\3.Image\2.���ź���˫���ε��ͼ��\OK_2D - ����.jpg)");
    Mat outMat = AffineTrans(mat, 0.0, 0.0, 45.0, 1.0);
    imwrite(R"(E:\3.Image\2.���ź���˫���ε��ͼ��\111.jpg)", outMat);
    ShowImage(outMat);

}
int main(int argc, char* argv[])
{
    //FlipTest();
    //ShowImageTest();
    //GammaTest();
    Rotatetest();
}