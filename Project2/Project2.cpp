// Authored in Visual Studio Environment
// Using OpenCV - Thanks to Itseez ;)

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <direct.h>
#include "opencv2\opencv.hpp"
#include "opencv\highgui.h"
#include "opencv2\core.hpp"
#include "histogram.cpp"

//#include "filter.cpp"

void applyFilterr(Mat & image, Mat_<float> & kernel, Mat & result);

void runHist();
void runHistEqualize();
void runSpatialFilter();
void runLagrangian();

using namespace cv;
using namespace std;

void runHist()
{
	Mat image = imread("c:\\fig323.tif");
	Mat result = image.clone();

	ShowHist(image, result);

	imshow("Original Image", image);
	imshow("Processed Image", result);
}

void runHistEqualize()
{
	Mat image = imread("c:\\fig309.tif");
	Mat result = image.clone();

	EqualizeImageHist(image, result);

	imshow("Original Image", image);
	imshow("Processed Image", result);
}

void runSpatialFilter()
{
	Mat image = imread("c:\\fig340.tif", IMREAD_GRAYSCALE);
	Mat result = image.clone();

	// Applying kernel functions
	float cons(0.0f);

	cout << "Enter kernel constant" << endl;
	cin >> cons;

	// Blurrer kernel matrix
	float val = 1.0f / 9;
	Mat_<float> kern(3, 3);
	Mat_<float> kern_sum(3, 3);

	kern << val, val, val, val, val, val, val, val, val;
	kern_sum << 0, 0, 0, 0, 1, 0, 0, 0, 0;

	kern = kern_sum - kern;
	multiply(kern, Scalar(cons), kern);

	kern = kern_sum + kern;
	applyFilterr(image, kern, result);

	imshow("Original Image", image);
	imshow("Processed Image", result);

	waitKey(0);
}

void runLagrangian()
{
	Mat image = imread("c:\\fig338.tif", IMREAD_GRAYSCALE);
	Mat result = image.clone();
	Mat result2 = image.clone();

	Mat_<float> kern(3, 3);

	kern << 0, 1, 0,
	        1, -4, 1,
			0, 1, 0;

	applyFilterr(image, kern, result);
	filter2D(image, result2, 8, kern);

	imshow("Original Image", image);
	imshow("Processed Image", result);
	imshow("Processed Image2", result2);

	waitKey(0);
}


int main()
{
	int cmd = 0;

	while (true)
	{
		// Enter command as int to navigate in switch case
		cout << "Enter a command to calculate"<<endl;

		cout << "1-) Show histogram of image" << endl;
		cout << "2-) Histogram equalization" << endl;
		cout << "3-) Apply spatial filter" << endl;
		cout << "4-) Apply lagrangian filter" << endl;

		cin >> cmd;

		cout << endl;
		cout << endl;

		switch (cmd)
		{
		case 1:
			runHist();
			break;
		case 2:
			runHistEqualize();
			break;
		case 3:
			runSpatialFilter();
			break;
		case 4:
			runLagrangian();
			break;
		}
	}
	waitKey(0);
	getchar();

    return 0;
}