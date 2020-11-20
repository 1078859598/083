#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
	Mat srcMat = imread("C:/Users/HS/Desktop/3.jpg");
	Mat hsv, gray, bin1, bin2, bin;
	Mat Result;

	resize(srcMat, srcMat, Size(400, 400));
	cvtColor(srcMat, hsv, CV_BGR2HSV);

	srcMat.copyTo(Result);

	int minH = 0;
	int maxH = 20;

	int minS = 43;
	int maxS = 255;

	int minV = 55;
	int maxV = 255;

	inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), bin1);
	minH = 160;
	maxH = 180;
	inRange(hsv, Scalar(minH, minS, minV), Scalar(maxH, maxS, maxV), bin2);

	bitwise_or(bin1, bin2, bin);

	vector<vector<Point>> contours;
	findContours(bin, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	Point2f vtx[4];
	for (int i = 0; i < contours.size(); i++) {


		RotatedRect rbox = minAreaRect(contours[i]);
		rbox.points(vtx);
		float width = rbox.size.width;
		float height = rbox.size.height;
		float prop = width / height;
		float area = width * height;
		if (area > 1000)
		{
			for (int j = 0; j < 4; j++)
			{
				line(Result, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 255, 255), 2, CV_AA);
			}
		}
	}
	imshow("srcMat", srcMat);
	imshow("result", Result);
	waitKey(0);
}