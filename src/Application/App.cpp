
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

        struct timespec prevFrameStart, frameStart, prevUpdateStart, updateStart, drawStart;
        clock_gettime(CLOCK_REALTIME, &prevUpdateStart);
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

                clock_gettime(CLOCK_REALTIME, &frameStart);

                frameElapsed = (frameStart.tv_sec - prevFrameStart.tv_sec) +
                                (frameStart.tv_nsec - prevFrameStart.tv_nsec) / BILLION;
                
                if(frameElapsed > interval){
                    //FixedUpdate
                    fixedUpdate((float)frameElapsed);

                    if(frameElapsed < interval * 2.0){
                        //Update & Draw
                        clock_gettime(CLOCK_REALTIME, &updateStart);
                        updateElapsed = (updateStart.tv_sec - prevUpdateStart.tv_sec) +
                                        (updateStart.tv_nsec - prevUpdateStart.tv_nsec) / BILLION;
                                        
                        prevUpdateStart = updateStart;

                        bool needDrawUpdate = update((float)updateElapsed);

                        bool needDrawGeometryUpdate = geometryUpdate((float)updateElapsed);

                        if(needDrawUpdate | needDrawGeometryUpdate) mNeedDraw = true;
                        
                        if(mNeedDraw){
                            clock_gettime(CLOCK_REALTIME, &drawStart);
                            
                            systemDraw();
                        }

                        if(!(needDrawUpdate | needDrawGeometryUpdate)) mNeedDraw = false;
                    }
                    
                    prevFrameStart = frameStart;
                }else{
                    usleep(1000);
                    //LOG("usleep\n");
                }
            }else{
                clock_gettime(CLOCK_REALTIME, &mPausedStart);
                double pausedUpdateElapsed = (mPausedStart.tv_sec - mPrevPausedStart.tv_sec) +
                                    (mPausedStart.tv_nsec - mPrevPausedStart.tv_nsec) / BILLION;
                pausedUpdate((float)pausedUpdateElapsed);
                
                mPrevPausedStart = mPausedStart;
                usleep(100000);
            }
        }
        
    }

    void App::pause()
    {
        mIsPaused.store(true);
        clock_gettime(CLOCK_REALTIME, &mPrevPausedStart);

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