#ifndef S3D_APPLICATION_APPDRIVER_H
#define S3D_APPLICATION_APPDRIVER_H

#include "S3D/Common.h"

#include "S3D/Application/App.h"


namespace S3D
{
    class GraphicsContext;
    class ContentApp;

    class AppDriver
    {
    public:
        AppDriver(ContentApp *app)
        :mApplication(app)
        {
        }

    public:

        virtual void init(){}
        virtual void cleanup(){}

        virtual bool runningProcessQueue() = 0;
        
        virtual GraphicsContext *createMainContext() = 0;
        virtual void swapBuffers(GraphicsContext *context) = 0;

        virtual bool isCreateSubContextInMainThread() = 0;

        virtual void getDisplayModes(std::vector<DisplayMode> &modes) const = 0;
        virtual void changeDisplayMode(const DisplayMode &mode) = 0;

    protected:
        ContentApp *mApplication;
    };

}; //namespace S3D

#endif //S3D_APPLICATION_APPDRIVER_H
