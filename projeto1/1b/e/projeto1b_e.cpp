#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

Mat resizeImageTo512(Mat img, string newImageName);

int main(int argc, char **argv)
{

    Mat baboon_32 = imread("baboon_32.bmp", IMREAD_GRAYSCALE);
    Mat baboon_64 = imread("baboon_64.bmp", IMREAD_GRAYSCALE);
    Mat baboon_128 = imread("baboon_128.bmp", IMREAD_GRAYSCALE);
    Mat baboon_256 = imread("baboon_256.bmp", IMREAD_GRAYSCALE);
 
    resizeImageTo512(baboon_32, "baboon32To512.bmp");
    resizeImageTo512(baboon_64, "baboon64To512.bmp");
    resizeImageTo512(baboon_128, "baboon128To512.bmp");
    resizeImageTo512(baboon_256, "baboon256To512.bmp");
    
    Mat lena_32 = imread("lena_32.bmp", IMREAD_GRAYSCALE);
    Mat lena_64 = imread("lena_64.bmp", IMREAD_GRAYSCALE);
    Mat lena_128 = imread("lena_128.bmp", IMREAD_GRAYSCALE);
    Mat lena_256 = imread("lena_256.bmp", IMREAD_GRAYSCALE);
 
    resizeImageTo512(lena_32, "lena32To512.bmp");
    resizeImageTo512(lena_64, "lena64To512.bmp");
    resizeImageTo512(lena_128, "lena128To512.bmp");
    resizeImageTo512(lena_256, "lena256To512.bmp");
    
    return 0; 

}

Mat resizeImageTo512(Mat original_img, string imageName)
{
    Mat resized_img = Mat::zeros(512, 512, CV_8UC1);

    int s1 = 512/original_img.size().height;
    int s2 = 512/original_img.size().width;

    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j <512; j++)
        {
            resized_img.at<uchar>(i, j) = original_img.at<uchar>((round(i/s1)), (round(j/s2)));
        }
    }
    if(!resized_img.isContinuous())
    {
        cout << "Erro ao fazer redimensionamento da imagem. Imagem não é contínua" << endl;
    }

    imwrite(imageName, resized_img);

   
    return resized_img;
}
