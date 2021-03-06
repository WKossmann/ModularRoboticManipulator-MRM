#ifndef Vision_h
#define Vision_h

#include <opencv2/highgui.hpp>
#include <opencv2/aruco.hpp>
#include <opencv2/core.hpp>
#include <opencv/cv.hpp>
#include <iostream>

#define DICTIONARY_ID 16

class Vision
{
public:
    Vision();
    ~Vision();
    bool start();
    bool getVisualPosition(int& x, int& y);
    void showPoints(int x[], int y[], int size, cv::Scalar color);
    cv::VideoCapture inputVideo;

private:
    cv::Ptr<cv::aruco::DetectorParameters> detectorParams;
    cv::Ptr<cv::aruco::Dictionary> dictionary;
    std::vector<int> ids;
    std::vector<std::vector<cv::Point2f>> corners, rejected;
    cv::Mat image, imageCopy;
    
};

Vision::Vision(){
    detectorParams = cv::aruco::DetectorParameters::create();
    dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME(DICTIONARY_ID));
    cv::namedWindow("Windown", cv::WINDOW_AUTOSIZE);
}
Vision::~Vision(){ 
}

bool Vision::start(){ 
    inputVideo.open(0);
    if(inputVideo.isOpened()){
        return true;
    }else{
        return false;
        std::cout << "Erro start camera" << std::endl;
    }
}

bool Vision::getVisualPosition(int& _x, int& _y){
    //Discart 5 frames to get the newest frame
    for(int i=0;i<5;i++){
        inputVideo.grab();
        inputVideo.retrieve(image);
    }
    _x=0;
    _y=0;

    // detect markers and estimate pose
    cv::aruco::detectMarkers(image, dictionary, corners, ids, detectorParams, rejected);

    // draw results
    int sizeIds = ids.size();
    if(sizeIds <=0){
        // std::cout << "Found nothing, Jon Snow" << std::endl;
        return false;
    }else for(int i =0;i<sizeIds;i++) {
        if(ids[i] == 213){
            _x = (int)((corners[i][0].x + corners[i][1].x + corners[i][2].x + corners[i][3].x)/4);
            _y = (int)((corners[i][0].y + corners[i][1].y + corners[i][2].y + corners[i][3].y)/4);

            // std::cout << ids[i] << " >> X: " <<  (int)_x << " Y: " << (int)_y << std::endl;
            
            // image.copyTo(imageCopy);
            // cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
            // imshow("out", imageCopy);
            return true;
        }
    }
    return false;
}
void Vision::showPoints(int x[], int y[], int size, cv::Scalar color){
    for(int i=0;i<5;i++){
        inputVideo.grab();
        inputVideo.retrieve(image);
    }
    for(int i=0;i<size;i++){
        cv::circle(image, cv::Point(x[i],y[i]), 2, color);
    }
    cv::imshow("Windown", image);
    cv::waitKey(0);
}



#endif