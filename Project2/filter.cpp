#include "stdafx.h"
#include "opencv2\opencv.hpp"

using namespace cv;
using namespace std;

void applyFilterr(Mat & image, Mat_<float> & kernel, Mat & result)
{
	for (int i = 0; i < image.rows; i++)
	{

		// Input image row 
		// i mean Image
		// Curr, Prev, Next points to Middle, Previous and Next rows
		uchar * iCurr = image.ptr<uchar>(i);
		uchar * iPrev(0);
		uchar * iNext(0);
		
		// Output image row
		uchar * oCurr = result.ptr<uchar>(i);

		// To check we are not out of bounds for candidate kernel matrix
		bool inbound = false;

		for (int j = 0; j < image.cols; j++)
		{
			// Checking bounds
			if((i - 1 >= 0) && (i + 1 < image.rows) && j > 1 && j < image.cols)
			{
				iPrev = image.ptr<uchar>(i - 1);
				iNext = image.ptr<uchar>(i + 1);
				inbound = true;
			}

			if (inbound)
			{
				// Apply kernel, by orienting K(x,y) for candiate pixel value
				float val = 1.0f *  (iPrev[j] * kernel(0,0)) + (iPrev[j + 1] * kernel(0,1)) + (iPrev[j + 2] * kernel(0,2))+
									(iCurr[j] * kernel(1,0)) + (iCurr[j + 1] * kernel(1,1)) + (iCurr[j + 2] * kernel(1,2))+ 
									(iNext[j] * kernel(2,0)) + (iNext[j + 1] * kernel(2,1)) + (iNext[j + 2] * kernel(2,2));

				// DEBUG PURPOSES ONLY
				oCurr[j] = static_cast<uchar>(val);
			}
			else
			{
				// If we are in out of bound, we have to copy in these points. Otherwise, we may apply 
				// only matching points by multiplying adjacent Kernel points. This method is not preferred to make code simpler.
				oCurr[j] = iCurr[j];
			}
		}


	}
}