
#include "S3D/Camera.h"

namespace S3D
{
    void Camera::updateState()
    {
        Entity::updateState();
    }

    void Camera::ortho(float left, float right, float bottom, float top, float near, float far)
    {
        mProjection.m[0][0] = 2.f / (right - left);
        mProjection.m[0][1] = mProjection.m[0][2] = mProjection.m[0][3] = 0.f;

        mProjection.m[1][1] = 2.f / (top - bottom);
        mProjection.m[1][0] = mProjection.m[1][2] = mProjection.m[1][3] = 0.f;

        mProjection.m[2][2] = -2.f / (far - near);
        mProjection.m[2][0] = mProjection.m[2][1] = mProjection.m[2][3] = 0.f;

        mProjection.m[3][0] = -(right + left) / (right - left);
        mProjection.m[3][1] = -(top + bottom) / (top - bottom);
        mProjection.m[3][2] = -(far + near) / (far - near);
        mProjection.m[3][3] = 1.f;

        mNeedRender = true;
    }

    void Camera::perspective(float fovy, float aspect, float near, float far)
    {
        float const a = 1.f / tanf(fovy / 2.f);

        mProjection.m[0][0] = a / aspect;
        mProjection.m[0][1] = 0.f;
        mProjection.m[0][2] = 0.f;
        mProjection.m[0][3] = 0.f;

        mProjection.m[1][0] = 0.f;
        mProjection.m[1][1] = a;
        mProjection.m[1][2] = 0.f;
        mProjection.m[1][3] = 0.f;

        mProjection.m[2][0] = 0.f;
        mProjection.m[2][1] = 0.f;
        mProjection.m[2][2] = -((far + near) / (far - near));
        mProjection.m[2][3] = -1.f;

        mProjection.m[3][0] = 0.f;
        mProjection.m[3][1] = 0.f;
        mProjection.m[3][2] = -((2.f * far * near) / (far - near));
        mProjection.m[3][3] = 0.f;

        mNeedRender = true;
    }

} // namespace S3D
