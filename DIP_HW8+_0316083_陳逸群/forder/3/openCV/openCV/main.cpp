#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <highgui.h>
#include <complex>
#include <math.h>
#include <valarray>
#include "cv.h"
using namespace std;
using namespace cv;
typedef valarray<valarray<complex<double>>> val2d;
const double pi = 2.0 * acos(0);
int main() {

	// Read input images
	// Fig3.tif is in openCV\bin\Release
	Mat SrcImg = imread("Q3.tif", CV_LOAD_IMAGE_GRAYSCALE);


	// Create a grayscale output image matrix
	Mat DstImg = Mat(SrcImg.rows, SrcImg.cols, CV_8UC1);

	
	// Copy each pixel of the source image to the output image
	Mat DstImg2 = Mat(DstImg.rows, DstImg.cols, CV_8UC1);
	double w1 = 2.0 * pi / SrcImg.cols;
	double w2 = 2.0 * pi / SrcImg.rows;
	// Copy each pixel of the source image to the output image
	val2d in(valarray<complex<double>>(SrcImg.rows), SrcImg.cols);
	val2d out1(valarray<complex<double>>(SrcImg.rows), SrcImg.cols);
	val2d out2(valarray<complex<double>>(SrcImg.rows), SrcImg.cols);


	Mat padded;
	int m = getOptimalDFTSize(SrcImg.rows);
	int n = getOptimalDFTSize(SrcImg.cols);
	//用zero padding對影像邊界拓展
	copyMakeBorder(SrcImg, padded, 0, m - SrcImg.rows, 0, n - SrcImg.cols, BORDER_CONSTANT, Scalar::all(0));
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
	Mat complexImg;
	merge(planes, 2, complexImg);
	
	
	
	
	
	//dft
	for (int i = 0; i<SrcImg.rows; ++i)
		for (int j = 0; j<SrcImg.cols; ++j)
		{
			in[i][j] = SrcImg.at<uchar>(i, j);
		}

	for (int i = 0; i<SrcImg.rows; ++i)
		for (int j = 0; j<SrcImg.cols; ++j)
		{
			for (int k = 0; k<SrcImg.cols; ++k)
			out1[i][j] += in[k][j] * polar(1.0, -k*j*w1);

		}

	for (int i = 0; i<SrcImg.cols; ++i)
		for (int j = 0; j<SrcImg.rows; ++j)
		{
			for (int k = 0; k < SrcImg.rows; ++k) {
				out2[i][j] += out1[k][j] * polar(1.0, -k*j*w2);
			}
			DstImg.at<uchar>(i, j) = (256 / log(256))*log(abs(out2[i][j])+1);
		
		}
	dft(complexImg, complexImg);


	//分離通道，planes[0]為實數部分，planes[1]為虛數部分
	split(complexImg, planes);
	

	//取強度
	magnitude(planes[0], planes[1], planes[0]);
	Mat magI = planes[0];
	magI += Scalar::all(1);
	log(magI, magI);
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));


	//將區塊重排，讓原點在影像的中央
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));
	Mat q1(magI, Rect(cx, 0, cx, cy));
	Mat q2(magI, Rect(0, cy, cx, cy));
	Mat q3(magI, Rect(cx, cy, cx, cy));

	Mat tmp;
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	q1.copyTo(tmp);
	q2.copyTo(q1);
	tmp.copyTo(q2);


	normalize(magI, magI, 0, 1, CV_MINMAX);
	
	// Show images
	imshow("Input Image", SrcImg);
	imshow("頻譜", magI);

	// Write output images
	imwrite("Q4_output.tif", magI);

	waitKey(0);
	return 0;
}
