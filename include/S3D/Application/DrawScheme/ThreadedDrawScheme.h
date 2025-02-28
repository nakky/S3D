#ifndef S3D_APPLICATION_THREADEDDRAWSCHEME_H
#define S3D_APPLICATION_THREADEDDRAWSCHEME_H

#include "S3D/Common.h"
#include "S3D/Application/DrawScheme.h"

namespace S3D
{
    class Content;
    class ContentApp;
    class Renderer;
    class RenderList;
    class Entity;

    class PreDrawWorkRequest : public GraphicsWorkRequest
    {
        public:
        PreDrawWorkRequest(ContentApp *app)
        :GraphicsWorkRequest(PRIORITY_HIGH, false),
        mApplication(app)
        {}

        virtual ~PreDrawWorkRequest(){}

        virtual bool work();
        protected:
        ContentApp *mApplication;
    };

    class DrawWorkRequest : public GraphicsWorkRequest
    {
        public:
        DrawWorkRequest(Content *content)
        :GraphicsWorkRequest(PRIORITY_HIGH, false),
        mContent(content)
        {}

        virtual ~DrawWorkRequest(){}

        Content *getContent() { return mContent; }

        virtual bool work();
        protected:
        Content *mContent;
    };

    class PostDrawWorkRequest : public GraphicsWorkRequest
    {
        public:
        PostDrawWorkRequest(ContentApp *app)
        :GraphicsWorkRequest(PRIORITY_HIGH, false),
        mApplication(app)
        {}

        virtual ~PostDrawWorkRequest(){}

        virtual bool work();
        protected:
        ContentApp *mApplication;
    };

    class ThraededDrawScheme : public DrawScheme
    {
    public:
        ThraededDrawScheme(ContentApp *app)
        :DrawScheme(app),
        mThread(NULL)
        {}

        virtual ~ThraededDrawScheme(){}

        virtual void init();
        virtual void cleanup();

        virtual bool update();
        virtual void draw();

    protected:

        GraphicsQueueThread *mThread;

    };



}; //namespace S3D

#endif //S3D_APPLICATION_THREADEDDRAWSCHEME_H
