// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <direct.h>
#include "opencv2\opencv.hpp"
#include "opencv\highgui.h"
#include "histogram.cpp"
#include "filter.cpp"

using namespace cv;
using namespace std;

int main()
{
	// Get command from user
	int cmd = 0;

	Mat image = imread("c:\\fig309.tif", IMREAD_GRAYSCALE);
	Mat result = image.clone();
	Mat_<float> kernel(3, 3);

	float val = 1.0f / 9;

	kernel << val, val, val, val, val, val, val, val, val;

	applyFilter(image, kernel, result);

	imshow("Processed Image", result);
	imshow("Original Image", image);

	waitKey(0);
	getchar();

    return 0;
}

