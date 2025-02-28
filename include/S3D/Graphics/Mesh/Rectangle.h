#ifndef S3D_MESH_RECTANGLE_H
#define S3D_MESH_RECTANGLE_H

#include "S3D/Graphics/Mesh.h"
#include "S3D/Graphics/Math/MathematicsTypes.h"

#include <vector>

namespace S3D
{
    class Rectangle : public Mesh
    {
    public:
        Rectangle(
            float width = 0.1f, float height = 0.1f)
            : Mesh(),
              mWidth(width),
              mHeight(height)
        {
        }

        virtual ~Rectangle() {}

        virtual void load(GraphicsContext *context){
            if(mVertexType & VERTEXTYPE_POSITION != 0) setPositions(mWidth, mHeight);
            if(mVertexType & VERTEXTYPE_NORMAL != 0) setNormals();
            if(mVertexType & VERTEXTYPE_UV != 0) setUvs();
            
            setIndices();

            Mesh::load(context);
        }

        virtual void *getVertices() { return &mVertices[0]; }
        virtual unsigned int getNumVertices() { return 4; }
        virtual unsigned int getVerticesBufferSize() { return 4 * sizeof(Vector3); }
        virtual void *getIndices() { return &mIndices[0]; }
        virtual unsigned int getNumIndices() { return 6; }
        virtual unsigned int getIndicesBufferSize() { return 6 * sizeof(int); }
        virtual void *getUvs() { return &mUvs[0]; }
        virtual unsigned int getNumUvs() { return 4; }
        virtual unsigned int getUvsBufferSize() { return 4 * sizeof(Vector2); }

        virtual void setPositions(float width, float height)
        {
            mVertices.resize(4);

            mWidth = width;
            mHeight = height;
            float hwidth = mWidth / 2.0f;
            float hheight = mHeight / 2.0f;
            mVertices[0].x = -hwidth;
            mVertices[0].y = -hheight;
            mVertices[0].z = 0.0f;
            mVertices[1].x = hwidth;
            mVertices[1].y = -hheight;
            mVertices[1].z = 0.0f;
            mVertices[2].x = hwidth;
            mVertices[2].y = hheight;
            mVertices[2].z = 0.0f;
            mVertices[3].x = -hwidth;
            mVertices[3].y = hheight;
            mVertices[3].z = 0.0f;
        }

        virtual void setPositions()
        {
            mNormals.resize(4);
            //TODO
        }

        virtual void setUvs()
        {
            mUvs.resize(4);

            mUvs[0] = Vector2(0.0f, 1.0f);
            mUvs[1] = Vector2(1.0f, 1.0f);
            mUvs[2] = Vector2(1.0f, 0.0f);
            mUvs[3] = Vector2(0.0f, 0.0f);
        }


    protected:
        float mWidth;
        float mHeight;

        std::vector<Vector3> mVertices;
        std::vector<Vector3> mNormals;
        std::vector<Vector2> mUvs;

        int mIndices[6] = {0, 1, 2, 0, 2, 3};
    };

}; // namespace S3D

#endif // S3D_MESH_RECTANGLE_H
