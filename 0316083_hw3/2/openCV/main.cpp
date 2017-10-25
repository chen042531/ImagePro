#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include <math.h>
#include "cv.h"
using namespace std;
using namespace cv;

int main() {

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread("Fig02_Slide14.tif", CV_LOAD_IMAGE_GRAYSCALE);

	// Create a grayscale output image matrix
	Mat DstImg1 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg2 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg3 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg4 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg5 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg6 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg7 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg8 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	// Copy each pixel of the source image to the output image
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
			//DstImg.at<uchar>(i,j)= 48.370*pow(SrcImg.at<uchar>(i,j),0.3);
			if (((SrcImg.at<uchar>(i, j) & 0x1)) == 1)
				DstImg1.at<uchar>(i, j) = 255;
			else
				DstImg1.at<uchar>(i, j) = 0;

		}
	}
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
			
			if (((SrcImg.at<uchar>(i, j) & 0x2 >> 1) == 1))
				DstImg2.at<uchar>(i, j) = 255;
			else
				DstImg2.at<uchar>(i, j) = 0;

		}
	}
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
			
			if (((SrcImg.at<uchar>(i, j) & 0x4) >> 2) == 1)
				DstImg3.at<uchar>(i, j) = 255;
			else
				DstImg3.at<uchar>(i, j) = 0;

		}
	}
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
		
			if (((SrcImg.at<uchar>(i, j) & 0x8) >> 3) == 1)
				DstImg4.at<uchar>(i, j) = 255;
			else
				DstImg4.at<uchar>(i, j) = 0;

		}
	}
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
			
			if (((SrcImg.at<uchar>(i, j) & 0x10) >> 4) == 1)
				DstImg5.at<uchar>(i, j) = 255;
			else
				DstImg5.at<uchar>(i, j) = 0;

		}
	}
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
		
			if (((SrcImg.at<uchar>(i, j) & 0x20) >> 5) == 1)
				DstImg6.at<uchar>(i, j) = 255;
			else
				DstImg6.at<uchar>(i, j) = 0;

		}
	}
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
	
			if (((SrcImg.at<uchar>(i, j) & 0x40) >> 6) == 1)
				DstImg7.at<uchar>(i, j) = 255;
			else
				DstImg7.at<uchar>(i, j) = 0;

		}
	}
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
			
			if (((SrcImg.at<uchar>(i, j) & 0x80) >> 7) == 1)
				DstImg8.at<uchar>(i, j) = 255;
			else
				DstImg8.at<uchar>(i, j) = 0;

		}
	}
	// Show images
	imshow("Input Image", SrcImg);
	imshow("Output Image1", DstImg1);
	imshow("Output Image2", DstImg2);
	imshow("Output Image3", DstImg3);
	imshow("Output Image4", DstImg4);
	imshow("Output Image5", DstImg5);
	imshow("Output Image6", DstImg6);
	imshow("Output Image7", DstImg7);
	imshow("Output Image8", DstImg8);

	// Write output images
	imwrite("Output Image1.tif", DstImg1);
	imwrite("Output Image2.tif", DstImg2);
	imwrite("Output Image3.tif", DstImg3);
	imwrite("Output Image4.tif", DstImg4);
	imwrite("Output Image5.tif", DstImg5);
	imwrite("Output Image6.tif", DstImg6);
	imwrite("Output Image7.tif", DstImg7);
	imwrite("Output Image8.tif", DstImg8);
	
	waitKey(0);
	return 0;
}