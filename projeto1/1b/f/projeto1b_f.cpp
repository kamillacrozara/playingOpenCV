#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Mat requantizeImage(Mat img, int numberOfBits, string newImageName);
vector<int> chunckGrayScale(int numberOfBits);

int main(int argc, char **argv)
{
    
    if(argv[1] == 0)
	{
		cout << "No image to display!" << endl;
		return 0;
	}


    Mat img_original = imread(argv[1], IMREAD_GRAYSCALE);
    
    requantizeImage(img_original, 2, "2bits_test.bmp");

    return 0; 
}


/* *
 * Faz a criação da nova escala de cinza.
 * Os valores extremos, 0 e 255, são mantidos.
 * Para os valores intermediários é feita a média 
 * dos valores extremos do intervalo. Por exemplo,
 * os valores entre 15 e 31 são mapeados para 
 * 23 = 15+31/2. Percebe-se que a variação entre
 * os novos valores é igual a 256 dividido pelo
 * número de bits desejável.
 *
 * @param numberOfBits: nova número de bits desejado.
 * Por exemplo, se deseja-se transformar uma imagem 
 * de 8 bits em uma imagem de 4 bits, deve-se passar
 * como parâmetro o valor 4.
 *
 * @return newGrayScale: vetor com os valores da
 * nova escala de cinza 
 * 
 * */
vector<int> chunckGrayScale(int numberOfBits)
{
    vector<int> newGrayScale(numberOfBits);
    newGrayScale.at(0) = 0;
    newGrayScale.at(numberOfBits-1) = 255;


    if(numberOfBits == 2)
    {
       return newGrayScale; 
    }

    else
    {
        int deltaGrayLevel = 256/numberOfBits;
    
        int prev = ((deltaGrayLevel - 1) + ((deltaGrayLevel-1) + deltaGrayLevel))/2;

        for(int i = 1; i < numberOfBits -1; i++)
        {
            newGrayScale.at(i) = prev;
            prev += deltaGrayLevel;
        }
    }
   return newGrayScale;
}


/* *
 * Faz o mapeamento para a nova escala de cinza. 
 *
 * @param original_img: imagem original a ser requantizada
 * @param numberOfBits: novo número de bits para a imagem requantizada
 * @param imageName: nome para salvar a imagem em disco
 * */
Mat requantizeImage(Mat original_img, int numberOfBits, string imageName)
{
    vector<int> newGrayScale = chunckGrayScale(numberOfBits);
    
    int deltaGrayLeves = 256/numberOfBits;

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

    imwrite(imageName, requantized_img);

   
    return requantized_img;
}
