#ifndef S3D_CAMERA_H
#define S3D_CAMERA_H

#include "S3D/Entity.h"

namespace S3D
{
    class Camera : public Entity
    {
    public:
        Camera()
            : Entity(),
              mNeedRender(true)
        {
        }

        virtual ~Camera() {}

        virtual const bool needRender()
        {
            return Entity::needRender() || mNeedRender;
        }
        virtual void resetNeedRender()
        {
            Entity::resetNeedRender();
            mNeedRender = false;
        }

        virtual void updateState();

        void ortho(float left, float right, float bottom, float top, float near, float far);
        void perspective(float fovy, float aspect, float near, float far);

        S3D::Matrix44 &getProjectionMatrix() { return mProjection; }

    protected:
        S3D::Matrix44 mProjection;
        bool mNeedRender;
    };
}

#endif // S3D_CAMERA_H
