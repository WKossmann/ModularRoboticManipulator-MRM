#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;
 
int main( )
{    
  // Create black empty images
  Mat image = Mat::zeros( 400, 400, CV_8UC3 );
   
  // Draw a circle 
  // circle( image, Point( 200, 200 ), 32.0, Scalar( 0, 0, 255 ), 1, 8 );
  imshow("Image",image);
 
  waitKey( 0 );
  return(0);
}