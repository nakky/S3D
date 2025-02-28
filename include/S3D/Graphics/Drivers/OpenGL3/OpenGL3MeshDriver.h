#ifndef S3D_GRAPHICS_OPENGL3MESHDRIVER_H
#define S3D_GRAPHICS_OPENGL3MESHDRIVER_H

#include "S3D/Common.h"
#include "S3D/Graphics/Drivers/MeshDriver.h"

namespace S3D
{
    class GraphicsContext;
    
    class OpenGL3MeshDriver : public MeshDriver
    {
    public:
        OpenGL3MeshDriver(Mesh *mesh)
        :MeshDriver(mesh)
        {
        }

        virtual ~OpenGL3MeshDriver() {}

        unsigned int getPositionVao() const { return mPositionVao; }
       
        unsigned int getPositionBuffer() const { return mPositionBuffer; }
        unsigned int getNormalBuffer() const { return mNormalBuffer; }
        unsigned int getUVBuffer() const { return mUVBuffer; }
        unsigned int getIndexBuffer() const { return mIndexBuffer; }

        virtual void load(GraphicsContext *context);
        virtual void unload(GraphicsContext *context);

    protected:
        unsigned int mPositionVao;

        unsigned int mPositionBuffer;
        unsigned int mNormalBuffer;
        unsigned int mUVBuffer;

        unsigned int mIndexBuffer;
    };

};

#endif //S3D_GRAPHICS_OPENGL3MESH_H

