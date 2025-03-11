/******************************************************************/
/*!
	@file  MMEDriver.h
	@brief MultiMediaExtention driver class is defined
	@note
	@todo
	@bug

	@author Naoto Nakamura
	@date   Sep 10, 2009
*/
/******************************************************************/

#ifndef S3D_MMEDRIVER_H
#define S3D_MMEDRIVER_H


#include "S3D/Common.h"

#include "S3D/Foundation/Lock.h"
#include "S3D/Foundation/QueueThread.h"

#include "S3D/Sound/SoundDriver.h"

#ifdef PLAYERAPI_MME

namespace S3D{

	class MMEDriver;

		/****************************************/
	/*!
		@class	Sound write request
		@brief

		@author	Naoto Nakamura
		@date	Nov. 9, 2009
		*/
	/****************************************/
	class MMESoundQueue : public WorkRequest
	{

	public:
		MMESoundQueue(MMEDriver *driver, int bufferIndex)
			:WorkRequest(PRIORITY_NORMAL, false),
			mDriver(driver),
			mBufferIndex(bufferIndex)
		{}

	protected:
		virtual bool work();

	public:


	private:
		MMEDriver *mDriver;
		int mBufferIndex;
	};

	/****************************************/
	/*!
		@class MMEDriver
		@brief 

		@author Naoto Nakamura
		@date Dec. 10, 2008
		*/
	/****************************************/
	class MMEDriver : public SoundDriver
	{
	public:
		MMEDriver(SoundEffector *head, SoundFileDescriptor *fd)
			:SoundDriver(head, fd),
			mIsEnabled(false),
			mIsRepeat(false)
		{}

		virtual bool open();
		virtual void close();

		virtual void play();
		virtual void pause();
		virtual void stop();

		virtual bool isEnabled();

		virtual bool isRepeat(){ return mIsRepeat; }
		virtual void setRepeat(bool repeat) { mIsRepeat = repeat; }


		virtual float getVolume();
		virtual bool setVolume(const float vol);

		virtual float getPan();
		virtual bool setPan(const float pan);


		void threadBuffering(unsigned int bIndex);
	
	private:
		static void CALLBACK callback(
			HWAVEOUT hwo,
			UINT uMsg,
			DWORD_PTR inUserData,
			DWORD_PTR buffer,
			DWORD_PTR dwParam2);

		void setEnabled(bool enabled);

		void resetWithBufferring();

	private:		
		bool mIsEnabled;
		bool mIsRepeat;

		QueueThread mQueueThread;
		Mutex mLock;

		HWAVEOUT mWaveOut;
		LPWAVEHDR mWaveHDR[STREAMING_NUM_BUFFER];

		MMESoundQueue *mQueue[STREAMING_NUM_BUFFER];

	};

};	//namespace S3D

#endif //PLAYERAPI_MME

#endif // S3D_MMEDRIVER_H
