
#include "S3D/Graphics/Texture.h"

#include "S3D/Graphics/ImageFactory.h"

#include "S3D/Application/GraphicsContext.h"


namespace S3D
{
    void Texture2D::load(GraphicsContext *context){
        mImage = ImageFactory::createImage(FilePath(mFilePath));
        mSize = *mImage->getSize();

        mPixelFormat = mImage->getPixelFormat();

        mDriver->load(context); 

        context->bind();
        mDriver->render(mImage->getBuffer());
        context->release();

        if(mImage != NULL && mIsStatic){
            mImage->cleanup();
            SAFE_DELETE(mImage);
        }
    }

    void Texture2D::unload(GraphicsContext *context){
        mDriver->unload(context);
        if(mImage != NULL){
            mImage->cleanup();
            SAFE_DELETE(mImage);
        }
    }
    
} // namespace S3D

       