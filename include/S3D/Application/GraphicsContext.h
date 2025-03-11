#ifndef S3D_APPLICATION_GRAPHICSCONTEXT_H
#define S3D_APPLICATION_GRAPHICSCONTEXT_H

#include "S3D/Common.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"

#include <vector>
#include <string>
#include <atomic>
#include <map>

#if defined OS_LINUX
#include <unistd.h>
#endif

namespace S3D
{
    class GraphicsContext
    {
    public:
        GraphicsContext(const Size2 &resolution):
        mResolution(resolution)
        {
        }

    public:

        virtual void init(){}
        virtual void cleanup(){}

        virtual void bind() = 0;
        virtual void release() = 0;

        const Size2 *getResolution() const { return &mResolution; }
        virtual const Size2 *getFrambufferResolution() { return &mResolution; }

        virtual GraphicsContext *createSubContext() = 0;

        Size2 mResolution;
    };

}; //namespace S3D

#endif //S3D_APPLICATION_GRAPHICSCONTEXT_H
