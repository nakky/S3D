

#include "S3D/Foundation/CPU.h"
#include "S3D/Foundation/QueueThreadPool.h"

namespace S3D{

    //////////////////////////////////////////////////////////////////////
    //							MultiQueueThread						//
    //////////////////////////////////////////////////////////////////////
    /****************************************/
    /*!
        @brief	Constructor
        @note

        @author	Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    QueueThreadPool::QueueThreadPool(const int numThread, const unsigned long idleTime, const int priority)
        :mNumThread(numThread),
    mIdleTime(idleTime),
    mPriority(priority)
    {
    }

    /****************************************/
    /*!
        @brief	Initialize
        @note

        @author	Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    void QueueThreadPool::init()
    {
        mRequestContainer = new QueueRequestContainer();
        mRequestContainer->init();
        
        CPU cpu;
        cpu.init();
        int numCore = cpu.getNumCPU();
        
        for(int i = 0 ; i < mNumThread ; i++){
            QueueThread *thread = this->createThread(mRequestContainer, mPriority, i % numCore);
            mThreadArray.push_back(thread);
            thread->init();

            std::string sstream;
            sstream += "thread-" + i;
            thread->setName(sstream);
        }
    }
    
    QueueThread *QueueThreadPool::createThread(RequestContainer *container, const int priority, const int bindCoreIndex)
    {
        return new QueueThread(container, false, mIdleTime, NULL, priority, bindCoreIndex);
    }

    /****************************************/
    /*!
        @brief	Cleanup
        @note

        @author	Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    void QueueThreadPool::cleanup()
    {
        for(int i = 0 ; i < mThreadArray.size() ; i++){
            if(mThreadArray[i] != NULL){
                mThreadArray[i]->cleanup();
                delete mThreadArray[i];
                mThreadArray[i] = NULL;
            }
        }
        
        mRequestContainer->cleanup();
        SAFE_DELETE(mRequestContainer)
    }
    
    void QueueThreadPool::addThread(QueueThread *thread)
    {
        mThreadArray.push_back(thread);
    }

    /****************************************/
    /*!
        @brief	Start the thread
        @note

        @author	Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    void QueueThreadPool::start()
    {
        for(int i = 0 ; i < mThreadArray.size() ; i++){
            mThreadArray[i]->start();
        }
    }

    /****************************************/
    /*!
        @brief	Shut down the thread
        @note

        @author	Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    void QueueThreadPool::shutdown()
    {
        for(int i = 0 ; i < mThreadArray.size() ; i++){
            mThreadArray[i]->shutdown();
        }
    }

    /****************************************/
    /*!
        @brief	Add new request
        @note

        @param	req Added request
        @return	return true if processing is valid,
                else return false

        @author	Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    bool QueueThreadPool::addRequest(WorkRequest *work, const bool resume)
    {
        mRequestContainer->add(work);

        if(resume){
            for(int i = 0 ; i < mThreadArray.size() ; i++){
                mThreadArray[i]->signalAll();
            }
        }
        
        return true;
    }
    
    void QueueThreadPool::signalAll()
    {
        for(int i = 0 ; i < mThreadArray.size() ; i++){
            mThreadArray[i]->signalAll();
        }
    }

    /****************************************/
    /*!
        @brief	Erase contained request
        @note	Object is not deleted,
                only erase from the queue

        @param	req Erased request
        @return	return true if processing is valid,
                else return false

        @author Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    bool QueueThreadPool::eraseRequest(WorkRequest *work)
    {
        bool ret = false;
        for(int i = 0 ; i < mThreadArray.size() ; i++){
            ret = mThreadArray[i]->eraseRequest(work);
            if(ret)break;
        }
        return ret;
    }

    /****************************************/
    /*!
        @brief	Clear all queue.
        @note	In this method, objects	which
                auto delete flag is true are deleted

        @author	Naoto Nakamura
        @date	Sep. 15, 2008
    */
    /****************************************/
    void QueueThreadPool::clearAllRequest()
    {
        for(int i = 0 ; i < mThreadArray.size() ; i++){
            mThreadArray[i]->clearAllRequest();
        }
    }

}; //namespace S3D