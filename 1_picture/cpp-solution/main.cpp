#include <regex>
#include <vector>
#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <path_to_tesseract/include/tesseract/baseapi.h>
#include <path_to_leptonica/include/leptonica/allheaders.h>

using namespace cv;
using std::cout;
using std::regex;
using std::vector;
using std::string;

const size_t AM_BLOCKS = 37;
const size_t PIC_PX = 100;


enum Color {
    black,
    white = 255
};

void paint (Mat & pic, Color color, size_t i, size_t j) {
    rectangle(pic, Point(i,j), Point(i + PIC_PX, j + PIC_PX), Scalar(color,color,color), -1);
}

bool checkRegex (string s) {
    // for black
    regex rx("(lack)");
    regex rx1("(ark)");
    regex rx2("(ot)");
    regex rx3("\\(\\d,\\d,\\d\\)[^[:print:]]");

    //for white
    regex rx4("(.)(.)(.)(.)(.)[^[:print:]]*");
    regex rx5("(hite)");
    regex rx6("\\(\\d\\d\\d(.)*[^[:print:]]*\\d\\d\\d(.)*[^[:print:]]*\\d\\d\\d\\)(.)*[^[:print:]]*");

    if (regex_search(s.begin(), s.end(), rx)
    || regex_search(s.begin(), s.end(), rx1)
    || regex_search(s.begin(), s.end(), rx2)
    || regex_match(s.begin(), s.end(), rx3)) {
        return true;
    }

    if (regex_match(s.begin(), s.end(), rx4)
    || regex_search(s.begin(), s.end(), rx5)
    || regex_search(s.begin(), s.end(), rx6)) {
        return false;
    }
    return true;
}

int main() {
    vector<string> outText;
    string imPath = "path_to_file/file.png";

    // tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();

    // initialize tesseract to use English (eng) and the LSTM OCR engine.
    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);

    // set page segmentation mode to PSM_BLOCK. Assume a single uniform block of text.
    ocr->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);

    // open image using OpenCV without changes
    Mat im = imread(imPath, -1);

    // separate im data to blocks and set blocks data
    for (size_t i = 0; i < AM_BLOCKS * PIC_PX; i += PIC_PX) {
        for (size_t j = 0; j < AM_BLOCKS * PIC_PX; j += PIC_PX) {

            Rect block(j + 1, i + 1, PIC_PX - 1, PIC_PX - 1); // delete borders for more efficient ocr
            ocr->SetImage(im(block).data, im(block).cols, im(block).rows, 3, im(block).step);

            string text = (string(ocr->GetUTF8Text()));

            outText.push_back(text);

            // paint new pic by checking regex
            if (checkRegex(text)) {
                paint(im, black, j, i);
            } else {
                paint(im, white, j, i);
            }
        }
    }

    imwrite("upd_file.png", im);

    // print text from pic
    for (auto const& box: outText) {
        cout << box << "\n";
    }

    ocr->End();
    return 0;
}
