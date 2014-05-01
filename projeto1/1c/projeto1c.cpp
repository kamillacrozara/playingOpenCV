#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

void detectBlob(Mat img, string imageName);

int main(int argc, char **argv)
{
    
    /*TODO: use listFiles.cpp to get all the files from a given
            directory*/

    Mat img_original;
    img_original = imread("images/fig1.jpg", IMREAD_GRAYSCALE);
    detectBlob(img_original, "fig1.bmp");
    img_original = imread("images/fig2.jpg", IMREAD_GRAYSCALE);
    detectBlob(img_original, "fig2.bmp");
    img_original = imread("images/fig3.jpg", IMREAD_GRAYSCALE);
    detectBlob(img_original, "fig3.bmp");
    img_original = imread("images/fig4.jpg", IMREAD_GRAYSCALE);
    detectBlob(img_original, "fig4.bmp");
    img_original = imread("images/HoleAnalysis_4.png", IMREAD_GRAYSCALE);
    detectBlob(img_original, "HoleAnalysis_4.bmp");
    return 0; 

}

void detectBlob(Mat img_original, string imageName)
{
    /**
     * Falar no relatório sobre o uso de threshold e Canny para
     * tratamento da image, todos sem sucesso. Verificar as
     * propriedades de GaussianBlur e adaptativeThreshold
     * Canny(img_original, img_original, 0, 1)
     */
    
    Size size(3,3);
    GaussianBlur(img_original, img_original, size , 0);  
    adaptiveThreshold(img_original, img_original, 255, 0, 0, 75, 10);  
    bitwise_not(img_original, img_original);
    
    imwrite("gaussianResult/"+imageName, img_original);

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    
    int spots = 0;
    int blobClassA = 0;
    int blobClassB = 0;

    findContours(img_original, contours, hierarchy, 3, 1);
    
    for(int idx = 0; idx < contours.size(); ++idx)
    {
        if(hierarchy[idx][3] == -1)
        {
            spots +=1;

            if(hierarchy[idx][2] != -1)
            {
                blobClassB += 1;
            
            }else
            {
                blobClassA +=1;
            }
        }    
    }
    cout << "[Imagem " + imageName + "]" << endl;
    cout << "Número de manchas = " << spots << endl;
    cout << "Manchas classe A = " << blobClassA << endl;
    cout << "Manchas classe B = " << blobClassB << endl;

}
