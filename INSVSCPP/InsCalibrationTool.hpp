#include<iostream>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

namespace Calibration{

	class InsCalibrationTool {

		public:
			Mat ManualAffineEstimate(const vector<Point2d>& uncalibratedPoint, const vector<Point2d>& calibratedPoint, bool fullAfine);
			double CalcRMSE(vector<Point2d> predictedPoint, vector<Point2d> calibratedPoint);
			tuple<Mat, double> GetTransform(vector<Point2d> uncalibratedPoint, vector<Point2d> calibratedPoint);

	};

}