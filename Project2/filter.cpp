#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <vector>

#include "stdafx.h"
#include "math.h"

#include "opencv2\opencv.hpp"
#include "opencv\highgui.h"

using namespace cv;
using namespace std;

void applyFilter(Mat & image, Mat_<float> kernel, Mat & result)
{
	// This is constant k, points to 𝑔(𝑥,𝑦)=𝑓(𝑥,𝑦)+𝑘 ∗[𝑓(𝑥,𝑦)−𝑓̅(𝑥,𝑦)]
	float k(0.0);
	cout << "Enter constant value for spatial filtering";
	cin >> k;

	uchar * kernelPrevP = kernel.ptr<uchar>(0);
	uchar * kernelCurrP = kernel.ptr<uchar>(1);
	uchar * kernelNextP = kernel.ptr<uchar>(2);

	for (unsigned int i = 0; i < image.rows; i++)
	{
		// Input image row 
		uchar * iCurr = image.ptr<uchar>(i);
		uchar * iPrev(0);
		uchar * iNext(0);
		if (i - 1 > -1)
		{
			iPrev = image.ptr<uchar>(i - 1);
		}
		else if (i + 1 <= image.rows)
		{
			iNext = image.ptr<uchar>(i + 1);
		}

		// Output image row
		uchar * oCurr = image.ptr<uchar>(i);

		for (unsigned int j = 0; i < image.cols; j++)
		{
			float val = 1.0f * (iPrev[j] * kernelPrevP[0]) + (iPrev[j + 1] * kernelPrevP[1]) + (iPrev[j + 1] * kernelPrevP[j + 2]) +
				(iCurr[j] * kernelCurrP[0]) + (iCurr[j + 1] * kernelCurrP[1]) + (iCurr[j + 1] * kernelCurrP[j + 2]) +
				(iNext[j] * kernelNextP[0]) + (iNext[j + 1] * kernelNextP[1]) + (iNext[j + 1] * kernelNextP[j + 2]);

			oCurr[j] = (int)val;
		}
	}
}