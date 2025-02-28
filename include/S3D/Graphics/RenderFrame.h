#ifndef S3D_RENDERFRAME_H
#define S3D_RENDERFRAME_H

#include "S3D/Common.h"
#include "S3D/Foundation/Resource.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"

#include "S3D/Graphics/Drivers/RenderFrameDriver.h"

#include "S3D/Application/GraphicsFactory.h"


namespace S3D
{
    enum FrameBufferType {
        FRAMEBUFFER_NONE = 0,
        FRAMEBUFFER_COLOR = 1 << 0,
        FRAMEBUFFER_DEPTH = 1 << 1,
        FRAMEBUFFER_STENCIL = 1 << 2,
    };

    class RenderFrame : public Resource
    {
    public:
        RenderFrame(FrameBufferType type, const Size2 &resolution)
        :mBufferType(type),
        mResolution(resolution),
        mDriver(NULL)
        {
        }

    RenderFrameDriver *getDriver(){ return mDriver; }

    const FrameBufferType getBufferType() { return mBufferType; }
    const Size2 *getResolution() { return &mResolution; }
    
    virtual void init(){ 
        mDriver = GraphicsFactory::createRenderFrameDriver(this);
        mDriver->init(); 
    }
    virtual void cleanup(){ 
        mDriver->cleanup(); 
        SAFE_DELETE(mDriver);
    }

    virtual void load(GraphicsContext *context){ mDriver->load(context); }
    virtual void unload(GraphicsContext *context){ mDriver->unload(context); }

    virtual const short getResourceType(){ return RESOURCETYPE_RENDERFRAME; }

    protected:
        FrameBufferType mBufferType;
        Size2 mResolution;

        RenderFrameDriver *mDriver;
    };
}

#endif // S3D_RENDERFRAME_H
