#ifndef EXAMPLEAPP_H
#define EXAMPLEAPP_H

#include "S3D/Application/ContentApp.h"

class ExampleApp : public S3D::ContentApp
{
public:
    ExampleApp(int argc, char *argv[], S3D::Content* defaultContent, const S3D::DisplayMode &dispMode, const S3D::GraphicsMode &grapMode)
        : S3D::ContentApp(argc, argv, defaultContent, dispMode, grapMode)
    {
    }

    virtual ~ExampleApp() {}

private:
};

#endif // EXAMPLEAPP_H
