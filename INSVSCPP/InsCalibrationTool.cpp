#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace Calibration {

    class InsCalibrationTool {

        public:
            /// <summary>
            /// 计算旋转矩阵
            /// </summary>
            /// <param name="uncalibratedPoint">未矫正点</param>
            /// <param name="calibratedPoint">已矫正点</param>
            /// <param name="fullAfine"></param>
            /// <returns>旋转矩阵</returns>
            Mat ManualAffineEstimate(const std::vector<Point2d>& uncalibratedPoint, const std::vector<Point2d>& calibratedPoint, bool fullAfine)
            {
                try {
                    Mat out(2, 3, CV_64F);
                    int size = 2 * (int)uncalibratedPoint.size();

                    if (fullAfine)
                    {
                        Mat matM(size, 6, CV_64F);
                        Mat matP(size, 1, CV_64F);
                        int contPt = 0;
                        for (int i = 0; i < size; i++)
                        {
                            Mat therow = Mat::zeros(1, 6, CV_64F);
                            if (i % 2 == 0)
                            {
                                therow.at<double>(0, 0) = uncalibratedPoint[contPt].x;
                                therow.at<double>(0, 1) = uncalibratedPoint[contPt].y;
                                therow.at<double>(0, 2) = 1;
                                therow.row(0).copyTo(matM.row(i));
                                matP.at<double>(i, 0) = calibratedPoint[contPt].x;
                            }
                            else
                            {
                                therow.at<double>(0, 3) = uncalibratedPoint[contPt].x;
                                therow.at<double>(0, 4) = uncalibratedPoint[contPt].y;
                                therow.at<double>(0, 5) = 1;
                                therow.row(0).copyTo(matM.row(i));
                                matP.at<double>(i, 0) = calibratedPoint[contPt].y;
                                contPt++;
                            }
                        }
                        Mat sol;
                        solve(matM, matP, sol, DECOMP_SVD);
                        out = sol.reshape(0, 2);
                    }
                    else
                    {
                        Mat matM(size, 4, CV_64F);
                        Mat matP(size, 1, CV_64F);
                        int contPt = 0;
                        for (int i = 0; i < size; i++)
                        {
                            Mat therow = Mat::zeros(1, 4, CV_64F);
                            if (i % 2 == 0)
                            {
                                therow.at<double>(0, 0) = uncalibratedPoint[contPt].x;
                                therow.at<double>(0, 1) = uncalibratedPoint[contPt].y;
                                therow.at<double>(0, 2) = 1;
                                therow.row(0).copyTo(matM.row(i));
                                matP.at<double>(i, 0) = calibratedPoint[contPt].x;
                            }
                            else
                            {
                                therow.at<double>(0, 0) = -uncalibratedPoint[contPt].y;
                                therow.at<double>(0, 1) = uncalibratedPoint[contPt].x;
                                therow.at<double>(0, 3) = 1;
                                therow.row(0).copyTo(matM.row(i));
                                matP.at<double>(i, 0) = calibratedPoint[contPt].y;
                                contPt++;
                            }
                        }
                        Mat sol;
                        solve(matM, matP, sol, DECOMP_SVD);
                        out.at<double>(0, 0) = sol.at<double>(0, 0);
                        out.at<double>(0, 1) = sol.at<double>(1, 0);
                        out.at<double>(0, 2) = sol.at<double>(2, 0);
                        out.at<double>(1, 0) = -sol.at<double>(1, 0);
                        out.at<double>(1, 1) = sol.at<double>(0, 0);
                        out.at<double>(1, 2) = sol.at<double>(3, 0);
                    }

                    return out;
                }
                catch (exception e) {

                }
            }
            /// <summary>
            /// 计算RMSE
            /// </summary>
            /// <param name="predictedPoint">根据计算的转换关系求出的点</param>
            /// <param name="calibratedPoint">已矫正点</param>
            /// <returns>RMSE</returns>
            double CalcRMSE(vector<Point2d> predictedPoint, vector<Point2d> calibratedPoint) {
                try {
                    double RMSE = 0.0;
                    for (int i = 0; i < predictedPoint.size(); ++i) {
                        RMSE += pow(calibratedPoint[i].x - predictedPoint[i].x, 2) + pow(calibratedPoint[i].y - predictedPoint[i].y, 2);
                    }

                    return sqrt(RMSE / predictedPoint.size());
                }
                catch (exception e) {

                }
            }
            /// <summary>
            /// 计算旋转矩阵
            /// </summary>
            /// <param name="uncalibratedPoint">未矫正点</param>
            /// <param name="calibratedPoint">已矫正点</param>
            /// <returns>旋转矩阵，RMSE</returns>
            tuple<Mat, double> GetTransform(vector<Point2d> uncalibratedPoint, vector<Point2d> calibratedPoint) {
                try {
                    for (int i = 0; i < calibratedPoint.size(); ++i) { // 修正机械手坐标
                        calibratedPoint[i].x = 2 * calibratedPoint[0].x - calibratedPoint[i].x;
                        calibratedPoint[i].y = 2 * calibratedPoint[0].y - calibratedPoint[i].y;
                    }

                    Mat affine;
                    estimateRigidTransform(uncalibratedPoint, calibratedPoint, true).convertTo(affine, CV_64F); // 调用cv库计算旋转矩阵
                    if (affine.empty()) affine = ManualAffineEstimate(uncalibratedPoint, calibratedPoint, true); // 手动计算旋转矩阵
                    double A = affine.at<double>(0, 0);
                    double B = affine.at<double>(0, 1);
                    double C = affine.at<double>(0, 2);
                    double D = affine.at<double>(1, 0);
                    double E = affine.at<double>(1, 1);
                    double F = affine.at<double>(1, 2);

                    vector<Point2d> predictedPoint;
                    for (int i = 0; i < uncalibratedPoint.size(); ++i) { // 未矫正点代入旋转矩阵计算
                        Point2d tempPoint;
                        tempPoint.x = A * uncalibratedPoint[i].x + B * uncalibratedPoint[i].y + C;
                        tempPoint.y = D * uncalibratedPoint[i].x + E * uncalibratedPoint[i].y + F;
                        predictedPoint.push_back(tempPoint);
                    }

                    double RMSE = CalcRMSE(predictedPoint, calibratedPoint);

                    return make_tuple(affine, RMSE);
                }
                catch (exception e) {

                }
            }
    };
    
}