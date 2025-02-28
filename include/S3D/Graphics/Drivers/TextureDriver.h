#ifndef S3D_TEXTUREDRIVER_H
#define S3D_TEXTUREDRIVER_H

#include "S3D/Common.h"

namespace S3D
{
    class Texture2D;
    class GraphicsContext;

    class Texture2DDriver
    {
    public:
        Texture2DDriver(
            Texture2D *texture
            )
            :mTexture(texture)
        {
        }

        virtual ~Texture2DDriver() {}

        virtual void init(){}
        virtual void cleanup(){}

        virtual void load(GraphicsContext *context) = 0;
        virtual void unload(GraphicsContext *context) = 0;

        virtual void render(const void *pixels) = 0;

    protected:
        Texture2D *mTexture;
    };

}; // namespace S3D

#endif // S3D_TEXTUREDRIVER_H
