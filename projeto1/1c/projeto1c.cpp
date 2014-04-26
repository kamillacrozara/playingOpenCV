#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

void detectBlob(Mat img);

int main(int argc, char **argv)
{
    
    if(argv[1] == 0)
	{
		cout << "No image to display!" << endl;
		return 0;
	} 

    Mat img_original = imread(argv[1], IMREAD_GRAYSCALE);
    
    detectBlob(img_original);

    return 0; 

}

void detectBlob(Mat img_original)
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
    
    imwrite("gaussianResult.bmp", img_original);

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
                cout << "hole" << endl;
                blobClassB += 1;
            
            }else
            {
                blobClassA +=1;
            }
        }    
    }

    cout << "Número de manchas = " << spots << endl;
    cout << "Manchas classe A = " << blobClassA << endl;
    cout << "Manchas classe B = " << blobClassB << endl;

}
