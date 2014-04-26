#include <iostream>
#include <dirent.h>
#include <vector>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

class ScaleImage
{
	
	private:
		 /* *
		 * Faz a criação de uma nova escala de cinza
		 * que será usada para a requantização.
		 * Os valores extremos, 0 e 255, são mantidos.
		 * Para os valores intermediários é feita a média 
		 * dos valores extremos do intervalo. Por exemplo,
		 * os valores entre 15 e 31 são mapeados para 
		 * 23 = 15+31/2. Percebe-se que a variação entre
		 * os novos valores é igual a 256 dividido pelo
		 * número de bits desejável.
		 *
		 * @param newNumberOfBits: nova número de bits desejado.
		 * Por exemplo, se deseja-se transformar uma imagem 
		 * de 8 bits em uma imagem de 4 bits, deve-se passar
		 * como parâmetro o valor 4.
		 *
		 * @return newGrayScale: vetor com os valores da
		 * nova escala de cinza 
		 * 
		 * */
		vector<int> chunckGrayScale(int newNumberOfBits)
		{
		    vector<int> newGrayScale(newNumberOfBits);
		    newGrayScale.at(0) = 0;
		    newGrayScale.at(newNumberOfBits-1) = 255;


		    if(newNumberOfBits == 2)
		    {
		       return newGrayScale; 
		    }

		    else
		    {
		        int deltaGrayLevel = 256/newNumberOfBits;
		    
		        int prev = ((deltaGrayLevel - 1) + ((deltaGrayLevel-1) + deltaGrayLevel))/2;

		        for(int i = 1; i < newNumberOfBits -1; i++)
		        {
		            newGrayScale.at(i) = prev;
		            prev += deltaGrayLevel;
		        }
		    }
		   return newGrayScale;
		}


	public:
		Mat resizeImage(Mat original_img, int newSize)
		{
			
			if(!original_img.data) 
			{
				throw "Imagem não foi inicializada corretamente.";
				exit(0);
			}

			if(newSize <= 0) 
			{
				throw "Novo tamanho não pode ser 0 ou negativo";
				exit(0);
			}

			int scaleFactor = original_img.size().height/newSize;

			Mat resized_img = Mat::zeros(newSize, newSize, CV_8UC1);

		    for(int i = 2; i < original_img.size().height; i += 2)
		    {
		        for(int j = 2; j < original_img.size().height; j += 2)
		        {
		            resized_img.at<uchar>(i/scaleFactor, j/scaleFactor) = original_img.at<uchar>(i,j);
		        }
		    }
		    if(!resized_img.isContinuous())
		    {
		        cout << "Erro ao fazer redimensionamento da imagem. Imagem não é contínua" << endl;
		    }

		    //imwrite(imageName, resized_img);

		   
		    return resized_img;
		}

		Mat rescaleImageTo512(Mat original_img)
		{
			
			if(!original_img.data) 
			{
				throw "Imagem não foi inicializada corretamente.";
				exit(0);
			}

			Mat resized_img = Mat::zeros(512, 512, CV_8UC1);

			int s1 = 512/original_img.size().height;
			int s2 = 512/original_img.size().width;

			for(int i = 0; i < 512; i++)
			{
			    for(int j = 0; j < 512; j++)
			    {
			        resized_img.at<uchar>(i, j) = original_img.at<uchar>((round(i/s1)), (round(j/s2)));
			    }
			}
			if(!resized_img.isContinuous())
			{
			    cout << "Erro ao fazer redimensionamento da imagem. Imagem não é contínua" << endl;
			}

			return resized_img;
		}

		/* *
		 * Faz o mapeamento para a nova escala de cinza. 
		 *
		 * @param original_img: imagem original a ser requantizada
		 * @param newNumberOfBits: novo número de bits para a imagem requantizada
		 * @param imageName: nome para salvar a imagem em disco
		 * */
		Mat requantizeImage(Mat original_img, int newNumberOfBits)
		{
			
			if(!original_img.data) 
			{
				throw "Imagem não foi inicializada corretamente.";
				exit(0);
			}

			if(newNumberOfBits < 0)
			{
				throw "Novo numero de bits não pode ser negativo";
				exit(0);	
			}

			vector<int> newGrayScale = chunckGrayScale(newNumberOfBits);

			int deltaGrayLeves = 256/newNumberOfBits;

			Mat requantized_img = Mat::zeros(original_img.size().height, original_img.size().width, CV_8UC1);

			int temp =  0;

			for(int i = 0; i < original_img.size().height; i++)
			{
				for(int j = 0; j < original_img.size().width; j++)
				{
					int comparativeGrayLevel = 255; 

					temp = (int)original_img.at<uchar>(i,j);

					for(int count = newGrayScale.size() - 1; count >= 0; count--)
					{

						if(count == 0)
						{

						    if(temp <= comparativeGrayLevel)
						    {
						    
						         requantized_img.at<uchar>(i,j) = newGrayScale.at(count);     
						         break;
						    }


						}
						else if((temp > comparativeGrayLevel-deltaGrayLeves) && (temp <= comparativeGrayLevel))
						{
						    requantized_img.at<uchar>(i,j) = newGrayScale.at(count);
						    break;
						}

						comparativeGrayLevel -= deltaGrayLeves;


					}

				}
			}

			if(!requantized_img.isContinuous())
			{
				cout << "Erro ao fazer redimensionamento da imagem. Imagem não é contínua" << endl;
			}

			return requantized_img;

		}

};

int main(int argc, char **argv)
{
	ScaleImage scale;

	/*TODO: use listFiles.cpp to get all the files from a given
			directory

	vector<string> files = listFiles("images");

	int resizeScale = 512;

	for(int i = 0; i < files.size(); i++)
	{
		cout << files.at(i) << endl;
		Mat img = imread(files.at(i), IMREAD_GRAYSCALE);
		stringstream imageName;
		imageName << "resizedImages/resizedImage" << i << ".bmp";
		cout << imageName.str() << endl;
		cout << resizeScale << endl;
		imwrite(imageName.str(), scale.resizeImage(img, resizeScale/2));
		
		resizeScale = resizeScale/2;
	}*/

	Mat img;

	/**resize images**/
	img = imread("images/Baboon.bmp", IMREAD_GRAYSCALE);
	imwrite("resizedImages/Baboon256.bmp", scale.resizeImage(img, 256));
	imwrite("resizedImages/Baboon128.bmp", scale.resizeImage(img, 128));
	imwrite("resizedImages/Baboon64.bmp", scale.resizeImage(img, 64));
	imwrite("resizedImages/Baboon32.bmp", scale.resizeImage(img, 32));

	img = imread("images/Lena.bmp", IMREAD_GRAYSCALE);
	imwrite("resizedImages/Lena256.bmp", scale.resizeImage(img, 256));
	imwrite("resizedImages/Lena128.bmp", scale.resizeImage(img, 128));
	imwrite("resizedImages/Lena64.bmp", scale.resizeImage(img, 64));
	imwrite("resizedImages/Lena32.bmp", scale.resizeImage(img, 32));
	/**resize images**/
	
	/**rescale images**/
	img = imread("resizedImages/Baboon256.bmp", IMREAD_GRAYSCALE);
	imwrite("rescaledImages/Baboon256To512.bmp", scale.rescaleImageTo512(img));
	img = imread("resizedImages/Baboon128.bmp", IMREAD_GRAYSCALE);
	imwrite("rescaledImages/Baboon128To512.bmp", scale.rescaleImageTo512(img));
	img = imread("resizedImages/Baboon64.bmp", IMREAD_GRAYSCALE);
	imwrite("rescaledImages/Baboon64To512.bmp", scale.rescaleImageTo512(img));
	img = imread("resizedImages/Baboon32.bmp", IMREAD_GRAYSCALE);
	imwrite("rescaledImages/Baboon32To512.bmp", scale.rescaleImageTo512(img));
	
	img = imread("resizedImages/Lena256.bmp", IMREAD_GRAYSCALE);
	imwrite("rescaledImages/Lena256To512.bmp", scale.rescaleImageTo512(img));
	img = imread("resizedImages/Lena128.bmp", IMREAD_GRAYSCALE);
	imwrite("rescaledImages/Lena128To512.bmp", scale.rescaleImageTo512(img));
	img = imread("resizedImages/Lena64.bmp", IMREAD_GRAYSCALE);
	imwrite("rescaledImages/Lena64To512.bmp", scale.rescaleImageTo512(img));
	img = imread("resizedImages/Lena32.bmp", IMREAD_GRAYSCALE);
	imwrite("rescaledImages/Lena32To512.bmp", scale.rescaleImageTo512(img));
	/**rescale images**/

	/*requantize images**/
	img = imread("images/Baboon.bmp", IMREAD_GRAYSCALE);
	imwrite("requantizedImages/Baboon8bits.bmp", scale.requantizeImage(img, 8));
	imwrite("requantizedImages/Baboon4bits.bmp", scale.requantizeImage(img, 4));
	imwrite("requantizedImages/Baboon2bits.bmp", scale.requantizeImage(img, 2));

	img = imread("images/Lena.bmp", IMREAD_GRAYSCALE);
	imwrite("requantizedImages/Lena8bits.bmp", scale.requantizeImage(img, 8));
	imwrite("requantizedImages/Lena4bits.bmp", scale.requantizeImage(img, 4));
	imwrite("requantizedImages/Lena2bits.bmp", scale.requantizeImage(img, 2));
	/*requantize images**/


    return 0; 
}

