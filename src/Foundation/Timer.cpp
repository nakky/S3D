

#include "S3D/Foundation/Timer.h"

namespace S3D{
    /****************************************/
    /*!
        @brief	Sleep
        @note

        @param	sec sleep time (sec.)

        @author	Naoto Nakamura
        @date	Aug. 11, 2009
    */
    /****************************************/
    void Timer::sleep(double sec)
    {
#if defined COMPILER_MSVC
        timeBeginPeriod(1);
        Sleep((unsigned int)(sec * 1000.0));
        timeEndPeriod(1);
#elif defined COMPILER_GCC
        struct timespec time;
        time.tv_sec = (unsigned int)sec;
        time.tv_nsec = ((unsigned int)(sec * 1000.0f) % 1000) * 1000000L;
        nanosleep(&time, NULL);
#endif

    }

};	// namespace S3D
