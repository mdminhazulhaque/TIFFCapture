#include <iostream>

#include <opencv2/opencv.hpp>
#include "tiffcapture.hpp"

using namespace std;
using namespace cv;

int main()
{
    TIFFCapture tc;
    tc.open("test.tiff");

    if(!tc.isOpened())
    {
        cerr << "Loading TIFF stream failed" << endl;
        return 1;
    }

    double width = tc.get(TIFFCapture::TIFF_CAP_PROP_FRAME_WIDTH);
    double height = tc.get(TIFFCapture::TIFF_CAP_PROP_FRAME_HEIGHT);
    double count = tc.get(TIFFCapture::TIFF_CAP_PROP_FRAME_COUNT);

    cout << "Loaded TIFF stream, WIDTH=" << width << " HEIGHT=" << height << " FRAMES=" << count << endl;

    Mat frame;
    while(tc.read(frame))
    {
        // Get frame position
        int fc = tc.get(TIFFCapture::TIFF_CAP_PROP_FRAME_POS);
        stringstream ss;
        ss << "Frame " << fc;

        // Print frame position over the image
        putText(frame, ss.str(), Point(80,220), CV_FONT_NORMAL, 1, Scalar(0,255,255), 1, CV_AA);
        imshow("Frame", frame);

        waitKey(100);
    }

    // Free memory
    tc.release();

    return 0;
}

