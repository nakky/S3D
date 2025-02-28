/******************************************************************/
/*!
	@file  SoundSystem.h
	@brief Manager class is defined
	@note
	@todo
	@bug

	@author Naoto Nakamura
	@date   Sep 17, 2009
*/
/******************************************************************/

#ifndef S3D_SOUNDSYSTEM_H
#define S3D_SOUNDSYSTEM_H

#include "S3D/Sound/SoundDataFormat.h"

#include "S3D/Sound/SoundObject.h"

#include "S3D/Foundation/IO.h"
#include "S3D/Foundation/QueueThread.h"

#ifdef PLAYERAPI_OPENSLES
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES.h>
#endif // PLAYERAPI_OPENSLES

namespace S3D
{

	//////////////////////////////////////////////////
	//				forward declarations			//
	//////////////////////////////////////////////////
	// implemented
	class SoundSystem;

	// required
	class Sound;

	/****************************************/
	/*!
		@class	SoundSystem
		@brief
		@author	Naoto Nakamura
		@date	Sep 18, 2009
		*/
	/****************************************/
	class SoundSystem
	{
		friend class Sound;
		friend class BufferingSound;

	private:
		SoundSystem();

	public:
		static void init();
		static void cleanup();

	private:
#if defined PLAYERAPI_OPENSLES
		static SLObjectItf mEngine;
		static SLEngineItf mEngineInterface;
#endif

	public:

#if defined PLAYERAPI_OPENSLES
		static SLEngineItf getEngineInterface() { return mEngineInterface; }
#endif
	};

}; // namespace S3D

#endif // S3D_SOUNDSYSTEM_H
