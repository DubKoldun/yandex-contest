#include <regex>
#include <vector>
#include <iostream>
#include "opencv2/opencv.hpp"
#include </nix/store/0a65109gxqip2y851pms8drk6339y6i8-tesseract-4.1.1/include/tesseract/baseapi.h>
#include </nix/store/pfd5bv39smag5izp4apf1cnb4scxdah4-leptonica-1.79.0/include/leptonica/allheaders.h>

using namespace cv;
using std::cout;
using std::regex;
using std::vector;
using std::string;

const size_t AM_BLOCKS = 37;
const size_t PIC_PX = 100;

// void painting(Mat const& pic, vector<string> const& blocks) {
//     for (auto const& block: blocks) {
//         std::tr1::regex rx("*", std::tr1::regex_constants::icase);
//         if (regex_search(box.begin(), box.end(), rx)) {
//
//         }
//
//     }
// }

void paint (Mat const& pic, string s) {
    regex rx("[:aplha:]*");
    if (regex_search(s.begin(), s.end(), rx)) {
        
        imshow("black", pic);
    }
}

int main() {
    vector<string> outText;
    string imPath = "/home/vutaliy/Documents/task1/Untitled7.png";

    // tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();

    // initialize tesseract to use English (eng) and the LSTM OCR engine.
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);

    // set page segmentation mode to PSM_AUTO
    ocr->SetPageSegMode(tesseract::PSM_AUTO);

    // open image using OpenCV
    Mat im = imread(imPath, IMREAD_COLOR);

    // separate img data to blocks and set blocks data
    // for (size_t i = 0; i < AM_BLOCKS * PIC_PX; i += PIC_PX) {
    //     for (size_t j = 0; j < AM_BLOCKS * PIC_PX; j += PIC_PX) {
    //         Rect block(j + 1, i + 1, PIC_PX - 1, PIC_PX - 1); // delete borders for more efficient ocr
    //         ocr->SetImage(im(block).data, im(block).cols, im(block).rows, 3, im(block).step);
    //         outText.push_back(string(ocr->GetUTF8Text()));
    //     }
    // }

    Rect r(1, 1, PIC_PX - 2, PIC_PX - 2);
    cv::Mat cropped;
    cv::getRectSubPix(im, im.size, im.center, cropped);
        // Set image data
    ocr->SetImage(cropped.data, cropped.cols, cropped.rows, 3, cropped.step);
    cout << string(ocr->GetUTF8Text());


    for (auto const& box: outText) {
        // if (i.empty()) return 0;
        cout << box << "\n";
    }

    // paint our pic
    Mat buff = im.clone();
    // // painting(buff, outText);
    paint (buff, string(ocr->GetUTF8Text()));

    ocr->End();
    return 0;
}
