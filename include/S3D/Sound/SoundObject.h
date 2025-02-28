/******************************************************************/
/*!
	@file  BaseSound.h
	@brief Basic sound class is defined
	@note
	@todo
	@bug

	@author Naoto Nakamura
	@date   Sep 10, 2009
*/
/******************************************************************/

#ifndef S3D_BASESOUND_H
#define S3D_BASESOUND_H

#include "S3D/Sound/SoundDataFormat.h"

#include <string>

#include "S3D/Foundation/ResourceDatabase.h"
#include "S3D/Foundation/IO.h"

#include "S3D/Sound/SoundDriver.h"

namespace S3D
{
	class SoundObject;

	enum SoundObjectState
	{
		SOUNDOBJECT_PLAY = 0,
		SOUNDOBJECT_PAUSE,
		SOUNDOBJECT_STOP,
	};

	/****************************************/
	/*!
		@class	SoundObject
		@brief

		@author	Naoto Nakamura
		@date	Nov. 9, 2009
		*/
	/****************************************/
	class SoundObject
	{
		friend class SoundCreator;
		friend class SoundFactory;

	private:
		SoundObject();

	public:
		explicit SoundObject(const unsigned int id);
		virtual ~SoundObject() {}

	public:
		virtual void init();
		virtual void cleanup();

		bool play();
		bool pause();
		bool stop();

		void setRepeat(const bool isRepeat) { mDriver->setRepeat(isRepeat); }
		bool isRepeat() const { return mDriver->isRepeat(); }

		bool setRepeatTime(const unsigned int startMilliSec = 0, const unsigned int endMilliSec = 0)
		{
			return mDriver->setRepeatTime(startMilliSec, endMilliSec);
		}

		SoundObjectState getState() const { return mState; }
		bool isPlaying() const { return mState == SOUNDOBJECT_PLAY; }

		float getVolume() const;
		bool setVolume(const float vol);

		float getPan() const;
		bool setPan(const float pan);

	protected:
		unsigned int mAudioFileID;
		AudioFile *mAudioFile;

		SoundDataFormat mDataFormat;
		SoundFileDescriptor *mFileDescriptor;

		SoundObjectState mState;
		SoundDriver *mDriver;

		SoundEffector *mEffectorHead;
	};

}; // namespace S3D

#endif // S3D_BASESOUND_H
