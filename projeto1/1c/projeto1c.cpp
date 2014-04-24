#include <iostream>
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
    //threshold(InputArray src, OutputArray dst, double thresh, double maxval, int type)
    threshold(img_original, img_dest, 0, 255, 1);
    imwrite("treshold.bmp", img_dest);
}
