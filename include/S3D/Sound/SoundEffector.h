/******************************************************************/
/*!
	@file  SoundEffector.h
	@brief Sound effector class are defined
	@note
	@todo
	@bug

	@author Naoto Nakamura
	@date   Apl 10, 2011
*/
/******************************************************************/

#ifndef S3D_SOUNDEFFECTOR_H
#define S3D_SOUNDEFFECTOR_H

#include "S3D/Sound/SoundDataFormat.h"

#include "S3D/Sound/SoundBuffer.h"

namespace S3D
{
	class SoundEffector;

	/****************************************/
	/*!
		@class	SoundEffector
		@brief

		@author	Naoto Nakamura
		@date   Apl 10, 2011
	*/
	/****************************************/
	class SoundEffector
	{
		friend class SoundBuffer;
		friend class SoundObject;

	public:
		SoundEffector(const SoundDataFormat &format)
			: mNext(NULL),
			  mFormat(format),
			  mBuffer(NULL)
		{
		}

	public:
		virtual void init();
		virtual void cleanup();

		virtual void enable(const bool isEnabled) { mIsEnable = isEnabled; }
		bool isEnable() const { return mIsEnable; }

	protected:
		virtual void process(char *src, size_t size) = 0;
		virtual void clear() = 0;

		void setNext(SoundEffector *effector) { mNext = effector; }
		SoundEffector *getNext() { return mNext; }

	protected:
		SoundEffector *mNext;

		SoundDataFormat mFormat;
		bool mIsEnable;

		char *mBuffer;
	};

	/****************************************/
	/*!
		@class	VolumePanEffector
		@brief implemented volume and pan effect

		@author	Naoto Nakamura
		@date   Apl 10, 2011
	*/
	/****************************************/
	class VolumePanEffector : public SoundEffector
	{
	public:
		VolumePanEffector(const SoundDataFormat &format)
			: SoundEffector(format),
			  mVolume(1.0f),
			  mPan(0.0f)
		{
		}

	public:
		virtual void init();

		virtual void process(char *src, size_t size);
		virtual void clear() {}

		void setVolume(const float vol)
		{
			mVolume = vol;
			updateFilter();
		}
		void setPan(const float pan)
		{
			mPan = pan;
			updateFilter();
		}

		float getVolume() const { return mVolume; }
		float getPan() const { return mPan; }

		virtual void setVolumePan(const float vol, const float pan)
		{
			mVolume = vol;
			mPan = pan;
			updateFilter();
		}

	private:
		void updateFilter();

	protected:
		float mVolume; //!< 0.0f - 1.0f
		float mPan;	   //!< Left -1.0f - +1.0f Right

		float mFilter[2];
	};

}; // namespace S3D

#endif // S3D_SOUNDEFFECTOR_H
