
#include "S3D/Application/App.h"

#include <string>


namespace S3D
{
    static const double BILLION  = 1000000000.0;

    bool App::init()
    {
        S3D::init();
        return true;
    }

    bool App::cleanup()
    {
        mMainGraphicsContext->cleanup();
        SAFE_DELETE(mMainGraphicsContext);
       
        S3D::cleanup();

        return true;
    }

    int App::run()
    {
        static const double BILLION  = 1000000000.0;

        double prevFrameStart, frameStart, prevUpdateStart, updateStart, drawStart;
        prevUpdateStart = mRenderTimer.getCurrentTime();
        prevFrameStart = prevUpdateStart;
        
        double updateElapsed = 0.0;
        double frameElapsed = 0.0;

        mMainGraphicsContext = createMainContext();
        mMainGraphicsContext->init();
        onCreateContext(mMainGraphicsContext);

        mRunning.store(true);

        while (true) {

            runningProcessQueue();
           
            if(!mRunning.load()) break;

            if(!mIsPaused.load()){
                //Update FPS
                float fps;
                fps = mGraphicsMode.fps;
                if(fps <= 0) fps = 5;
                double interval = 1.0 / (double)fps;

                frameStart = mRenderTimer.getCurrentTime();

                frameElapsed = frameStart - prevFrameStart;
                
                if(frameElapsed > interval){
                    //FixedUpdate
                    fixedUpdate((float)frameElapsed);

                    if(frameElapsed < interval * 2.0){
                        //Update & Draw
                        updateStart = mRenderTimer.getCurrentTime();
                        updateElapsed = updateStart - prevUpdateStart;
                                        
                        prevUpdateStart = updateStart;

                        bool needDrawUpdate = update((float)updateElapsed);

                        bool needDrawGeometryUpdate = geometryUpdate((float)updateElapsed);

                        if(needDrawUpdate | needDrawGeometryUpdate) mNeedDraw = true;
                        
                        if(mNeedDraw){
                            drawStart = mRenderTimer.getCurrentTime();
                            
                            systemDraw();
                        }

                        if(!(needDrawUpdate | needDrawGeometryUpdate)) mNeedDraw = false;
                    }
                    
                    prevFrameStart = frameStart;
                }else{
                    Timer::sleep(0.0001);
                    //LOG("usleep\n");
                }
            }else{
                mPausedStart = mRenderTimer.getCurrentTime();
                double pausedUpdateElapsed = mPausedStart - mPrevPausedStart;
                pausedUpdate((float)pausedUpdateElapsed);
                
                mPrevPausedStart = mPausedStart;
                Timer::sleep(0.01);
            }
        }
        
    }

    void App::pause()
    {
        mIsPaused.store(true);
        mPrevPausedStart = mRenderTimer.getCurrentTime();

        onPaused();
    }

    void App::resume()
    {
        mIsPaused.store(false);
        
        onResumed();
    }
    
    void App::quit()
    {
        mRunning.store(false);
    }


}; //namespace S3D