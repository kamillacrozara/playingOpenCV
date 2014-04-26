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
    Mat binary_img = Mat::zeros(img_original.size().height, img_original.size().width ,CV_8UC1);
    Mat img_dest2 = Mat::zeros(img_original.size().height, img_original.size().width ,CV_8UC1);
    
    if(!img_original.isContinuous())
    {
        cout << "Imagem não é contínua" << endl;
    }

    //threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)
    //threshold(img_original, img_dest, 0, 255, 0);

    vector<vector <cv::Point> > contours;
    vector<Vec4i> hierarchy;
    
    //CV_RETR_TREE retrieves all of the contours and reconstructs a full hierarchy of 
    //nested contours. This full hierarchy is built and shown in the OpenCV contours.c demo.
    
    //CV_CHAIN_APPROX_NONE stores absolutely all the contour points. That is, any 2 
    //subsequent points (x1,y1) and (x2,y2) of the contour will be either horizontal, 
    //vertical or diagonal neighbors, that is, max(abs(x1-x2),abs(y2-y1))==1.
   
    Canny(img_original, img_original, 0, 1);
    /* 
     * Contours found by findContours function has direction. Objects are 
     * counter clockwise, and holes are clockwise. So if you check signed 
     * area of each contour, you will know whether this is a hole or not by 
     * its sign. Signed area of contour can be calculated in following way: */
    // contourArea(InputArray contour, bool oriented=false);
    //bitwise_not(img_original, img_dest);

    findContours(img_original, contours, hierarchy, 3, 1);

    int spots = 0;
    int holes = 0;

    vector <int>blobClassA;//nao tem buracos
    vector <int>blobClassB;//tem buracos

    for(vector<Vec4i>::size_type idx=0; idx<hierarchy.size(); ++idx)
    {
        //se a mancha não tem pai, então é uma macha do primeiro
        //nível da hierarquia. É marcado como -1 e adiciono à
        //conta do número de manchas
        if(hierarchy[idx][3] == -1)
        {
           spots +=1;
        }
    

        if(hierarchy[idx][2] == -1)
        {
           blobClassA.push_back(1);
        }
        else
        {
            blobClassB.push_back(1);
        }
    }
    cout << "Spots = " << spots << endl;
    cout << "Class A = " << blobClassA.size() << endl;
    cout << "Class B = " << blobClassB.size() << endl;



    }
