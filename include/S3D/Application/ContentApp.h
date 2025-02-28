#ifndef S3D_APPLICATION_CONTENTAPP_H
#define S3D_APPLICATION_CONTENTAPP_H

#include "S3D/Common.h"
#include "S3D/Application/App.h"

#include "S3D/Application/GraphicsQueueThread.h"
#include "S3D/Application/DrawScheme.h"
#include "S3D/Application/AppDriver.h"
#include "S3D/Game/Content.h"

#include <queue>

namespace S3D
{    
    class AppDriver;

    class LoadWorkRequest : public GraphicsWorkRequest
    {
        public:
        LoadWorkRequest(Content *content)
        :GraphicsWorkRequest(PRIORITY_HIGH, false),
        mContent(content)
        {}

        virtual ~LoadWorkRequest(){}

        Content *getContent() { return mContent; }

        virtual bool work();
        protected:
        Content *mContent;
    };

    class UnloadWorkRequest : public GraphicsWorkRequest
    {
        public:
        UnloadWorkRequest(Content *content)
        :GraphicsWorkRequest(PRIORITY_HIGH, false),
        mContent(content)
        {}

        virtual ~UnloadWorkRequest(){}

        Content *getContent() { return mContent; }

        virtual bool work();
        protected:
        Content *mContent;
    };

    class ContentApp : public App
    {
    public:
        ContentApp(
            int argc, char *argv[], 
            Content* defaultContent, 
            const DisplayMode &dispMode,
            const GraphicsMode &grapMode,
            DrawScheme *drawScheme = NULL
            )
        :App(argc, argv, dispMode, grapMode),
        mDraw(true),
        mDrawScheme(drawScheme),
        mDefaultContent(defaultContent)
        {
        }

        virtual bool init();
        virtual bool cleanup();

        virtual void onCreateContext(GraphicsContext *context);

        virtual bool update(float delta);
        virtual void fixedUpdate(float delta);

        virtual bool geometryUpdate(float delta);
        virtual void systemDraw();
        
        virtual GraphicsContext *createMainContext();
        virtual void runningProcessQueue();
        virtual void swapBuffers(GraphicsContext *contet);

        bool IsCreatedSubContextInMain() { return mAppDriver->isCreateSubContextInMainThread(); }

        std::list<Content*> *getCurrentContents(){ return &mCurrentContents; }

        virtual void getDisplayModes(std::vector<DisplayMode> &modes) const { return mAppDriver->getDisplayModes(modes); }
        virtual void changeDisplayMode(const DisplayMode &mode) { mAppDriver->changeDisplayMode(mode); }

    protected:
        void addNextContent(Content *content);
        void addRemoveContent(Content *content);

    protected:
        std::list<Content*> mCurrentContents;

        GraphicsQueueThread *mContentLoadThread;
        GraphicsQueueThread *mContentUnloadThread;
        GraphicsQueueThread *mAssetLoadThread;
        GraphicsQueueThread *mSystemProcessThread;

        std::queue<LoadWorkRequest*> mLoadContentQueueu;
        std::queue<UnloadWorkRequest*> mUnloadContentQueueu;
        
        bool mDraw;

        DrawScheme *mDrawScheme;

        AppDriver *mAppDriver;

        Content *mDefaultContent;

    };

}; //namespace S3D

#endif //S3D_APPLICATION_CONTENTAPP_H
