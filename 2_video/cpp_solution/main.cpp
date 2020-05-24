#include <regex>
#include <vector>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include </nix/store/0a65109gxqip2y851pms8drk6339y6i8-tesseract-4.1.1/include/tesseract/baseapi.h>
#include </nix/store/pfd5bv39smag5izp4apf1cnb4scxdah4-leptonica-1.79.0/include/leptonica/allheaders.h>


using namespace std;
using namespace cv;

int main(){

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap("/home/vutaliy/Downloads/task.mp4");

  // Check if camera opened successfully
  // if(!cap.isOpened()){
  //   cout << "Error opening video stream or file" << endl;
  //   return -1;
  // }

  int i = 0;

  while(1){

    Mat frame;
    // Capture frame-by-frame
    cap >> frame;

    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Display the resulting frame
    imwrite( "Frame" + i, frame );

    ++i;
  }

  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();

  return 0;
}
