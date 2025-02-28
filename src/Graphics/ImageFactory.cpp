#include "S3D/Graphics/ImageFactory.h"

#include "S3D/Graphics/IO/PngImageGenerator.h"

#include <filesystem>

namespace S3D
{
    //static
    std::map<std::string, ImageGenerator *> ImageFactory::mGeneratorMap;

    void ImageFactory::init()
    {
        registerGenerator(new PngImageGenerator());
    }
    
    void ImageFactory::cleanup()
    {
        for(auto ite = mGeneratorMap.begin() ; ite != mGeneratorMap.end() ; ite++)
        {
            SAFE_DELETE((*ite).second);
        }
    }

    bool ImageFactory::registerGenerator(ImageGenerator *generator)
    {
        auto ite = mGeneratorMap.find(generator->getExt());
        if(ite == mGeneratorMap.end())
        {
            mGeneratorMap[generator->getExt()] = generator;
            return true;
        }else return false;
    }

    Image *ImageFactory::createImage(const FilePath &path)
    {
        std::string ext = path.getExtension();        
        auto ite = mGeneratorMap.find(ext);
        if(ite != mGeneratorMap.end()) return mGeneratorMap[ext.c_str()]->createImage(path);
        else return NULL;

    }


    
} // namespace S3D
