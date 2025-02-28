

#ifndef S3D_IMAGEFACTORY_H
#define S3D_IMAGEFACTORY_H

#include "S3D/Common.h"

#include "S3D/Foundation/FilePath.h"
#include "S3D/Graphics/Image.h"

#include <map>

namespace S3D
{
    class ImageGenerator
    {
    public:
        ImageGenerator(const char *ext)
        :mExt(ext)
        {}
        virtual ~ImageGenerator(){}

        virtual Image *createImage(const FilePath &path) = 0;

        const char *getExt() { return mExt.c_str(); }

    protected:
        std::string mExt;
    };

    class ImageFactory
    {
    private:
        ImageFactory()
        {
        }
    public:

        static void init();
        static void cleanup();

        static bool registerGenerator(ImageGenerator *generator);
        static Image *createImage(const FilePath &path);

    protected:
        static std::map<std::string, ImageGenerator *> mGeneratorMap;
    };

};

#endif //S3D_IMAGEFACTORY_H

