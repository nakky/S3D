/******************************************************************/
/*!
	@file	PThreadThreadDriver.h
	@brief
	@note
	@todo
	@bug
 
	@author Naoto Nakamura
	@date Sep. 15, 2010
 */
/******************************************************************/

#ifndef S3D_PTHREAD_PTHREADTHREADDRIVER_H
#define S3D_PTHREAD_PTHREADTHREADDRIVER_H

#include "S3D/Common.h"

#ifdef USE_PTHREAD_INTERFACE

#include "S3D/Foundation/ThreadDriver.h"


namespace S3D{
    //////////////////////////////////////////////////
    //				forward declarations			//
    //////////////////////////////////////////////////
    //implemented
    class PThreadThreadDriver;

    
    //////////////////////////////////////////////////
    //				class declarations				//
    //////////////////////////////////////////////////
    class PThreadThreadDriver : public ThreadDriver
    {
    public:
        PThreadThreadDriver(Thread *thread)
        :ThreadDriver(thread),
         mBindIndex(-1)
        {
        }
        
        virtual ~PThreadThreadDriver(){}
        
    public:
        virtual bool setPriority(int priority);
        
        virtual void startThread(const int bindIndex);
        virtual void cancelThread();

        virtual void shutdownThread();
        
        virtual ResumeStatus join(unsigned long timeupMillSec);
        
    private:
        static void *_staticRun(void *instance);
      
    private:
        
        ThreadHandle mJoinHandle;
        Condition mJoinCondition;

        int mBindIndex;
    };
    
}; //namespace S3D

#endif //USE_PTHREAD_INTERFACE

#endif //STHREAD_PTHREAD_PTHREADTHREADDRIVER_H
