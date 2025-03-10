/******************************************************************/
/*!
	@file	Timer.h
	@brief	Classes for managing time schedule
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_TIMER_H
#define S3D_TIMER_H

#include "S3D/Common.h"

#if defined OS_WINDOWS
#include <mmsystem.h>
#elif defined OS_MACOSX || defined OS_IPHONE
#include <CoreFoundation/CoreFoundation.h>
#elif defined OS_LINUX || defined OS_ANDROID
#include <sys/time.h>
#endif

#include <time.h>

namespace S3D{
    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class Timer;

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	Timer
        @brief	Timer class
        @note

        @author	Naoto Nakamura
        @date	Mar. 23, 2009
    */
    /****************************************/
    class Timer
    {
    public:
        Timer()
#if defined OS_WINDOWS
        :mBaseTime(0)
#elif defined OS_MACOSX || defined OS_IPHONE
        :mBaseTime(0.0)
#endif
        {
#if defined OS_WINDOWS
            timeBeginPeriod(1);
#endif
            reset();
        }

        ~Timer(){
#if defined OS_WINDOWS
            timeEndPeriod(1);
#endif
        }
    public:
        inline void reset();
        inline double getElapsedTime();

        inline double getCurrentTime();

        static void sleep(double sec);

    private:
#if defined OS_WINDOWS
        unsigned int mBaseTime;
#elif defined OS_MACOSX || defined OS_IPHONE
        double mBaseTime;
#elif defined OS_LINUX || defined OS_ANDROID
        struct timespec mBaseTime;
        struct timespec mElapsedTime;
#endif

    };

    /****************************************/
    /*!
        @brief	Reset timer
        @note	Reset internal time stump (base time)

        @author	Naoto Nakamura
        @date	Aug. 11, 2009
    */
    /****************************************/
    inline void Timer::reset()
    {
#if defined OS_WINDOWS
        mBaseTime = timeGetTime();
#elif defined OS_MACOSX || defined OS_IPHONE
        mBaseTime = CFAbsoluteTimeGetCurrent();
#elif defined OS_LINUX || defined OS_ANDROID
        clock_gettime(CLOCK_REALTIME, &mBaseTime);
#endif
    }

    /****************************************/
    /*!
        @brief	Get Elapsed time
        @note

        @return	Got time (sec)

        @author	Naoto Nakamura
        @date	Aug. 11, 2009
    */
    /****************************************/
    inline double Timer::getElapsedTime()
    {
#if defined OS_WINDOWS
        return (double)(timeGetTime() - mBaseTime) / 1000.0;
#elif defined OS_MACOSX || defined OS_IPHONE
        return ((CFAbsoluteTimeGetCurrent() - mBaseTime));
#elif defined OS_LINUX || defined OS_ANDROID
        clock_gettime(CLOCK_REALTIME, &mElapsedTime);
        return (double)((mElapsedTime.tv_sec - mBaseTime.tv_sec) % 0xffffff) + (double)(mElapsedTime.tv_usec - mBaseTime.tv_usec) / 1000000000.0;
#endif
    }

    /****************************************/
    /*!
        @brief	Get Current time
        @note

        @return	Got time (sec)

        @author	Naoto Nakamura
        @date	Aug. 11, 2009
    */
    /****************************************/
    inline double Timer::getCurrentTime()
    {
#if defined OS_WINDOWS
        return (double)timeGetTime() / 1000.0;
#elif defined OS_MACOSX || defined OS_IPHONE
        return CFAbsoluteTimeGetCurrent();
#elif defined OS_LINUX || defined OS_ANDROID
        clock_gettime(CLOCK_REALTIME, &mElapsedTime);
        return (double)(mElapsedTime.tv_sec % 0xffffff) + (double)mElapsedTime.tv_usec / 1000000000.0;
#endif
    }


};// namespace S3D


#endif //STHREAD_TIMER_H
