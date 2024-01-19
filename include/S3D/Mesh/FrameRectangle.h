#ifndef S3D_MESH_FRAMERECTANGLE_H
#define S3D_MESH_FRAMERECTANGLE_H

#include "S3D/Mesh/Mesh.h"
#include "S3D/Math/MathematicsTypes.h"

namespace S3D
{
    class FrameRectangle : public Mesh
    {
    public:
        FrameRectangle(
            float width = 0.1f, float height = 0.1f,
            float top = 0.01f, float right = 0.01f, float bottom = 0.01f, float left = 0.01f,
            float uvMarginTop = 0.25f, float uvMarginRight = 0.25f, float uvMarginBottom = 0.25f, float uvMarginLeft = 0.25f)
            : mWidth(width),
              mHeight(height),
              mTop(top),
              mRight(right),
              mBottom(bottom),
              mLeft(left),
              mMarginTop(uvMarginTop),
              mMarginRight(uvMarginRight),
              mMarginBottom(uvMarginBottom),
              mMarginLeft(uvMarginLeft)
        {
        }

        virtual ~FrameRectangle() {}

        virtual void init()
        {
            setIndices();
            setParam(mWidth, mHeight, mTop, mRight, mBottom, mLeft, mMarginTop, mMarginRight, mMarginBottom, mMarginLeft);
        }
        virtual void cleanup() {}

        virtual void *getVertices() { return mVertices; }
        virtual unsigned int getNumVertices() { return 16; }
        virtual unsigned int getVerticesBufferSize() { return 16 * sizeof(Vector3); }
        virtual void *getIndices() { return mIndices; }
        virtual unsigned int getNumIndices() { return 54; }
        virtual unsigned int getIndicesBufferSize() { return 54 * sizeof(int); }
        virtual void *getUvs() { return mUvs; }
        virtual unsigned int getNumUvs() { return 16; }
        virtual unsigned int getUvsBufferSize() { return 16 * sizeof(Vector2); }

        virtual void setIndices()
        {
            for (int y = 0; y < 3; y++)
            {
                for (int x = 0; x < 3; x++)
                {
                    int r = y * 3 + x;
                    int index = y * 4 + x;

                    mIndices[r * 6] = index;
                    mIndices[r * 6 + 1] = index + 1;
                    mIndices[r * 6 + 2] = index + 4 + 1;

                    mIndices[r * 6 + 3] = index;
                    mIndices[r * 6 + 4] = index + 4 + 1;
                    mIndices[r * 6 + 5] = index + 4;
                }
            }
        }

        virtual void setParam(float width = 0.1f, float height = 0.1f,
                              float top = 0.01f, float right = 0.01f, float bottom = 0.01f, float left = 0.01f,
                              float uvMarginTop = 0.25f, float uvMarginRight = 0.25f, float uvMarginBottom = 0.25f, float uvMarginLeft = 0.25f)
        {
            mWidth = width;
            mHeight = height;
            mTop = top;
            mRight = right;
            mBottom = bottom;
            mLeft = left;
            mMarginTop = uvMarginTop;
            mMarginRight = uvMarginRight;
            mMarginBottom = uvMarginBottom;
            mMarginLeft = uvMarginLeft;

            float hwidth = mWidth / 2.0f;
            float hheight = mHeight / 2.0f;

            mVertices[0].x = -hwidth;
            mVertices[0].y = -hheight;
            mVertices[0].z = 0.0f;
            mVertices[1].x = -hwidth + mLeft;
            mVertices[1].y = -hheight;
            mVertices[1].z = 0.0f;
            mVertices[2].x = hwidth - mRight;
            mVertices[2].y = -hheight;
            mVertices[2].z = 0.0f;
            mVertices[3].x = hwidth;
            mVertices[3].y = -hheight;
            mVertices[3].z = 0.0f;

            mVertices[4].x = -hwidth;
            mVertices[4].y = -hheight + mBottom;
            mVertices[4].z = 0.0f;
            mVertices[5].x = -hwidth + mLeft;
            mVertices[5].y = -hheight + mBottom;
            mVertices[5].z = 0.0f;
            mVertices[6].x = hwidth - mRight;
            mVertices[6].y = -hheight + mBottom;
            mVertices[6].z = 0.0f;
            mVertices[7].x = hwidth;
            mVertices[7].y = -hheight + mBottom;
            mVertices[7].z = 0.0f;

            mVertices[8].x = -hwidth;
            mVertices[8].y = hheight - mTop;
            mVertices[8].z = 0.0f;
            mVertices[9].x = -hwidth + mLeft;
            mVertices[9].y = hheight - mTop;
            mVertices[9].z = 0.0f;
            mVertices[10].x = hwidth - mRight;
            mVertices[10].y = hheight - mTop;
            mVertices[10].z = 0.0f;
            mVertices[11].x = hwidth;
            mVertices[11].y = hheight - mTop;
            mVertices[11].z = 0.0f;

            mVertices[12].x = -hwidth;
            mVertices[12].y = hheight;
            mVertices[12].z = 0.0f;
            mVertices[13].x = -hwidth + mLeft;
            mVertices[13].y = hheight;
            mVertices[13].z = 0.0f;
            mVertices[14].x = hwidth - mRight;
            mVertices[14].y = hheight;
            mVertices[14].z = 0.0f;
            mVertices[15].x = hwidth;
            mVertices[15].y = hheight;
            mVertices[15].z = 0.0f;

            mUvs[0].x = 0.0f;
            mUvs[0].y = 1.0f;
            mUvs[1].x = mMarginLeft;
            mUvs[1].y = 1.0f;
            mUvs[2].x = 1.0 - mMarginRight;
            mUvs[2].y = 1.0f;
            mUvs[3].x = 1.0f;
            mUvs[3].y = 1.0f;

            mUvs[4].x = 0.0f;
            mUvs[4].y = 1.0f - mMarginBottom;
            mUvs[5].x = mMarginLeft;
            mUvs[5].y = 1.0f - mMarginBottom;
            mUvs[6].x = 1.0 - mMarginRight;
            mUvs[6].y = 1.0f - mMarginBottom;
            mUvs[7].x = 1.0f;
            mUvs[7].y = 1.0f - mMarginBottom;

            mUvs[8].x = 0.0f;
            mUvs[8].y = mMarginTop;
            mUvs[9].x = mMarginLeft;
            mUvs[9].y = mMarginTop;
            mUvs[10].x = 1.0 - mMarginRight;
            mUvs[10].y = mMarginTop;
            mUvs[11].x = 1.0f;
            mUvs[11].y = mMarginTop;

            mUvs[12].x = 0.0f;
            mUvs[12].y = 0.0f;
            mUvs[13].x = mMarginLeft;
            mUvs[13].y = 0.0f;
            mUvs[14].x = 1.0 - mMarginRight;
            mUvs[14].y = 0.0f;
            mUvs[15].x = 1.0f;
            mUvs[15].y = 0.0f;
        }

    protected:
        float mWidth;
        float mHeight;
        float mTop;
        float mRight;
        float mBottom;
        float mLeft;
        float mMarginTop;
        float mMarginRight;
        float mMarginBottom;
        float mMarginLeft;

        Vector3 mVertices[16];
        int mIndices[54];
        Vector2 mUvs[16];
    };

}; // namespace S3D

#endif // S3D_MESH_FRAMERECTANGLE_H
