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
	Mat image = imread("c:\\fig309.tif", IMREAD_GRAYSCALE);
	
	showHist(image);

	waitKey(0);
	getchar();

    return 0;
}

