#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define DICTIONARY_ID 16

int main(int argc, char *argv[]) {

    Ptr<aruco::DetectorParameters> detectorParams = aruco::DetectorParameters::create();
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME(DICTIONARY_ID));

    VideoCapture inputVideo;
    inputVideo.open(0);
    
    while(1) {
        Mat image, imageCopy;
        for(int i=0;i<5;i++){
            inputVideo.grab();
            inputVideo.retrieve(image);
        }

        vector< int > ids;
        vector< vector< Point2f > > corners, rejected;

        // detect markers and estimate pose
        aruco::detectMarkers(image, dictionary, corners, ids, detectorParams, rejected);

        // draw results
        image.copyTo(imageCopy);
        if(ids.size() > 0) {
            Point ponto;
            ponto.x = (corners[0][0].x + corners[0][1].x + corners[0][2].x + corners[0][3].x)/4;
            ponto.y = (corners[0][0].y + corners[0][1].y + corners[0][2].y + corners[0][3].y)/4;

            cout << "centro: " <<  ponto.x << " " << ponto.y << endl;
            aruco::drawDetectedMarkers(imageCopy, corners, ids);
        }

        imshow("out", imageCopy);
        char key = (char)waitKey(0);
        if(key == 27) break;
    }

    return 0;
}
