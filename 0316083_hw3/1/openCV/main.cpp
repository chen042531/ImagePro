#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include <math.h>
#include "cv.h"
using namespace std;
using namespace cv;

int main(){

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread("Fig01_Slide10.tif", CV_LOAD_IMAGE_GRAYSCALE);

	// Create a grayscale output image matrix
	Mat DstImg1 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg2 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg3 = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	// Copy each pixel of the source image to the output image
	for(int i=0; i<SrcImg.rows; ++i)
		for(int j=0; j<SrcImg.cols; ++j)
		{
			DstImg1.at<uchar>(i, j) = (256 / pow(256, 0.3))*pow(SrcImg.at<uchar>(i, j), 0.3);
			DstImg2.at<uchar>(i, j) = (256 / pow(256, 0.4))*pow(SrcImg.at<uchar>(i, j), 0.4);
			DstImg3.at<uchar>(i, j) = (256 / pow(256, 0.6))*pow(SrcImg.at<uchar>(i, j), 0.6);
		}

	// Show images
	imshow("Input Image", SrcImg);
	imshow("Output Image 0.3", DstImg1);
	imshow("Output Image 0.4", DstImg2);
	imshow("Output Image 0.6", DstImg3);

	// Write output images
	imwrite("Image_3.tif", DstImg1);
	imwrite("Image_4.tif", DstImg2);
	imwrite("Image_6.tif", DstImg3);
	waitKey(0);
	return 0;
}