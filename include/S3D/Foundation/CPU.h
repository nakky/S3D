/******************************************************************/
/*!
	@file	CPU.h
	@brief	CPU information manager
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_CPU_H
#define S3D_CPU_H

#include "S3D/Common.h"

#include <string>

namespace S3D
{
	//////////////////////////////////////////////////////
	//				forward declarations				//
	//////////////////////////////////////////////////////
	// implemented
	class CPU;

	//////////////////////////////////////////////////////
	//				class declarations					//
	//////////////////////////////////////////////////////
	/****************************************/
	/*!
		@class	CPU
		@brief	CPU class
		@note

		@author	Naoto Nakamura
		@date	Mar. 23, 2009
	*/
	/****************************************/
	class CPU
	{
	public:
		CPU()
			: mNumCPU(0),
			  mNumLogicalCPU(0),
			  mFamily(0),
			  mFPU(false),
			  mVModeExt(false),
			  mConditionalMove(false),
			  mMMX(false),
			  mMMXExt(false),
			  mSSE(false),
			  mSSE2(false),
			  mSSE3(false),
			  mSSSE3(false),
			  mSSE4_1(false),
			  mSSE4_2(false),
			  mAVX(false),
			  mAVX2(false),
			  mHyperThread(false),
			  m3DNow(false),
			  m3DNowExt(false),
			  mAESNI(false),
			  mMultiProsessing(false),
			  mNEON(false)
		{
		}

	public:
		virtual void init();

		void cpuId(const unsigned int infoType, unsigned int &valA, unsigned int &valB, unsigned int &valC, unsigned int &valD);

		void getVenderName(std::string &name) const { name = mVendor; }
		void getBrandName(std::string &name) const { name = mBrand; }

		unsigned int getNumCPU() const { return mNumCPU; }
		unsigned int getNumLogicalCPU() const { return mNumLogicalCPU; }
		unsigned int getFamily() const { return mFamily; }

		bool isFPUEnabled() const { return mFPU; }
		bool isVirtual86ModeExtEnabled() const { return mVModeExt; }
		bool isConditionalMoveEnabled() const { return mConditionalMove; }

		bool isMMXEnabled() const { return mMMX; }
		bool isMMXExtEnabled() const { return mMMXExt; }

		bool isSSEEnabled() const { return mSSE; }
		bool isSSE2Enabled() const { return mSSE2; }
		bool isSSE3Enabled() const { return mSSE3; }
		bool isSSSE3Enabled() const { return mSSE3; }
		bool isSSE4_1Enabled() const { return mSSE4_1; }
		bool isSSE4_2Enabled() const { return mSSE4_2; }

		bool isAVXEnabled() const { return mAVX; }
		bool isAVX2Enabled() const { return mAVX2; }

		bool isHyperThreadEnabled() const { return mHyperThread; }
		bool is3DNowEnabled() const { return m3DNow; }
		bool is3DNowExtEnabled() const { return m3DNowExt; }
		bool isAESNIEnabled() const { return mAESNI; }

		bool isMultiProsessingEnabled() const { return mMultiProsessing; }

		bool isNEONEnabled() const { return mNEON; }

	private:
		std::string mVendor;
		std::string mBrand;
		unsigned int mNumCPU;
		unsigned int mNumLogicalCPU;
		unsigned int mFamily;
		bool mFPU;

		bool mVModeExt;
		bool mConditionalMove;
		bool mMMX;
		bool mMMXExt;
		bool mSSE;
		bool mSSE2;
		bool mSSE3;
		bool mSSSE3;
		bool mSSE4_1;
		bool mSSE4_2;
		bool mAVX;
		bool mAVX2;
		bool mHyperThread;
		bool m3DNow;
		bool m3DNowExt;
		bool mAESNI;
		bool mMultiProsessing;

		bool mNEON;
	};

}; // namespace S3D

#endif // S3D_CPU_H
