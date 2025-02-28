
#include "S3D/Graphics/Camera.h"

namespace S3D
{
    void Camera::updateViewProjection(const GeometricState *state)
    {
        mViewProjection.setUnitMatrix();

        Matrix44 projMat;
        projMat.setUnitMatrix();

        if(mProjectionMode == PROJECTION_ORTHOGONAL){
            projMat.m[0][0] = -2.0f / (mOrthgonalSize * mAspect);
            projMat.m[1][1] = 2.0f / mOrthgonalSize;
            projMat.m[2][2] = -2.0f / (mFarPlane - mNearPlane);
            projMat.m[3][2] = -(mFarPlane + mNearPlane) / (mFarPlane - mNearPlane);
            projMat.m[3][3] = 1.0f;
                            
        }else{
            float s, cot, diff;
            
            float radians = mFieldOfView / 2.0f * PIF / 180.0f;
            
            diff = mFarPlane - mNearPlane;
            s = sin(radians);
            if ((diff == 0) || (s == 0) || (mAspect == 0)) return;
            
            cot = ::cos(radians) / s;
            
            projMat.m[0][0] = -cot / mAspect;
            projMat.m[1][1] = cot;
            projMat.m[2][2] = -(mFarPlane + mNearPlane) / diff;
            projMat.m[2][3] = -1.0f;
            projMat.m[3][2] = -2.0f * mFarPlane * mNearPlane / diff;
            projMat.m[3][3] = 0.0f;
        }
        
        Matrix44 mat;
        mat.setUnitMatrix();

        Vector3 tmpvec;

        state->rotation.convertVector(tmpvec, Vector3(-1.0f, 0.0f, 0.0f));
        mat.m[0][0] = tmpvec.x;
        mat.m[1][0] = tmpvec.y;
        mat.m[2][0] = tmpvec.z;

        state->rotation.convertVector(tmpvec, Vector3(0.0f, 1.0f, 0.0f));
        mat.m[0][1] = tmpvec.x;
        mat.m[1][1] = tmpvec.y;
        mat.m[2][1] = tmpvec.z;

        state->rotation.convertVector(tmpvec, Vector3(0.0f, 0.0f, -1.0f));
        mat.m[0][2] = tmpvec.x;
        mat.m[1][2] = tmpvec.y;
        mat.m[2][2] = tmpvec.z;

        Matrix44 translation;
        translation.setTransrationMatrix(-state->position.x, -state->position.y, -state->position.z);
        
        mViewProjection =  projMat * mat * translation;
    }

}; //namespace S3D

