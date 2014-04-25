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
    Mat img_dest = Mat::zeros(img_original.size().height, img_original.size().width ,CV_8UC1);
    Mat img_dest2 = Mat::zeros(img_original.size().height, img_original.size().width ,CV_8UC1);
    
    if(!img_original.isContinuous())
    {
        cout << "Imagem não é contínua" << endl;
    }


    //threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)
    threshold(img_original, img_dest, 0, 255, 1);

    vector<vector <cv::Point> > contours;
    vector<Vec4i> hierarchy;
    
    //CV_RETR_TREE retrieves all of the contours and reconstructs a full hierarchy of 
    //nested contours. This full hierarchy is built and shown in the OpenCV contours.c demo.
    
    //CV_CHAIN_APPROX_NONE stores absolutely all the contour points. That is, any 2 
    //subsequent points (x1,y1) and (x2,y2) of the contour will be either horizontal, 
    //vertical or diagonal neighbors, that is, max(abs(x1-x2),abs(y2-y1))==1.
    
    findContours(img_original, contours, hierarchy, 3, 0);
    int spots = contours.size();

    for(int i = hierarchy.size(); i <=0; i--){
        cout << "oi" << endl;
    }
       // cout << hierarchy.at(i) << endl;
            
    cout << "Number of spots = " << spots << endl;
}
