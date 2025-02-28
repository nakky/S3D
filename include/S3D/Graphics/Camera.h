#ifndef S3D_CAMERA_H
#define S3D_CAMERA_H

#include "S3D/Game/Entity.h"

namespace S3D
{
    //implemented
    class Camera;
    
    enum ProjectionMode
    {
        PROJECTION_ORTHOGONAL,
        PROJECTION_PERSPECTIVE
    };
    
    class Camera 
    {
    public:
        Camera():
        mProjectionMode(PROJECTION_ORTHOGONAL),
        mResoultion(1920, 1080),
        mViewport(Rectf4(0.0f, 0.0f, 1.0f, 1.0f)),
        mBackgroundColor(Color4::black),
        mNearPlane(0.1f),
        mFarPlane(100.0f),
        mOrthgonalSize(2.0f),
        mFieldOfView(45.0f)
        {
            mAspect = (float)mViewport.width / (float)mViewport.height;
        }

        virtual ~Camera() {}
        
        void setProjectionMode(const ProjectionMode mode)  { mProjectionMode = mode; }
        ProjectionMode getProjectionMode() const { return mProjectionMode; }
        
        void setViewport(const Rectf4 &viewPort){ mViewport = viewPort; }
        const Rectf4 *getViewport() const { return &mViewport; }

        void setResolution(const Size2 &resolution) { 
            mResoultion = resolution; 
            setAspect((float)mResoultion.width / (float)mResoultion.height);
        }
        const Size2 *getResolution() const { return &mResoultion; }
        
        void setNearPlane(const float nearPlane) { mNearPlane = nearPlane; }
        float getNearPlane() const { return mNearPlane; }
        
        void setFarPlane(const float farPlane) { mFarPlane = farPlane; }
        float getFarPlane() const { return mFarPlane; }
        
        //Orthogonal
        void setOrthgonalSize(const float &size){ mOrthgonalSize = size; }
        const float getOrthgonalSize() const { return mOrthgonalSize; }
        
        //Perspective
        void setFieldOfView(const float angle) { mFieldOfView = angle; }
        float getFieldOfView() const { return mFieldOfView; }
        
        float getAspect() const {return mAspect;}

        void setBackgroundColor(const Color4 color) { mBackgroundColor = color; }
        const Color4 &getBackgroundColor() const {return mBackgroundColor;}

        const Matrix44 *getViewProjection() const { return &mViewProjection; }
        void updateViewProjection(const GeometricState *state);
    protected:
        void setAspect(const float aspect) { mAspect = aspect; }
    
    protected:
        ProjectionMode mProjectionMode;

        Color4 mBackgroundColor;
        
        Rectf4 mViewport;

        Size2 mResoultion;

        float mNearPlane;
        float mFarPlane;
        
        //Orthogonal
        float mOrthgonalSize;

        //Persprctive
        float mFieldOfView;
        float mAspect;

        Matrix44 mViewProjection;
    };
}

#endif // S3D_CAMERA_H
