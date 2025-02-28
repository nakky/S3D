#ifndef S3D_OPENGL3TEXTUREDRIVER_H
#define S3D_OPENGL3TEXTUREDRIVER_H

#include "S3D/Common.h"
#include "S3D/Graphics/Renderer.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"
#include "S3D/Graphics/Drivers/TextureDriver.h"

namespace S3D
{
    class OpenGL3Texture2DDriver : public Texture2DDriver
    {
    public:
        OpenGL3Texture2DDriver(
            Texture2D *texture
            )
            : Texture2DDriver(texture),
            mTextureName(0)
        {
        }

        virtual ~OpenGL3Texture2DDriver() {}

        virtual void load(GraphicsContext *context);
        virtual void unload(GraphicsContext *context);

        unsigned int getTextureName(){ return mTextureName; }

        virtual void render(const void *pixels);

    protected:
        unsigned int mTextureName;

    };

}; // namespace S3D

#endif // S3D_OPENGL3TEXTUREDRIVER_H
