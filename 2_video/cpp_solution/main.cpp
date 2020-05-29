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

// check on color characters
string parseColorSet (Mat const& img) {

    for (size_t x = 0; x < img.rows; ++x) {
        for (size_t y = 0; y < img.cols; ++y) {
            Vec3b intensity = img.at<Vec3b>(y, x);
            uchar blue = intensity.val[0];
            uchar green = intensity.val[1];
            uchar red = intensity.val[2];

            if (blue == 255 && red == 0 && green == 0) {
                return "U";
            }

            if (green == 255 && red == 0 && blue == 0) {
                return "G";
            }

            if (red == 255 && blue == 0) {
                if (green == 255) {
                    return "Y";
                } else if (green == 0) {
                    return "R";
                }
            }

        }
    }
    return "Q";
}

int main(){
    // vector for saving characters
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

        // get frame
        Mat frame;
        cap >> frame;

        // if the frame is empty, break immediately
        if (frame.empty())
            break;

        // parse by start color
        string currentChar = parseColorSet(frame);

        // if not color
        if (currentChar == "Q") {

            // grayscale
            cvtColor(frame, frame, COLOR_BGR2GRAY);

            // invert colors if need
            Scalar colour = frame.at<uchar>(Point(0, 0));
            Scalar colour1 = frame.at<uchar>(Point(frame.cols, 0));
            if((colour.val[0] < 130 && colour1.val[0] < 130)) {
                frame = ~frame;
            }

            // saturate all characters
            for (size_t i = 0; i < frame.cols; ++i) {
                for (size_t j = 0; j < frame.rows; ++j) {
                    if (frame.at<uchar>(i,j) < 210) frame.at<uchar>(i,j) = 0; // 250 for print saturated 'Y', but bad for the rest parse.
                }
            }

            // ocr set image and convert to text
            ocr->SetImage(frame.data, frame.cols, frame.rows, 1, frame.step);
            currentChar = string(ocr->GetUTF8Text());

        }

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

    // map all characters
    map<char, int> alpha;
    for (size_t i = 0; i < chars.size(); ++i) {
        if (chars[i][0] == '0') {
            ++alpha['O'];
            continue;
        }
        if (chars[i][0] == '1') {
            ++alpha['I'];
            continue;
        }
        if (chars[i][0] == '\\') {
            ++alpha['X'];
            continue;
        }
        ++alpha[chars[i][0]];
    }

    //print ans
    string ans = "";
    for (auto const& i: alpha) {
            if (i.first == 0) continue;
            ans += i.first + to_string(i.second);
    }
    cout << ans;

    // when everything done, release the video capture object
    cap.release();

    // closes all the frames
    destroyAllWindows();

      return 0;
}
