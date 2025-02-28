#ifndef S3D_PNGIMAGEGENERATOR_H
#define S3D_PNGIMAGEGENERATOR_H

#include "S3D/Common.h"
#include "S3D/Graphics/ImageFactory.h"

namespace S3D
{
    class Input;

    class PngImageGenerator : public ImageGenerator
    {
    public:
        PngImageGenerator()
        :ImageGenerator("png")
        {}
        virtual ~PngImageGenerator(){}

        virtual Image *createImage(const FilePath &path);

    protected:
        unsigned char *loadFromFile(Input *input, int *x, int *y, int *comp, int reqComp);
    };

};

#endif //S3D_PNGIMAGEGENERATOR_H

