
#include "S3D/Application/DrawScheme/ThreadedDrawScheme.h"

#include "S3D/Application/ContentApp.h"
#include "S3D/Graphics/Renderer.h"
#include "S3D/Application/GraphicsFactory.h"
#include "S3D/Graphics/RenderFrame.h"
#include "S3D/Game/Function/CameraFunction.h"
#include "S3D/Game/Function/RendererFunction.h"

namespace S3D
{
    bool PreDrawWorkRequest::work()
    {
        return true;
    }
    
    bool DrawWorkRequest::work()
    {
        mContext->bind();        


        mContext->release();

        return true;
    }

    bool PostDrawWorkRequest::work()
    {
        mApplication->swapBuffers(mContext);
        return true;
    }

    void ThraededDrawScheme::init()
    {
        DrawScheme::init();

        mThread = new GraphicsQueueThread(mApplication->getMainGraphicsContext(), mApplication->IsCreatedSubContextInMain());
        mThread->init();
        mThread->start();
    }
    
    void ThraededDrawScheme::cleanup()
    {
        if(mThread != NULL){
            mThread->cleanup();
            SAFE_DELETE(mThread);
        }   
        DrawScheme::cleanup();
    }
    
    bool ThraededDrawScheme::update()
    {
        return false;
    }

    void ThraededDrawScheme::draw()
    {
        
    }

}; //namespace S3D