/******************************************************************/
/*!
	@file	Texture.h
	@brief	Texture class
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_TEXTURE_H
#define S3D_TEXTURE_H

#include "S3D/Common.h"
#include "S3D/Graphics/Math/MathematicsTypes.h"
#include "S3D/Foundation/Resource.h"

#include "S3D/Graphics/Drivers/TextureDriver.h"
#include "S3D/Graphics/Image.h"

#include "S3D/Application/GraphicsFactory.h"

namespace S3D{

    enum TextureType
    {
        TEXTURE_COLOR,
        TEXTURE_NORMAL
    };

    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class Texture2D;

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	Texture2D
        @brief	2D Texture class
        @note
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class Texture2D : public Resource
    {

    public:
        Texture2D()
        :Resource(),
        mImage(NULL),
        mIsStatic(true)
        {}

        virtual const short getResourceType() { return RESOURCETYPE_TEXTURE2D; }

        virtual void setIsStatic(const bool isStatic) { mIsStatic = isStatic; }
        virtual void setFilePath(const char *path) { mFilePath = path; }
       
        TextureType getType(){ return mType; }
        void setType(const TextureType type){ mType = type; }
        
        Size2 *getSize(){ return &mSize; }
        PixelFormat getPixelFormat(){ return mPixelFormat; }

        const Texture2DDriver *getDriver() const { return mDriver; }

        virtual void init(){ 
            mDriver = GraphicsFactory::createTexture2DDriver(this);
            mDriver->init();
        }
        virtual void cleanup(){ 
            mDriver->cleanup(); 
            SAFE_DELETE(mDriver);
        }

        virtual void load(GraphicsContext *context);
        virtual void unload(GraphicsContext *context);

        virtual void render(const void *pixels){ mDriver->render(pixels); }

    protected:
        void setPixelFormat(const PixelFormat format){ mPixelFormat = format; }
        void setSize(const Size2 &size){ mSize = size; }

    protected:
        bool mIsStatic;
        TextureType mType;
        Size2 mSize;
        PixelFormat mPixelFormat;

        Texture2DDriver *mDriver;

        std::string mFilePath;

        Image *mImage;
    };

};// namespace S3D

#endif //S3D_TEXTURE_H

