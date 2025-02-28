
#include "S3D/Application/ContentApp.h"

#include "S3D/Application/DrawScheme.h"
#include "S3D/Application/DrawScheme/SimpleDrawScheme.h"
#include "S3D/Application/DrawScheme/ThreadedDrawScheme.h"
#include "S3D/Application/AppDriver.h"

#include "S3D/Application/GraphicsFactory.h"

#include "S3D/Foundation/Timer.h"

namespace S3D
{
    bool LoadWorkRequest::work()
    {
        if(!GraphicsFactory::isLoaded()) GraphicsFactory::load(mContext);
        mContent->load(mContext);
        mContent->postLoad(mContext);
        return true;
    }

    bool UnloadWorkRequest::work()
    {
        mContent->preUnload(mContext);
        mContent->unload(mContext);
        return true;
    }

    bool ContentApp::init()
    {
        mAppDriver = GraphicsFactory::createAppDriver(this);
        mAppDriver->init();

        bool ret = App::init();
        return ret;
    }

    bool ContentApp::cleanup()
    {
        mContentLoadThread->cleanup();
        SAFE_DELETE(mContentLoadThread);

        mContentUnloadThread->cleanup();
        SAFE_DELETE(mContentUnloadThread);

        mAssetLoadThread->cleanup();
        SAFE_DELETE(mAssetLoadThread);

        mSystemProcessThread->cleanup();
        SAFE_DELETE(mSystemProcessThread);

         if(mDrawScheme == NULL){
            mDrawScheme->cleanup();
            SAFE_DELETE(mDrawScheme);
        }

        for(auto ite = mCurrentContents.begin() ; ite != mCurrentContents.end() ; ite++)
        {
            (*ite)->unload(mMainGraphicsContext);
            (*ite)->cleanup();
            SAFE_DELETE(*ite);
        }

        if(mAppDriver != NULL) {
            mAppDriver->cleanup();
            SAFE_DELETE(mAppDriver);
        }

        bool ret = App::cleanup();
        return ret;
    }

    void ContentApp::onCreateContext(GraphicsContext *context)
    {
        App::onCreateContext(context);

        mContentLoadThread = new GraphicsQueueThread(mMainGraphicsContext, IsCreatedSubContextInMain());
        mContentLoadThread->init();
        mContentLoadThread->start();

        mContentUnloadThread = new GraphicsQueueThread(mMainGraphicsContext, IsCreatedSubContextInMain());
        mContentUnloadThread->init();
        mContentUnloadThread->start();

        mAssetLoadThread = new GraphicsQueueThread(mMainGraphicsContext, IsCreatedSubContextInMain());
        mAssetLoadThread->init();
        mAssetLoadThread->start();

        mSystemProcessThread = new GraphicsQueueThread(mMainGraphicsContext, IsCreatedSubContextInMain());
        mSystemProcessThread->init();
        mSystemProcessThread->start();

        while(true){
            Timer::sleep(0.1f);
            if(
                mContentLoadThread->isSetup() 
                && mContentUnloadThread->isSetup() 
                &&  mAssetLoadThread->isSetup()
                &&  mSystemProcessThread->isSetup()
                ) break;
        }

        if(mDrawScheme == NULL){
            mDrawScheme = new SimpleDrawScheme(this);
            mDrawScheme->init();
        }
        addNextContent(mDefaultContent);
    }


    void ContentApp::fixedUpdate(float delta)
    {
        for(auto ite = mCurrentContents.begin() ; ite != mCurrentContents.end() ; ite++)
        {
            (*ite)->fixedUpdate(delta);
        }
    }


    bool ContentApp::update(float delta)
    {
        bool draw = false;
        for(auto ite = mCurrentContents.begin() ; ite != mCurrentContents.end() ; ite++)
        {
            draw = (*ite)->update(delta);
        }
        
        if(mLoadContentQueueu.size() > 0){
            LoadWorkRequest * req = mLoadContentQueueu.front();
            if(req->isDone()){
                mLoadContentQueueu.pop();
                auto content = req->getContent();
                content->prepare();
                req->cleanup();
                SAFE_DELETE(req);
                mCurrentContents.push_back(content);
            }
        }

        if(mUnloadContentQueueu.size() > 0){
            UnloadWorkRequest * req = mUnloadContentQueueu.front();
            if(req->isDone()){
                mUnloadContentQueueu.pop();
                Content *content = req->getContent();
                content->cleanup();
                SAFE_DELETE(content);
                req->cleanup();
                SAFE_DELETE(req);
            }
        }

        return mDraw || draw;
    }

    GraphicsContext *ContentApp::createMainContext()
    {
        return mAppDriver->createMainContext();
    }

    void ContentApp::runningProcessQueue()
    {
        if(!mAppDriver->runningProcessQueue()) quit();
    }

    void ContentApp::swapBuffers(GraphicsContext *contet)
    {
         mAppDriver->swapBuffers(contet);
    }

   
    void ContentApp::addNextContent(Content *content)
    {
        content->init();
        content->setApplication(this);
        content->setContext(mMainGraphicsContext, mAssetLoadThread);
        LoadWorkRequest *req = new LoadWorkRequest(content);
        mLoadContentQueueu.push(req);
        mContentLoadThread->addRequest(req);
    }

    void ContentApp::addRemoveContent(Content *content)
    {
        for(auto ite = mCurrentContents.begin() ; ite != mCurrentContents.end() ; ite++)
        {
            if(*ite == content){
                mCurrentContents.erase(ite);
                break;
            } 
        }
        UnloadWorkRequest *req = new UnloadWorkRequest(content);
        mUnloadContentQueueu.push(req);
        mContentUnloadThread->addRequest(req);
    }

    bool ContentApp::geometryUpdate(float delta)
    {
        return mDrawScheme->update();
    }

    void ContentApp::systemDraw()
    {
        mDrawScheme->draw();
    }

}; //namespace S3D