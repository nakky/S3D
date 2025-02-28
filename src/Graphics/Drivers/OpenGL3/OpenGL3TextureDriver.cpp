
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.h"

#include "S3D/Application/GraphicsContext.h"
#include "S3D/Graphics/Texture.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D
{
    void OpenGL3Texture2DDriver::load(GraphicsContext *context)
    {
        context->bind();

        GLuint texName = 0;
            
        ::glEnable(GL_TEXTURE_2D);
        ::glGenTextures(1 , (GLuint*)&(texName));
        
        if(texName == 0) return;

        mTextureName = texName;

        context->release();
    }

    void OpenGL3Texture2DDriver::unload(GraphicsContext *context)
    {
        context->bind();

        ::glEnable(GL_TEXTURE_2D);
        ::glDeleteTextures(1 , (GLuint*)&(mTextureName));

        context->release();
    }

    void OpenGL3Texture2DDriver::render(const void *pixels)
    {
        ::glActiveTexture(GL_TEXTURE0);
        ::glBindTexture(GL_TEXTURE_2D, mTextureName);  

        ::glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        ::glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        ::glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

        auto size = mTexture->getSize();

        switch (mTexture->getPixelFormat())
        {
        case PIXEL_RGBA32:
        {
            ::glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGBA, size->width, size->height,
                0, GL_RGBA, GL_UNSIGNED_BYTE, pixels
            );
        }
        break;
        case PIXEL_RGB24:
        {
            ::glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RGB, size->width, size->height,
                0, GL_RGB, GL_UNSIGNED_BYTE, pixels
            );
        }
        break;
        case PIXEL_ALPHA8:
        {
            ::glTexImage2D(
                GL_TEXTURE_2D, 0, GL_ALPHA, size->width, size->height,
                0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels
            );
        }
        break;
        case PIXEL_LUMINANCE8:
        {
            ::glTexImage2D(
                GL_TEXTURE_2D, 0, GL_LUMINANCE, size->width, size->height,
                0, GL_LUMINANCE, GL_UNSIGNED_BYTE, pixels
            );
        }
        break;
        case PIXEL_LUMINANCE_ALPHA16:
        {
            ::glTexImage2D(
                GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, size->width, size->height,
                0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, pixels
            );
        }
        break;
        }
        
    }


}; //namespace S3D

