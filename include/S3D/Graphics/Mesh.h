#ifndef S3D_MESH_H
#define S3D_MESH_H

#include "S3D/Common.h"
#include "S3D/Foundation/Resource.h"

#include "S3D/Graphics/Drivers/MeshDriver.h"

#include "S3D/Application/GraphicsFactory.h"

namespace S3D
{
    enum VertexType
    {
        VERTEXTYPE_POSITION = 1,
        VERTEXTYPE_NORMAL = 1 << 1,
        VERTEXTYPE_UV = 1 << 2,
    };

    class Mesh : public Resource
    {
    public:
        Mesh()
            : Resource(),
            mIsStatic(true)
        {
        }

        virtual ~Mesh() {}

        void setIsStatic(const bool isStatic) { mIsStatic = isStatic; }

        void setVertexType(const int type) { mVertexType = type; }
        int getVertexType() const { return mVertexType; }

        virtual const short getResourceType() { return RESOURCETYPE_MESH; }

        virtual void *getVertices() = 0;
        virtual unsigned int getNumVertices() = 0;
        virtual unsigned int getVerticesBufferSize() = 0;

        virtual void *getNormals() = 0;
        virtual unsigned int getNumNormals() = 0;
        virtual unsigned int getNormalsBufferSize() = 0;

        virtual void *getUvs() = 0;
        virtual unsigned int getNumUvs() = 0;
        virtual unsigned int getUvsBufferSize() = 0;

        virtual void *getIndices() = 0;
        virtual unsigned int getNumIndices() = 0;
        virtual unsigned int getIndicesBufferSize() = 0;

        MeshDriver *getDriver() const { return mDriver; }

        virtual void init(){ 
            mDriver = GraphicsFactory::createMeshDriver(this);
            mDriver->init(); 
        }
        virtual void cleanup(){ 
            mDriver->cleanup(); 
            SAFE_DELETE(mDriver);
        }

        virtual void load(GraphicsContext *context){ mDriver->load(context); }
        virtual void unload(GraphicsContext *context){ mDriver->unload(context); }


    protected:
        bool mIsStatic;
        int mVertexType;

        MeshDriver *mDriver;

    };

}; // namespace S3D

#endif // S3D_MESH_H
