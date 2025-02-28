#ifndef S3D_OPENGL3RENDERFRAMEDRIVER_H
#define S3D_OPENGL3RENDERFRAMEDRIVER_H

#include "S3D/Common.h"
#include "S3D/Graphics/Drivers/RenderFrameDriver.h"

namespace S3D
{
    class OpenGL3RenderFrameDriver : public RenderFrameDriver
    {
    public:
        OpenGL3RenderFrameDriver(RenderFrame *renderFrame)
        :RenderFrameDriver(renderFrame)
        {
        }

        virtual void load(GraphicsContext *context);
        virtual void unload(GraphicsContext *context);

        unsigned int getFrameBufferName() { return mFrameBufferName; }

    protected:
        unsigned int mFrameBufferName;

        unsigned int mColorRenderBufferName;
        unsigned int mDepthRenderBufferName;
        unsigned int mStencilRenderBufferName;
    };
}

#endif // S3D_OPENGL3RENDERFRAMEDRIVER_H
