#include <iostream>
#include <cmath>
#include <boost/math/distributions/normal.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class FuzzyIntensityTransform
{

	private:

		int fuziffyContrast(int valor_pixel_original, int min_dark, int max_dark, int min_gray, int max_gray, int min_bright, int max_bright, int increment)
		{
			int valor_novo_pixel;

			//se um pixel é escuro, faça-o mais escuro
			if(valor_pixel_original >= min_dark && valor_pixel_original < max_dark)
			{
				if(valor_pixel_original <= min_dark + increment)
				{
					valor_novo_pixel = min_dark;
				}
				else
				{
					valor_novo_pixel = valor_pixel_original - increment;
				}

			}
			//se um pixel é cinza, então faça-o cinza
			if(valor_pixel_original >= min_gray && valor_pixel_original < max_gray)
			{	
				valor_novo_pixel = valor_pixel_original;

			}

			//se um pixel é claro, então faça-o mais claro
			if(valor_pixel_original >= min_bright && valor_pixel_original < max_bright)
			{
				if(valor_pixel_original <= max_bright - increment)
				{
					valor_novo_pixel = max_bright;
				}
				else
				{
					valor_novo_pixel = valor_pixel_original + increment;
				}
			}

			return valor_novo_pixel;

		}




	public:

		Mat fuzzyfyIntesity(Mat img, int min_dark, int max_dark, int min_gray, int max_gray, int min_bright, int max_bright, int increment)
		{
			if(!img.data)
			{
				cout << "Erro ao incializar imagem" << endl;
				exit(-1);
			}

			Mat output_img = Mat::zeros(img.size().width, img.size().height, img.type());

			for(int i = 0; i < img.size().height; i++)
			{
				for(int j = 0; j < img.size().width; j++)
				{
					output_img.at<uchar>(i,j) = fuziffyContrast((int)img.at<uchar>(i,j), min_dark, max_dark, min_gray, max_gray, min_bright, max_bright, increment);	
				}
			}

		    return output_img;
		}

};


int main(int argc, char **argv)
{
	if(argv[1] == 0)
	{
		cout << "No image to display!" << endl;
		return 0;
	}

	Mat img = imread(argv[1], IMREAD_GRAYSCALE);
    

	int min_dark = 0;
	int max_dark = 50;
	int min_gray = 51;
	int max_gray = 205;
	int min_bright = 206;
	int max_bright = 255;
	int increment = 1;

    FuzzyIntensityTransform f;
    
    imwrite("result/output.bmp", f.fuzzyfyIntesity(img, min_dark, max_dark, min_gray, max_gray, min_bright, min_bright, increment));

    return 0; 
    
}


