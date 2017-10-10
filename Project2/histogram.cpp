#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <vector>

#include "stdafx.h"
#include "math.h"

#include "opencv2\opencv.hpp"
#include "opencv\highgui.h"

using namespace std;
using namespace cv;

void createHist(Mat &image, vector<float> hist)
{
	// normalize the hist data for fast processing
	int sizeHist = hist.size();
	int maxVal(0);

	for (int p = 0; p < sizeHist; p++)
	{
		if (maxVal < hist[p])
		{
			maxVal = hist[p];
		}
	}

	for (int n = 0; n < sizeHist; n++)
	{
		hist[n] /= maxVal;
		hist[n] *= image.rows;
	}

	Mat histImage(256, image.rows, CV_8U, Scalar(0));

	for (unsigned int i = sizeHist-1; i > 0; i--)
	{
		for (unsigned int j = image.rows - 1; j > ceil(hist[i]) ; j--)
		{
			histImage.at<uchar>(i, j) = 255;
		}
	}

	rotate(histImage, histImage, ROTATE_90_COUNTERCLOCKWISE);

	imshow("Histogram Image", histImage);
}

void showHist(Mat &image)
{
	// histogram array to store
	//float hist[256] = { 0 };

	vector<float> hist;
	hist.assign(256, 0);

	// check if image is empty or not
	if (image.empty())
	{
		cout << "data is not loaded";
	}
	else
	{
		//fill_n(hist, 256, 0);

		uchar *p;
		for (unsigned int i = 0; i < image.rows; i++)
		{
			p = image.ptr<uchar>(i);
			for (unsigned int j = 0; j < image.cols; j++)
			{
				// Find value in image(x, y) and increase the related value in the histogram array by one.
				uchar val = image.at<uchar>(i, j);
				hist[val] += 1.0f;
			}
		}
	}
	
	createHist(image, hist);

	imshow("Image", image);
}