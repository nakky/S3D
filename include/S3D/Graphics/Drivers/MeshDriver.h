#ifndef S3D_GRAPHICS_MESHDRIVER_H
#define S3D_GRAPHICS_MESHDRIVER_H

#include "S3D/Common.h"

namespace S3D
{
    class Mesh;
    class GraphicsContext;

    class MeshDriver
    {
    public:
        MeshDriver(Mesh *mesh)
        :mMesh(mesh)
        {
        }

        virtual ~MeshDriver() {}

        virtual void init(){}
        virtual void cleanup(){}

        virtual void load(GraphicsContext *context) = 0;
        virtual void unload(GraphicsContext *context) = 0;

    protected:
        Mesh *mMesh;
    };

};

#endif //S3D_GRAPHICS_MESHDRIVER_H

