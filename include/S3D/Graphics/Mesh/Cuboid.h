#ifndef S3D_MESH_CUBOID_H
#define S3D_MESH_CUBOID_H

#include "S3D/Graphics/Mesh.h"
#include "S3D/Graphics/Math/MathematicsTypes.h"

namespace S3D
{
    class Cuboid : public Mesh
    {
    public:
        Cuboid(float x = 0.5f, float y = 0.5f, float z = 0.5f)
            : Mesh(),
              mX(x),
              mY(y),
              mZ(z)
        {
        }

        virtual ~Cuboid() {}

        virtual void load(GraphicsContext *context){
            if(mVertexType & VERTEXTYPE_POSITION != 0) setPositions(mX, mY, mZ);
            if(mVertexType & VERTEXTYPE_NORMAL != 0) setNormal();
            if(mVertexType & VERTEXTYPE_UV != 0) setUvs();

            Mesh::load(context);
        }
        
        virtual void *getVertices() { return &mVertices[0]; }
        virtual unsigned int getNumVertices() { return 24; }
        virtual unsigned int getVerticesBufferSize() { return 24 * sizeof(Vector3); }
        virtual void *getNormals(){ return &mNormals[0];}
        virtual unsigned int getNumNormals(){ return 24; }
        virtual unsigned int getNormalsBufferSize(){ return 24 * sizeof(Vector3); }
        virtual void *getUvs() { return &mUvs[0]; }
        virtual unsigned int getNumUvs() { return 24; }
        virtual unsigned int getUvsBufferSize() { return 24 * sizeof(Vector2); }

        virtual void *getIndices() { return mIndices; }
        virtual unsigned int getNumIndices() { return 36; }
        virtual unsigned int getIndicesBufferSize() { return 36 * sizeof(int); }

        virtual void setPositions(float x = 0.1f, float y = 0.1f, float z = 0.1f)
        {
            mVertices.resize(24);

            float hx = mX / 2.0f;
            float hy = mY / 2.0f;
            float hz = mZ / 2.0f;

            mVertices[0].x = -hx; mVertices[0].y = -hy; mVertices[0].z = -hz;
            mVertices[1].x = hx; mVertices[1].y = -hy; mVertices[1].z = -hz;
            mVertices[2].x = hx; mVertices[2].y = hy; mVertices[2].z = -hz;
            mVertices[3].x = -hx; mVertices[3].y = hy; mVertices[3].z = -hz;

            mVertices[4].x = hx; mVertices[4].y = -hy; mVertices[4].z = -hz;
            mVertices[5].x = hx; mVertices[5].y = -hy; mVertices[5].z = hz;
            mVertices[6].x = hx; mVertices[6].y = hy; mVertices[6].z = hz;
            mVertices[7].x = hx; mVertices[7].y = hy; mVertices[7].z = -hz;

            mVertices[8].x = hx; mVertices[8].y = -hy; mVertices[8].z = hz;
            mVertices[9].x = -hx; mVertices[9].y = -hy; mVertices[9].z = hz;
            mVertices[10].x = -hx; mVertices[10].y = hy; mVertices[10].z = hz;
            mVertices[11].x = hx; mVertices[11].y = hy; mVertices[11].z = hz;

            mVertices[12].x = -hx; mVertices[12].y = -hy; mVertices[12].z = hz;
            mVertices[13].x = -hx; mVertices[13].y = -hy; mVertices[13].z = -hz;
            mVertices[14].x = -hx; mVertices[14].y = hy; mVertices[14].z = -hz;
            mVertices[15].x = -hx; mVertices[15].y = hy; mVertices[15].z = hz;

            mVertices[16].x = hx; mVertices[16].y = -hy; mVertices[16].z = -hz;
            mVertices[17].x = -hx; mVertices[17].y = -hy; mVertices[17].z = -hz;
            mVertices[18].x = -hx; mVertices[18].y = -hy; mVertices[18].z = hz;
            mVertices[19].x = hx; mVertices[19].y = -hy; mVertices[19].z = hz;

            mVertices[20].x = -hx; mVertices[20].y = hy; mVertices[20].z = -hz;
            mVertices[21].x = hx; mVertices[21].y = hy; mVertices[21].z = -hz;
            mVertices[22].x = hx; mVertices[22].y = hy; mVertices[22].z = hz;
            mVertices[23].x = -hx; mVertices[23].y = hy; mVertices[23].z = hz;
        }

        virtual void setNormal()
        {
            mNormals.resize(24);

            //TODO
        }

        void setUvs(
            const Vector2 &v1 = Vector2(0.0f, 1.0f), 
            const Vector2 &v2 = Vector2(1.0f, 1.0f),
            const Vector2 &v3 = Vector2(1.0f, 0.0f),
            const Vector2 &v4 = Vector2(0.0f, 0.0f)){
            mUvs.resize(24);
            mUvs[0] = v1; mUvs[1] = v2; mUvs[2] = v3; mUvs[3] = v4;
            mUvs[4] = v1; mUvs[5] = v2; mUvs[6] = v3; mUvs[7] = v4;
            mUvs[8] = v1; mUvs[9] = v2; mUvs[10] = v3; mUvs[11] = v4;
            mUvs[12] = v1; mUvs[13] = v2; mUvs[14] = v3; mUvs[15] = v4;
            mUvs[16] = v1; mUvs[17] = v2; mUvs[18] = v3; mUvs[19] = v4;
            mUvs[20] = v1; mUvs[21] = v2; mUvs[22] = v3; mUvs[23] = v4;
        }

    protected:
        float mX;
        float mY;
        float mZ;

        std::vector<Vector3> mVertices;
        std::vector<Vector3> mNormals;
        std::vector<Vector2> mUvs;

        int mIndices[36] = {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7,
            8, 9, 10, 8, 10, 11,
            12, 13, 14, 12, 14, 15,
            16, 17, 18, 16, 18, 19,
            20, 21, 22, 20, 22, 23};

    };

}; // namespace S3D

#endif // S3D_MESH_CUBOID_H
