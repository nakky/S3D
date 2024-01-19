
#include "S3D/CPU.h"

#if defined COMPILER_GCC
#include <unistd.h>

#if defined ARCHTECTURE_IA
#include <cpuid.h>
#endif
#endif

#if defined OS_ANDROID
#include <cpu-features.h>
#elif defined OS_IPHONE
#include <sys/sysctl.h>
#endif

namespace S3D
{

	/****************************************/
	/*!
		@brief	Initialize
		@note	Extruct CPU information

		@author	Naoto Nakamura
		@date	Aug. 11, 2009
	*/
	/****************************************/
	void CPU::init()
	{
#if defined ARCHTECTURE_IA

#if defined COMPILER_MSVC
		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		mNumCPU = systemInfo.dwNumberOfProcessors;
#elif defined COMPILER_GCC
		mNumCPU = (unsigned int)sysconf(_SC_NPROCESSORS_ONLN);
#endif
		if (mNumCPU < 1)
			mNumCPU = 1;

		unsigned int maxInput, maxExtInput, a, b, c, d;
		maxInput = maxExtInput = a = b = c = d = 0;
		char vendor[32] = "";
		char brand[64] = "";

		cpuId(0, maxInput, ((unsigned int *)vendor)[0], ((unsigned int *)vendor)[2], ((unsigned int *)vendor)[1]); // EBX->EDX->ECX

		if (maxInput >= 1)
		{
			cpuId(1, a, b, c, d);

			mFamily = (a >> 8) & 0x0F;
			mNumLogicalCPU = (b >> 16) & 0xFF;

			mFPU = (d & 0x01) != 0;
			mVModeExt = (d & (0x01 << 1)) != 0;
			mConditionalMove = (d & (0x01 << 15)) != 0;

			mMMX = (d & (0x01 << 23)) != 0;

			mSSE = (d & (0x01 << 25)) != 0;
			mSSE2 = (d & (0x01 << 26)) != 0;
			mSSE3 = (c & (0x01 << 0)) != 0;
			mSSSE3 = (c & (0x01 << 9)) != 0;
			mSSE4_1 = (c & (0x01 << 19)) != 0;
			mSSE4_2 = (c & (0x01 << 20)) != 0;

			mAVX = (c & (0x01 << 28)) != 0;

			mAESNI = (c & (0x01 << 25)) != 0;

			mHyperThread = (d & (0x01 << 28)) != 0;

			cpuId(7, a, b, c, d);
			mAVX2 = (b & (0x01 << 5)) != 0;

			cpuId(0x80000000, maxExtInput, b, c, d);

			if (maxExtInput >= 0x80000001)
			{
				cpuId(0x80000001, a, b, c, d);
				m3DNow = (d & (0x01 << 31)) != 0;
				m3DNowExt = (d & (0x01 << 30)) != 0;
				mMMXExt = (d & (0x01 << 22)) != 0;
				mMultiProsessing = (d & (0x01 << 19)) != 0;

				if (maxExtInput >= 0x80000002)
				{
					cpuId(0x80000002, ((unsigned int *)brand)[0], ((unsigned int *)brand)[1], ((unsigned int *)brand)[2], ((unsigned int *)brand)[3]);
					brand[16] = '\0';

					if (maxExtInput >= 0x80000003)
					{

						cpuId(0x80000003, ((unsigned int *)brand)[4], ((unsigned int *)brand)[5], ((unsigned int *)brand)[6], ((unsigned int *)brand)[7]);
						brand[32] = '\0';

						if (maxExtInput >= 0x80000004)
						{

							cpuId(0x80000004, ((unsigned int *)brand)[8], ((unsigned int *)brand)[9], ((unsigned int *)brand)[10], ((unsigned int *)brand)[11]);
							brand[48] = '\0';
						}
					}
				}
			}
		}

		mVendor = vendor;
		mBrand = brand;
#if defined COMPILER_MSVC
		LARGE_INTEGER spf;
		QueryPerformanceFrequency(&spf);
		unsigned int64 freq = (unsigned int64)(spf.QuadPart * 1000);
#elif defined COMPILER_GCC

#endif

#elif defined OS_IPHONE

		size_t len;
		unsigned int ncpu;

		len = sizeof(ncpu);
		sysctlbyname("hw.ncpu", &ncpu, &len, NULL, 0);
		mNumCPU = ncpu;

#if defined __ARM_NEON__
		mNEON = true;
#else
		mNEON = false;
#endif

#elif defined OS_ANDROID

		mFamily = android_getCpuFamily();

		uint64_t features = android_getCpuFeatures();

		if (features & ANDROID_CPU_ARM_FEATURE_NEON)
			mNEON = true;
		else
			mNEON = false;

		mNumCPU = android_getCpuCount();

#endif // ARCHTECTURE_IA
	}

#if defined ARCHTECTURE_IA
	void CPU::cpuId(const unsigned int infoType, unsigned int &valA, unsigned int &valB, unsigned int &valC, unsigned int &valD)
	{
#if defined COMPILER_MSVC

		int p[4];
		__cpuid((int *)p, infoType);
		valA = p[0];
		valB = p[1];
		valC = p[2];
		valD = p[3];
#elif defined COMPILER_GCC
		__cpuid(infoType, valA, valB, valC, valD);
#endif
	}

#endif // ARCHTECTURE_IA

}; // namespace S3D
