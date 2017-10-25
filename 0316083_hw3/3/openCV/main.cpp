#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include "cv.h"
using namespace std;
using namespace cv;
/*�e������*/
void drawHistImg(const Mat &src, Mat &dst) {
	int histSize = 256;
	float histMaxValue = 0;
	for (int i = 0; i<histSize; i++) {
		float tempValue = src.at<float>(i);
		if (histMaxValue < tempValue) {
			histMaxValue = tempValue;
		}
	}

	float scale = (0.8* 256) / histMaxValue;
	for (int i = 0; i<histSize; i++) {
		int intensity = static_cast<int>(src.at<float>(i)*scale);
		line(dst, Point(i, 255), Point(i, 255 - intensity), Scalar(0));
	}
}
int main(){

	int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange = { range };

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread("Fig03_Slide23.tif", CV_LOAD_IMAGE_GRAYSCALE);
	//Mat SrcImg_second;
	
	// Create a grayscale output image matrix
	Mat SrcImg_t = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg_t = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg_dark = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg_bright = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg_lowContrast = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg_highContrast = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	Mat DstImg_exposure = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);
	equalizeHist(SrcImg, SrcImg_t);
	// Copy each pixel of the source image to the output image
	/*�t*/
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{	
			DstImg_dark.at<uchar>(i, j) = (SrcImg.at<uchar>(i, j))/3;
		}
	}

	/*�G*/
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
			DstImg_bright.at<uchar>(i, j) = (SrcImg.at<uchar>(i, j))/2 +125;
		}
	}

	/*�C���*/
	for (int i = 0; i < SrcImg.rows; ++i) {
		for (int j = 0; j < SrcImg.cols; ++j)
		{
			DstImg_t.at<uchar>(i, j) = (SrcImg.at<uchar>(i, j)) / 2 + 62;
		}
	}
	equalizeHist(DstImg_t, DstImg_lowContrast);
	/*�����*/
	equalizeHist(SrcImg_t, DstImg_highContrast);
	
	/*�L�n*/
	for (int i = 0; i < SrcImg_t.rows; ++i) {
		for (int j = 0; j < SrcImg_t.cols; ++j)
		{
			if ((SrcImg_t.at<uchar>(i, j))*1.05 > 255) {
				DstImg_t.at<uchar>(i, j) = 255;
			}
			else {
				DstImg_t.at<uchar>(i, j) = (SrcImg_t.at<uchar>(i, j))*1.05;
			}

		}
	}
	equalizeHist(DstImg_t, DstImg_exposure);
	/*�L�n*/
	Mat histImg_exposure;
	calcHist(&DstImg_exposure, 1, 0, Mat(), histImg_exposure, 1, &histSize, &histRange);
	Mat showHistImg_exposure(255, 255, CV_8UC1, Scalar(255));  //�⪽��Ϩq�b�@��256*256�j���v���W
	drawHistImg(histImg_exposure, showHistImg_exposure);
	/*�����*/
	/*
	Mat histImg_highContrast;
	calcHist(&DstImg_highContrast, 1, 0, Mat(), histImg_highContrast, 1, &histSize, &histRange);
	Mat showHistImg_highContrast(255, 255, CV_8UC1, Scalar(255));  //�⪽��Ϩq�b�@��256*256�j���v���W
	drawHistImg(histImg_highContrast, showHistImg_highContrast);
	*/
	Mat histImg_lowContrast;
	calcHist(&DstImg_lowContrast, 1, 0, Mat(), histImg_lowContrast, 1, &histSize, &histRange);
	Mat showHistImg_lowContrast(255, 255, CV_8UC1, Scalar(255));  //�⪽��Ϩq�b�@��256*256�j���v���W
	drawHistImg(histImg_lowContrast, showHistImg_lowContrast);
	// Show images

	imshow("�t", DstImg_dark);
	imshow("�G", DstImg_bright);
	imshow("�C���", DstImg_lowContrast);
	imshow("�����", DstImg_highContrast);
	imshow("�L�n", DstImg_exposure);
	imshow("���", SrcImg);
	//imshow("Output Image2", DstImg);
	imshow("�C���@�Ԧ��������", showHistImg_lowContrast);
	imshow("�L�n���@�Ԧ��������", showHistImg_exposure);
	// Write output images
	imwrite("origin.tif", SrcImg);
	imwrite("dark.tif", DstImg_dark);
	imwrite("bright.tif", DstImg_bright);
	imwrite("lowContrast.tif", DstImg_lowContrast);
	imwrite("highContrast.tif", DstImg_highContrast);
	imwrite("exposure.tif", DstImg_exposure);
	imwrite("exhist.tif", showHistImg_exposure);
	imwrite("hchist.tif", showHistImg_lowContrast);
	waitKey(0);
	return 0;
}
