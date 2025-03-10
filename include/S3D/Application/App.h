#ifndef S3D_APPLICATION_APP_H
#define S3D_APPLICATION_APP_H

#include "S3D/Common.h"

#include <vector>
#include <string>
#include <atomic>
#include <map>

#if defined OS_LINUX
#include <unistd.h>
#endif

#include "S3D/Foundation/Timer.h"

#include "S3D/Application/GraphicsContext.h"

namespace S3D
{
    struct DisplayMode
    {
        DisplayMode(const bool fullscreen, const Size2 &res,  int refreshrate = 0)
        :isFullscreen(fullscreen),
        resolution(res),
        refreshRate(refreshrate)
        {
        }

        bool isFullscreen;
        Size2 resolution;
        int refreshRate;
        
    };

    struct GraphicsMode
    {
        GraphicsMode(bool vsync, float flamePerSec)
        :vSync(vsync),
        fps(flamePerSec)
        {
        }

        bool vSync;
        float fps;
    };

    class App
    {
    public:
        App(int argc, char *argv[], const DisplayMode &dispMode, const GraphicsMode &grapMode)
        :mRunning(true),
        mArgc(argc),
        mArgv(argv),
        mIsPaused(false),
        mNeedDraw(true),
        mDisplayMode(dispMode),
        mGraphicsMode(grapMode),
        mRenderTimestamp(0.0)
        {
        }

        virtual bool init();
        virtual bool cleanup();

        int run();

        virtual void runningProcessQueue() = 0;

        virtual GraphicsContext *createMainContext() = 0;
        virtual void onCreateContext(GraphicsContext *context){}

        GraphicsContext *getMainGraphicsContext() { return mMainGraphicsContext; }

        virtual bool update(float delta) = 0;
        virtual void fixedUpdate(float delta) = 0;

        virtual void swapBuffers(GraphicsContext *contet) = 0;

        virtual bool geometryUpdate(float delta) = 0;
        virtual void systemDraw() = 0;

        virtual void pausedUpdate(float delta){}

        const DisplayMode *getDisplayMode() const { return &mDisplayMode; }

        virtual void getDisplayModes(std::vector<DisplayMode> &modes) const = 0;

        virtual void setDisplayMode(const DisplayMode &mode) { 
            mDisplayMode = mode; 
            changeDisplayMode(mode);
        }

        virtual void changeDisplayMode(const DisplayMode &mode) = 0;

        const GraphicsMode *getGraphicsMode() const { return &mGraphicsMode; }
        virtual void setGraphicsMode(const GraphicsMode &mode) { 
            mGraphicsMode = mode; 
        }

        bool isPaused(){ return mIsPaused.load(); }

        virtual void pause();
        virtual void resume();
        virtual void quit();

        virtual void onPaused(){}
        virtual void onResumed(){}

    protected:
    protected:
        int mArgc;
        char **mArgv;

        std::atomic<bool> mRunning;

        std::atomic<bool> mIsPaused;
        double mPrevPausedStart, mPausedStart;

        bool mNeedDraw;
        Timer mRenderTimer;
        double mRenderTimestamp;

        DisplayMode mDisplayMode;
        GraphicsMode mGraphicsMode;

        GraphicsContext *mMainGraphicsContext;
    };

}; //namespace S3D

#endif //S3D_APPLICATION_APP_H
