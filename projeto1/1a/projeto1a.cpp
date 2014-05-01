#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;


//
void changeIntensity(Mat input, Rect &roi, int flag);
        
int main(int argc, char **argv)
{
    Mat input = Mat::zeros(1024, 1024, CV_8UC1);
    char userAnswer = 'k';
    Rect roi(8, 8, 1008, 1008);
    
    int intensity = 0;
    int grayPerception = 0;

    namedWindow("Grays Intesity Test", 1);
    imshow("Grays Intesity Test", input);
    
    for(;;)
    {
        
        while(((userAnswer = char(waitKey(1))) != 'q') && intensity <= 255)
        {
            if (userAnswer == 'n')
            {
                changeIntensity(input, roi, 0);
                intensity +=1;
                updateWindow("Grays Intensity Test");
                imshow("Grays Intesity Test", input);
            }
            if (userAnswer == 's')
            {
                grayPerception += 1;
                changeIntensity(input, roi, 1);
                updateWindow("Grays Intensity Test");
                imshow("Grays Intesity Test", input);
            }
        }
        cout << "======================================================" << endl;
        cout << "Mudanças de intensidade observadas = " << grayPerception << endl;
        cout << "======================================================" << endl;
        return 0;
    }
    
    return 0;
}

void changeIntensity(Mat input, Rect &roi, int flag)
{
    switch(flag)
    {
        case(0):
            input(roi) += 1;
            break;

        case(1):
            if(roi.width >= 32 && roi.height >= 32)
            {
                roi = (Rect(roi.x += 8, roi.y += 8, roi.width -=16, roi.height-=16));     
            }
            break;

       default:
            cout << "Invalid flag" << endl;
            break;
    }
}
