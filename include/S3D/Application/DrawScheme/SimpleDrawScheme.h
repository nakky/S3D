#ifndef S3D_APPLICATION_SIMPLEDRAWSCHEME_H
#define S3D_APPLICATION_SIMPLEDRAWSCHEME_H

#include "S3D/Common.h"
#include "S3D/Application/DrawScheme.h"

namespace S3D
{
    class Content;
    class ContentApp;
    class Renderer;
    class RenderList;
    class Entity;

    class SimpleDrawScheme : public DrawScheme
    {
    public:
        SimpleDrawScheme(ContentApp *app)
        :DrawScheme(app)
        {}

        virtual ~SimpleDrawScheme(){}

        virtual bool update();
        virtual void draw();

        bool checkFunction(Entity *entity);
        void updateGeometry(Entity *entity, bool parentIsDirty);

        std::list<RenderList*> mRenderLists;

    protected:
    };

}; //namespace S3D

#endif //S3D_APPLICATION_SIMPLEDRAWSCHEME_H
