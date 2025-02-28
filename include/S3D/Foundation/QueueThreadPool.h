/******************************************************************/
/*!
	@file	ThreadPool.h
	@brief	Thread pool implementation(QueueThreadPool, WorkerThreadPool)
	@note	

	@todo
	@bug

	@author	Naoto Nakamura
	@date	Sep. 15, 2008
*/
/******************************************************************/

#ifndef S3D_THREADPOOL_H
#define S3D_THREADPOOL_H

#include "S3D/Common.h"

#include "S3D/Foundation/QueueThread.h"


namespace S3D{
    //////////////////////////////////////////////////
    //				forward declarations			//
    //////////////////////////////////////////////////
    //implemented

    class QueueThreadPool;

    //////////////////////////////////////////////////
    //				class declarations				//
    //////////////////////////////////////////////////
   
    /****************************************/
    /*!
        @class	ThreadPool
        @brief	Thread pool of QueueThread

        @author	Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    class QueueThreadPool
    {
    public:
        explicit QueueThreadPool(
                                    const int numThread,
                                    const unsigned long idleTime = 0xFFFFFFFF,
                                    const int priority = PRIORITY_NORMAL
                                    );

    public:
        virtual void init();
        virtual void cleanup();
        
        void addThread(QueueThread *thread);

        void start();
        void shutdown();

        bool addRequest(WorkRequest *work, const bool resume = TRUE);
        bool eraseRequest(WorkRequest *work);
        void clearAllRequest();
        
        void signalAll();

    protected:
        virtual QueueThread * createThread(RequestContainer *container, const int priority, const int bindCoreIndex);
        
    protected:
        std::vector<QueueThread*> mThreadArray;	//!< Thread constainer
        
        int mNumThread;
        
        unsigned long mIdleTime;
        
        RequestContainer *mRequestContainer;
        
        int mPriority;
        
    };

    
}; //namespace S3D


#endif //S3D_THREADPOOL_H
