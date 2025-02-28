

#include "S3D/Application/GraphicsQueueThread.h"

#include "S3D/Application/GraphicsContext.h"

namespace S3D
{
    void GraphicsQueueThread::init()
    {
        QueueThread::init();

        if(mMakeSubContextInInit){
             mContext = mParentContext->createSubContext();
             mContext->init();
        }
    }

    void GraphicsQueueThread::cleanup()
    {   
        if(mMakeSubContextInInit){
            mContext->cleanup();
            SAFE_DELETE(mContext);
        }
        
        QueueThread::cleanup();
    }

    void GraphicsQueueThread::run()
    {
        if(!mMakeSubContextInInit){
            mContext = mParentContext->createSubContext();
            mContext->init();
        }

        mSetup.store(true);

        QueueThread::run();

        if(!mMakeSubContextInInit){
            mContext->cleanup();
            SAFE_DELETE(mContext);
        }
    }

    bool GraphicsQueueThread::addRequest(WorkRequest *req, const bool resume)
    {
        GraphicsWorkRequest *gReq = (GraphicsWorkRequest*) req;
        gReq->addGraphicsContext(mContext);
        QueueThread::addRequest(req, resume);
    }

}; //namespace S3D