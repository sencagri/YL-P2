// Project2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <direct.h>
#include "opencv2\opencv.hpp"
#include "opencv\highgui.h"
#include "histogram.cpp"

using namespace cv;
using namespace std;

int main()
{
	// Get command from user
	int cmd = 0;

	Mat image = imread("c:\\fig323.tif", IMREAD_GRAYSCALE);
	
	showHist(image);
	//histEqualize(image);
	

	waitKey(0);
	getchar();

    return 0;
}

