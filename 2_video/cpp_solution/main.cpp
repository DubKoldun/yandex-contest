#include <map>
#include <regex>
#include <vector>
#include <iostream>
#include <algorithm>
#include "opencv2/opencv.hpp"
#include </nix/store/0a65109gxqip2y851pms8drk6339y6i8-tesseract-4.1.1/include/tesseract/baseapi.h>
#include </nix/store/pfd5bv39smag5izp4apf1cnb4scxdah4-leptonica-1.79.0/include/leptonica/allheaders.h>


using namespace std;
using namespace cv;

int main(){
    vector<string> chars;
    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    VideoCapture cap("/home/vutaliy/Downloads/cut.mp4");

    // Check if camera opened successfully
    if(!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    // tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();

    // initialize tesseract to use English (eng) and the LSTM OCR engine.
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);

    // set page segmentation mode to PSM_CHAR
    ocr->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);

    // capture frame-by-frame
    int i = 0;
    while(true) {

        // get frame and grayscale
        Mat img;
        cap >> img;
        Mat frame;
        cvtColor(img, frame, COLOR_BGR2GRAY);

        // invert colors if need
        Scalar colour = frame.at<uchar>(Point(0, 0));
        if(colour.val[0] < 130) {
            frame = ~frame;
        }


        // if the frame is empty, break immediately
        if (frame.empty())
            break;

        ocr->SetImage(frame.data, frame.cols, frame.rows, 1, frame.step);
        string currentChar = string(ocr->GetUTF8Text());

        // skipping same frames
        if (i > 0 && currentChar == chars[i-1]) {
            continue;
        }
        chars.push_back(currentChar);
        ++i;

        // display the resulting frame
        imshow("Frame", frame);

        // press  ESC on keyboard to exit
        char c=(char)waitKey(25);
        if(c==27)
            break;
    }

    // sort(chars.begin(), chars.end());
    // vector<int> alpha(27);
    map<char, int> alpha;
    for (size_t i = 0; i < chars.size(); ++i) {
        // cout << chars[i][0];
        ++alpha[chars[i][0]];
    }

    string ans = "";
    for (auto const& i: alpha) {
            if (i.first == 0) continue;
            ans += i.first + to_string(i.second);
    }
    // reverse(ans.begin(), ans.end());
    cout << ans;

    // when everything done, release the video capture object
    cap.release();

    // closes all the frames
    destroyAllWindows();

      return 0;
}
