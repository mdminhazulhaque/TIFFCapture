# TIFFCapture

An `OpenCV::VideoCapture` like implementation for multi-directory TIFF media

## Requirements

* libopencv-dev
* libtiff-dev

## Methods

    TIFFCapture(const char* tifffile)
    bool open(const char* tifffile)
    bool isOpened()
    void release()
    void operator >> (Mat& image)
    bool read(Mat& image)
    int get(int propId)

## Properties

    TIFF_CAP_PROP_FRAME_COUNT
    TIFF_CAP_PROP_FRAME_HEIGHT
    TIFF_CAP_PROP_FRAME_WIDTH
    TIFF_CAP_PROP_FRAME_POS

## Example

See `main.cpp`. Run `make` then execute `./TIFFCapture`

## Doesn't Work on Windows?

Use Linux or OS X. :)