#include <stdio.h>
#include <iostream>
#include <direct.h>
#include <vector>

#include "stdafx.h"
#include "math.h"

#include "opencv2\opencv.hpp"
#include "opencv\highgui.h"
#include "histogram.h"

using namespace std;
using namespace cv;

vector<float> * GetImageHist(Mat & image);

void PlotHistData(Mat &image, vector<float> * histP, Mat & result)
{
	vector<float> hist = *histP;

	// Normalize the hist data for fast processing
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
	

	delete histP;

	result = histImage;
}

void ShowHist(Mat & image, Mat & result)
{
	// histogram array to store
	//float hist[256] = { 0 };

	// check if image is empty or not
	if (image.empty())
	{
		cout << "data is not loaded";
	}
	else
	{
		PlotHistData(image, GetImageHist(image), result);
	}
}

vector<float> * GetImageHist(Mat & image)
{
	uchar *p(NULL);
	int depth = image.depth();
	int vectorSize = pow(2, depth);
	vector<float> * hist = new vector<float>(256);

	for (unsigned int i = 0; i < image.rows; i++)
	{
		p = image.ptr<uchar>(i);
		for (unsigned int j = 0; j < image.cols; j++)
		{
			// Find value in image(x, y) and increase the related value in the histogram array by one.
			uchar val = image.at<uchar>(i, j);
			hist->at(val) = hist->at(val) + 1.0f;
		}
	}

	//delete p;

	return hist;
}

vector<float> * GetHistEqualizerFunc(Mat & image)
{
	// Get histogram of input image
	vector<float> * HHr = GetImageHist(image);
	vector<float> * PPr_k = new vector<float>(HHr->size());
	
	// Create probablity function from input image histogram
	// Now hist points to -----> p(r_k)
	int totPixel = image.rows * image.cols;
	for (unsigned int i = 0; i < HHr->size(); i++)
	{
		PPr_k->at(i) = HHr->at(i) / totPixel;
	}
	
	// Create array for histogram equalizer function with same size as histogram array of input image
	// Now PPs_k points to ----> p(s_k)
	vector<float> * PPs_k = new vector<float>(PPr_k->size());

	// maxIntensity is points to (L - 1)
	unsigned int maxIntensity = 255; 
	
	for (unsigned int i = 0; i < PPs_k->size(); i++)
	{
		// Integral from 0 to i value s(k) = T(r) = (L - 1) * sum(p(k))
		float sumOfProb(0);
		for (unsigned int j = 0; j <= i; j++)
		{
			sumOfProb += PPr_k->at(j);
		}

		PPs_k->at(i) = round((maxIntensity * sumOfProb));

		// Clear integral var
		sumOfProb = 0;
	}

	// Delete unused vectors
	delete PPr_k;

	// Now wekcan return transformation function
	return PPs_k;
}

void EqualizeImageHist(Mat & image, Mat & resImg)
{
	vector<float> * tranFunc = GetHistEqualizerFunc(image); 
	Mat result = image.clone();

	uchar * p;
	uchar * r;
	for (unsigned int i = 0; i < image.rows; i++)
	{
		p = image.ptr<uchar>(i);
		r = result.ptr<uchar>(i);

		for (unsigned int j = 0; j < image.cols; j++)
		{
			int val = p[j];
			int out = tranFunc->at(val);
			r[j] = out;
		}
	}

	resImg = result;
}