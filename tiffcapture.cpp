#include "tiffcapture.hpp"

TIFFCapture::TIFFCapture()
{
    isTIFFOpened = false;
}

TIFFCapture::TIFFCapture(const char* tifffile)
{
    isTIFFOpened = false;
    open(tifffile);
}

bool TIFFCapture::open(const char* tifffile)
{
    TIFFSetWarningHandler(NULL);

    tiff = TIFFOpen(tifffile, "r");

    if(tiff)
    {
        frameCount = framePos = 0;

        TIFFGetField(tiff, TIFFTAG_IMAGEWIDTH, &width);
        TIFFGetField(tiff, TIFFTAG_IMAGELENGTH, &height);

        /** allocate space to store rgb data */
        data = new uint32[width*height];

        /** count total frames */
        while(TIFFReadDirectory(tiff))
            frameCount++;

        /** reset tiff index */
        TIFFSetDirectory(tiff, 0);

        isTIFFOpened = true;
    }
    else
        isTIFFOpened = false;

    return isTIFFOpened;
}

bool TIFFCapture::isOpened()
{
    return isTIFFOpened;
}

void TIFFCapture::release()
{
    TIFFClose(tiff);
    delete data;
}

void TIFFCapture::operator >>(cv::Mat &image)
{
    read(image);
}

bool TIFFCapture::read(cv::Mat &image)
{
    if(isTIFFOpened and TIFFReadDirectory(tiff))
    {
        /** create mat with frame height and width */
        /** 3 channel with RGB data */
        image = cv::Mat::zeros(height, width, CV_8UC3);

        /** render current tiff directory */
        TIFFReadRGBAImage(tiff, width, height, data);

        for(uint32 row = 0; row < height; row ++)
        {
            for(uint32 col = 0; col < width; col ++)
            {
                uint32 value = data[row*width + col];
                /** convert RGB data into Mat element as OpenCV default BGR data */
                image.at<Vec3b>(row,col) = Vec3b(TIFFGetB(value),TIFFGetG(value),TIFFGetR(value));
            }
        }

        /** bad programmer, image is upside down */
        flip(image, image, 0);

        framePos++;

        return true;
    }
    else
        return false;
}

int TIFFCapture::get(int propId)
{
    switch(propId)
    {
    case TIFF_CAP_PROP_FRAME_COUNT:
        return (int)frameCount;
        break;
    case TIFF_CAP_PROP_FRAME_HEIGHT:
        return (int)height;
        break;
    case TIFF_CAP_PROP_FRAME_WIDTH:
        return (int)width;
        break;
    case TIFF_CAP_PROP_FRAME_POS:
        return (int)framePos;
        break;
    default:
        return (int)NULL;
    }
}
