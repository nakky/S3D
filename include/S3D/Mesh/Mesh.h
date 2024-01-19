#ifndef S3D_MESH_H
#define S3D_MESH_H

#include "S3D/Resource.h"

namespace S3D
{

    class Mesh : public Resource
    {
    public:
        Mesh()
            : Resource()
        {
        }

        virtual ~Mesh() {}

        virtual const short getResourceType() { return RESOURCETYPE_MESH; }

        virtual const bool needRender() { return false; }
        virtual void resetNeedRender() {}

        virtual void *getVertices() = 0;
        virtual unsigned int getNumVertices() = 0;
        virtual unsigned int getVerticesBufferSize() = 0;
        virtual void *getIndices() = 0;
        virtual unsigned int getNumIndices() = 0;
        virtual unsigned int getIndicesBufferSize() = 0;
        virtual void *getUvs() = 0;
        virtual unsigned int getNumUvs() = 0;
        virtual unsigned int getUvsBufferSize() = 0;
    };

}; // namespace S3D

#endif // S3D_MESH_H
