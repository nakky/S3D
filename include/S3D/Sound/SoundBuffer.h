/******************************************************************/
/*!
	@file  Soundbuffer.h
	@brief Sound buffer class and misc class are defined
	@note
	@todo
	@bug

	@author Naoto Nakamura
	@date   Sep 10, 2009
*/
/******************************************************************/

#ifndef S3D_SOUNDBUFFER_H
#define S3D_SOUNDBUFFER_H

#include "S3D/Sound/SoundDataFormat.h"

#include "S3D/Sound/SoundFileDescriptor.h"

namespace S3D
{

	// implemented
	class AudioFile;

	// required
	class SoundEffector;

	/****************************************/
	/*!
		@class	SoundBuffer
		@brief

		@author	Naoto Nakamura
		@date	Nov. 9, 2009
		*/
	/****************************************/
	class SoundBuffer
	{
		friend class SoundDriver;
		friend class SoundObject;

	private:
		SoundBuffer();

	public:
		SoundBuffer(SoundFileDescriptor *descriptor, SoundEffector *head)
			: mBufferSize(0),
			  mFileDescriptor(descriptor),
			  mIsEndPoint(false),
			  mEffectorHead(head)
		{
		}

	public:
		unsigned int getBufferSize() const { return mBufferSize; }

		SoundDataFormat getDataFormat() const { return mFileDescriptor->getDataFormat(); }
		int getChannelsPerSample() const { return mFileDescriptor->getChannelsPerSample(); }

		virtual void cleanup() { releaseBuffer(); }

		bool allocateBuffer(const unsigned int bufferSize);
		bool releaseBuffer();

		virtual size_t bufferData(size_t startBufferPos, size_t &size);

		bool isEndPoint() const { return mIsEndPoint; }
		void setEndPointFlag(const bool isEndPoint) { mIsEndPoint = isEndPoint; }

		char *getBufferHead() { return mCurrentBufferHead; }

	private:
		char *mInputBuffer;
		unsigned int mBufferSize; //<! Buffer size

		SoundFileDescriptor *mFileDescriptor;
		bool mIsEndPoint;

		SoundEffector *mEffectorHead;

		char *mCurrentBufferHead;
	};

}; // namespace S3D

#endif // S3D_SOUNDBUFFER_H
