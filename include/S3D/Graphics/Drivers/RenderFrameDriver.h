#ifndef S3D_RENDERFRAMEDRIVER_H
#define S3D_RENDERFRAMEDRIVER_H

#include "S3D/Common.h"

namespace S3D
{
    class RenderFrame;
    class GraphicsContext;

    class RenderFrameDriver 
    {
    public:
        RenderFrameDriver(RenderFrame *renderFrame)
        {
        }

        virtual void init(){}
        virtual void cleanup(){}

        virtual void load(GraphicsContext *context) = 0;
        virtual void unload(GraphicsContext *context) = 0;

    protected:
        RenderFrame *mRenderFrame;
    };
}

#endif // S3D_RENDERFRAMEDRIVER_H
