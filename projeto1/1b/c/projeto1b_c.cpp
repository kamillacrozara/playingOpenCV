#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Mat resizeImage(Mat img, int newSize, string newImageName);

int main(int argc, char **argv)
{

    if(argv[1] == 0 || argv[2] == 0)
	{
		cout << "No image to display!" << endl;
		return 0;
	}
    Mat img_1_512_512;
    Mat img_2_512_512;
   
    img_1_512_512 = imread(argv[1], IMREAD_GRAYSCALE);
    img_2_512_512 = imread(argv[2], IMREAD_GRAYSCALE);

    if(img_1_512_512.channels() != 1 || img_1_512_512.size().height != 512 || img_1_512_512.size().width !=512)
    {
        cout << "Image 1 is not in grayscale or size is not 512x512" << endl;
        return 0;
    }
    if(img_2_512_512.channels() != 1 || img_2_512_512.size().height != 512 || img_2_512_512.size().width !=512)
    {
        cout << "Image 2 is not in grayscale or size is not 512x512" << endl;
        return 0;
    }
   
    resizeImage(resizeImage(resizeImage(resizeImage(img_1_512_512, 256, "baboon_256.bmp"), 128, "baboon_128.bmp"), 64, "baboon_64.bmp"), 32, "baboon_32.bmp");
    resizeImage(resizeImage(resizeImage(resizeImage(img_2_512_512, 256, "lena_256.bmp"), 128, "lena_128.bmp"), 64, "lena_64.bmp"), 32, "lena_32.bmp");

    return 0; 

}

Mat resizeImage(Mat original_img, int newSize, string imageName)
{
    Mat resized_img = Mat::zeros(newSize, newSize, CV_8UC1);

    for(int i = 2; i < original_img.size().height; i += 2)
    {
        for(int j = 2; j < original_img.size().height; j += 2)
        {
            resized_img.at<uchar>(i/2, j/2) = original_img.at<uchar>(i,j);
        }
    }
    if(!resized_img.isContinuous())
    {
        cout << "Erro ao fazer redimensionamento da imagem. Imagem não é contínua" << endl;
    }

    imwrite(imageName, resized_img);

   
    return resized_img;
}
