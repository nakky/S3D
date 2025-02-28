/******************************************************************/
/*!
	@file  GraphicsSystem.h
	@brief Manager class is defined
	@note
	@todo
	@bug

	@author Naoto Nakamura
	@date   Sep 17, 2009
*/
/******************************************************************/

#ifndef S3D_GRAPHICSSYSTEM_H
#define S3D_GRAPHICSSYSTEM_H

#include "S3D/Common.h"
#include "S3D/Foundation/CPU.h"

namespace S3D
{

	enum SIMDInstructionType
	{
		SIMD_NONE = 0,
#if defined SIMDARCH_SSE
		SIMD_SSE,
		SIMD_VMX,
		SIMD_VMX128,
#elif defined SIMDARCH_NEON
		SIMD_NEON,
#endif
	};

	//////////////////////////////////////////////////
	//				forward declarations			//
	//////////////////////////////////////////////////
	// implemented
	class GraphicsSystem;

	/****************************************/
	/*!
		@class	SoundSystem
		@brief
		@author	Naoto Nakamura
		@date	Sep 18, 2009
		*/
	/****************************************/
	class GraphicsSystem
	{
	private:
		GraphicsSystem();

	public:
		static void init();
		static void cleanup();

        static void setSIMDInstructionType(const SIMDInstructionType type);

		static SIMDInstructionType getSIMDInstructionType() { return mSIMDInstructionType; }

    protected:
        static CPU mCPU;
		static SIMDInstructionType mSIMDInstructionType;

	};

}; // namespace S3D

#endif // S3D_GRAPHICSSYSTEM_H
