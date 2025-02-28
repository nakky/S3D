#ifndef S3D_RESOURCE_H
#define S3D_RESOURCE_H

#include "S3D/Common.h"

namespace S3D
{
    class GraphicsContext;
    
    enum ResourceType
    {
        RESOURCETYPE_MESH = 50001,
        RESOURCETYPE_MATERIAL = 50002,
        RESOURCETYPE_TEXTURE2D = 50003,

        RESOURCETYPE_RENDERFRAME = 50101,
        RESOURCETYPE_SHADER = 50102,
    };

    class Resource
    {
    public:
        Resource()
            :mResourceId(0)
        {
        }

        virtual ~Resource() {}

        virtual void init() {}
        virtual void cleanup() {}

        virtual void load(GraphicsContext *context){}
        virtual void unload(GraphicsContext *context){}

        virtual const short getResourceType() = 0;

        unsigned int getResourceId() { return mResourceId; }
        void setResourceId(unsigned id) { mResourceId = id; }

    protected:
        unsigned int mResourceId;
    };

}; // namespace S3D

#endif // S3D_RESOURCE_H
