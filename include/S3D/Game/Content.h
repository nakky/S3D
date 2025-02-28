#ifndef S3D_GAME_CONTENT_H
#define S3D_GAME_CONTENT_H

#include "S3D/Common.h"

#include <list>
#include "S3D/Game/RenderList.h"
#include "S3D/Foundation/Lock.h"
#include "S3D/Foundation/ResourceDatabase.h"
#include "S3D/Application/ContentApp.h"
#include "S3D/Application/GraphicsContext.h"

namespace S3D
{
    class GraphicsContext;
    class GraphicsQueueThread;
    class GraphicsWorkRequest;
    class ContentApp;
    class Entity;
    class RenderList;

    class Content
    {
    public:
        Content():
        mContext(NULL),
        mLoadThread(NULL),
        mElapsed(0.0f),
        mApplication(NULL)
        {
        }

    public:
        void setApplication(ContentApp *application)
        { mApplication = application; }

        void setContext(GraphicsContext *context, GraphicsQueueThread *loadThread)
        { mContext = context; mLoadThread = loadThread;}

        virtual void init();
        virtual void cleanup();

        virtual void load(GraphicsContext *loadingContext);
        virtual void postLoad(GraphicsContext *loadingContext){}

        virtual void prepare(){}

        virtual void preUnload(GraphicsContext *loadingContext){}
        virtual void unload(GraphicsContext *loadingContext);

        virtual bool update(float delta);
        virtual void fixedUpdate(float delta);

        void updateFunctions(float delta, Entity *entity);
        bool fixedUpdateFunctions(float delta, Entity *entity);

        Entity *getRootEntity(){ return &mRootEntity;}

        void addResouceDatabase(Resource *resource);

    protected:
        ContentApp *mApplication;

        GraphicsContext *mContext;
        GraphicsQueueThread *mLoadThread;

        float mElapsed;

        Entity mRootEntity;

        std::list<Entity*> mEntityList;

        Mutex mRenderListLocker;

        ResourceDatabase mResourceDB;
    };

}; //namespace S3D

#endif //S3D_GAME_CONTENT_H
