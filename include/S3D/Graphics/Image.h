#ifndef S3D_GRAPHICS_IMAGE_H
#define S3D_GRAPHICS_IMAGE_H

#include "S3D/Common.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"


namespace S3D
{
    enum PixelFormat
    {
        PIXEL_ALPHA8,
        PIXEL_LUMINANCE8,
        PIXEL_LUMINANCE_ALPHA16,
        PIXEL_RGB24,
        PIXEL_RGBA32
    };

    class Image 
    {
    public:
        Image(PixelFormat format, const Size2 &size, unsigned char *buffer)
        :mPixelFormat(format),
        mSize(size),
        mBuffer(buffer)
        {
        }

        virtual ~Image() {}

        const Size2 *getSize() { return &mSize; }
        unsigned char* getBuffer(){ return mBuffer; }
        const PixelFormat getPixelFormat() { return mPixelFormat; }

        virtual void init();
        virtual void cleanup();

    protected:
        Size2 mSize;
        unsigned char* mBuffer;
        PixelFormat mPixelFormat;
    };

};

#endif //S3D_GRAPHICS_IMAGEFILE_H

