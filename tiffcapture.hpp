#ifndef TIFFCAPTURE_HPP
#define TIFFCAPTURE_HPP

#include "opencv2/core/core.hpp"
#include "tiffio.h"

using cv::Mat;
using cv::Vec3b;

class TIFFCapture
{
public:
    enum TIFFCaptureProp
    {
        TIFF_CAP_PROP_FRAME_COUNT = 0,
        TIFF_CAP_PROP_FRAME_HEIGHT,
        TIFF_CAP_PROP_FRAME_WIDTH,
        TIFF_CAP_PROP_FRAME_POS
    };

    TIFFCapture();
    TIFFCapture(const char* tifffile);

    bool open(const char* tifffile);
    bool isOpened();
    void release();
    void operator >> (Mat& image);
    bool read(Mat& image);
    int get(int propId);

private:
    TIFF* tiff;
    uint32 width;
    uint32 height;
    uint32 frameCount;
    uint32 framePos;
    uint32 *data;
    bool isTIFFOpened;
};

#endif // TIFFCAPTURE_HPP
