#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class Filtering
{

private:
	Mat addPadding(Mat img_original)
	{
		int paddNumOfRows = 2*img_original.rows;
		int paddNumOfColumns = 2*img_original.cols;

		Mat img_padded = Mat::zeros(paddNumOfRows, paddNumOfColumns, img_original.type());

		img_original.copyTo(img_padded(Rect(paddNumOfRows/4, paddNumOfColumns/4, img_original.rows, img_original.cols)));

		return img_padded;
	}

	Mat removePadding(Mat img_padded)
	{
		int originalNumOfLines = img_padded.rows/2;

		int originalNumOfColumns = img_padded.cols/2;

		Mat img_original = Mat::zeros(originalNumOfLines, originalNumOfColumns, img_padded.type());

		img_padded(Rect(originalNumOfLines/2, originalNumOfColumns/2, img_original.rows, img_original.cols)).copyTo(img_original);

		return img_original; 
	}

public:

	Mat applyDFT(Mat img_original)
	{

		Mat img_padded = addPadding(img_original);

		imwrite("result/output_padded.bmp", img_padded);
		//void dft(InputArray src, OutputArray dst, int flags=0, int nonzeroRows=0)
		
		//Moreover, the frequency domains range is much larger than its spatial 
		//counterpart. Therefore, we store these usually at least in a float format. 
		//Therefore we’ll convert our input image to this type and expand it with 
		//another channel to hold the complex values:

		Mat planes[] = {Mat_<float>(img_padded), Mat::zeros(img_padded.size(), CV_32F)};
	    
	    Mat complexI;

	    //Creates one multichannel array out of several single-channel ones
	    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	    dft(complexI, complexI);            // this way the result may fit in the source matrix

	    //Divides a multi-channel array into several single-channel arrays.
	    //The functions split split a multi-channel array into separate single-channel arrays:
	    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

	    //The function magnitude calculates the magnitude of 2D vectors 
	    //formed from the corresponding elements of x and y arrays:

		/*x – floating-point array of x-coordinates of the vectors.
		  y – floating-point array of y-coordinates of the vectors; it must have the same size as x.
		  magnitude – output array of the same size and type as x.
		*/
    	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude

    	Mat img_magnitude = planes[0];


    	img_magnitude += Scalar::all(1);                    // switch to logarithmic scale
    	
    	//log(img_magnitude, img_magnitude);
    	// crop the spectrum, if it has an odd number of rows or columns
	    img_magnitude = img_magnitude(Rect(0, 0, img_magnitude.cols & -2, img_magnitude.rows & -2));

    	return shiftDFT(img_magnitude); 

	}


	Mat inverseDFT(Mat apply_mask)
	{

		Mat planes[] = {Mat_<float>(apply_mask), Mat::zeros(apply_mask.size(), CV_32F)};
	    
	    Mat complexI;

	    //Creates one multichannel array out of several single-channel ones
	    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

	    //inverse DFT
	    idft(complexI, complexI);            // this way the result may fit in the source matrix

	    //Divides a multi-channel array into several single-channel arrays.
	    //The functions split split a multi-channel array into separate single-channel arrays:
	    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))

	    //The function magnitude calculates the magnitude of 2D vectors 
	    //formed from the corresponding elements of x and y arrays:

		/*x – floating-point array of x-coordinates of the vectors.
		  y – floating-point array of y-coordinates of the vectors; it must have the same size as x.
		  magnitude – output array of the same size and type as x.
		*/
    	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude

    	Mat img_magnitude = planes[0];

		return img_magnitude;
	}

	Mat shiftDFT(Mat img_dft)
	{
		

	    // rearrange the quadrants of Fourier image  so that the origin is at the image center
	    int cx = img_dft.cols/2;
	    int cy = img_dft.rows/2;

	    Mat q0(img_dft, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	    Mat q1(img_dft, Rect(cx, 0, cx, cy));  // Top-Right
	    Mat q2(img_dft, Rect(0, cy, cx, cy));  // Bottom-Left
	    Mat q3(img_dft, Rect(cx, cy, cx, cy)); // Bottom-Right

	    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	    q0.copyTo(tmp);
	    q3.copyTo(q0);
	    tmp.copyTo(q3);

	    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	    q2.copyTo(q1);
	    tmp.copyTo(q2);

	    //normalize(img_dft, img_dft, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
	                      
	                                           // viewable image form (float between values 0 and 1).
	    //img_dft.convertTo(img_dft, CV_8UC3, 255.0); 
    	imwrite("result/img_dft_shift.bmp", img_dft);
	    return img_dft;
	}

	float calculateDistance(int k, int l, int P, int Q)
	{
		float d = sqrt( pow((k-P/2), 2) + pow((l-Q/2), 2) );

		return d;
	}


	Mat lowPassIdeal(Mat img_original, int D_0)
	{

		//get image with DFT and shift
		Mat img_dft_shift = applyDFT(img_original);


		Mat mask = Mat::zeros(img_dft_shift.rows, img_dft_shift.cols, img_dft_shift.type());

		int d = 0;
		//create mask
		for(int i = 0; i<img_dft_shift.rows; i++)
		{
			for(int j = 0; j<img_dft_shift.cols; j++)
			{
				d = calculateDistance(i, j, img_original.rows, img_original.rows);
				if(d <= D_0)
				{
					mask.at<float>(i,j) = 1;
				}else
				{
					mask.at<float>(i,j) = 0;
				}
			}
		}

		Mat apply_mask = mask * img_dft_shift;

		    //final.convertTo(final, CV_8UC3, 255.0); 
    	imwrite("result/apply_mask.bmp", apply_mask);

		//undo shift
		Mat img_undo_shift = shiftDFT(apply_mask);

		//inverse DFT
		Mat img_idft = inverseDFT(img_undo_shift);

		//final.convertTo(final, CV_8UC3, 255.0); 
    	imwrite("result/inverse_dft.bmp", img_idft);

		Mat undo_padding = removePadding(img_idft);

		return undo_padding;

	}

	Mat highPassIdeal(Mat img_dft_shift){}

	Mat lowPassButterWorth(Mat img_dft_shift){}

	Mat hihgPassButterWorth(Mat img_dft_shift){}

};

int main(int argc, char **argv)
{
	Mat img = imread(argv[1], IMREAD_GRAYSCALE);

	int D_0 = 60;
	
	if(img.empty())
	{
		cout << "No image to display!" << endl;
		return -1;
	}
    
    Filtering f;

    Mat final = f.lowPassIdeal(img, D_0);

    final.convertTo(final, CV_8UC3, 255.0); 
    imwrite("result/output_fourier.bmp", final);

    return 0; 
    
}