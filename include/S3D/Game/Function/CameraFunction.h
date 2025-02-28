#ifndef S3D_GAME_FUNCTION_CAMERAFUNCTION_H
#define S3D_GAME_FUNCTION_CAMERAFUNCTION_H

#include "S3D/Game/Function/EntityFunction.h"
#include "S3D/Graphics/Camera.h"

namespace S3D
{
    class Color;

    class CameraFunction : public EntityFunction
    {
    public:
        CameraFunction()
        :EntityFunction(),
        mCamera()
        {
        }

        virtual ~CameraFunction() {}

        constexpr virtual unsigned long getFunctionType() { return entityNameHash("S3D::CameraFunction");}

        Camera *getCamera(){ return &mCamera; }

        virtual const bool isCamera() const { return true; }

        void setBackgroundColor(const Color4 &color) { mCamera.setBackgroundColor(color); }
        void setFarPlane(const float &farPlane) { mCamera.setFarPlane(farPlane); }
        void setNearPlane(const float &nearPlane) { mCamera.setNearPlane(nearPlane); }
        void setFieldOfView(const float &angle) { mCamera.setFieldOfView(angle); }
        void setOrthgonalSize(const float &size) { mCamera.setOrthgonalSize(size); }
        void setProjectionMode(const ProjectionMode &mode) { mCamera.setProjectionMode(mode); }
        void setViewport(const Rectf4 &viewPort) { mCamera.setViewport(viewPort); }

    protected:
        Camera mCamera;
    };

};

#endif //S3D_GAME_FUNCTION_CAMERAFUNCTION_H

