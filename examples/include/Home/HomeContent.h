#ifndef HOMECONTENT_H
#define HOMECONTENT_H

#include "S3D/Game/Content.h"

class HomeContent : public S3D::Content
{
public:
    HomeContent()
    :S3D::Content()
    {
    }

protected:
    virtual void init();
    virtual void cleanup();

    virtual void load(S3D::GraphicsContext *context);
    virtual void unload(S3D::GraphicsContext *context);

    virtual bool update(float delta);
};


#endif //HOMECONTENT_H
