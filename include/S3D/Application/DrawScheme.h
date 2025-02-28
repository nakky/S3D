#ifndef S3D_APPLICATION_DRAWSCHEME_H
#define S3D_APPLICATION_DRAWSCHEME_H

#include "S3D/Common.h"
#include "S3D/Application/App.h"
#include "S3D/Application/GraphicsQueueThread.h"

#include <queue>
#include <list>

namespace S3D
{
    class Content;
    class ContentApp;
    class Renderer;
    class RenderList;
    class Entity;

    class DrawScheme
    {
    public:
        DrawScheme(ContentApp *app)
        :mApplication(app)
        {}

        virtual ~DrawScheme(){}

        virtual void init();
        virtual void cleanup();

        virtual bool update() = 0;
        virtual void draw() = 0;

        ContentApp *getApplication() { return mApplication; }

        protected:
        ContentApp *mApplication;

        Renderer *mRenderer;
    };

}; //namespace S3D

#endif //S3D_APPLICATION_DRAWSCHEME_H
