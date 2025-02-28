/******************************************************************/
/*!
	@file  CoreAudioDriver.h
	@brief CoreAudio driver class is defined
	@note
	@todo
	@bug

	@author Naoto Nakamura
	@date   Sep 10, 2009
*/
/******************************************************************/

#ifndef S3D_OPENSLESDRIVER_H
#define S3D_OPENSLESDRIVER_H


#include "S3D/SoundCommon.h"

#include "VS/Foundation/Lock.h"
#include "VS/Foundation/QueueThread.h"

#include <queue>

#ifdef OS_ANDROID
#include <SLES/OpenSLES_Android.h>
#endif //OS_ANDROID

#ifdef PLAYERAPI_OPENSLES
#include <SLES/OpenSLES.h>
#endif //PLAYERAPI_OPENSLES


#include "S3D/SoundDriver.h"


namespace VS{
	namespace Sound{

		class OpenSLESDriver;

		 /****************************************/
		/*!
		 @class	Sound write request
		 @brief

		 @author	Naoto Nakamura
		 @date	Nov. 9, 2009
		 */
		/****************************************/
        class OpenSLES3DRequest : public WorkRequest
		{
        public:
            OpenSLES3DRequest(OpenSLESDriver *driver, int bufferIndex)
				:WorkRequest(PRIORITY_NORMAL, false),
				mDriver(driver),
				mBufferIndex(bufferIndex)
			{}

        protected:
            virtual bool work();

        private:
            OpenSLESDriver *mDriver;
			int mBufferIndex;
		};

		/****************************************/
		/*!
		 @class OpenSLESDriver
		 @brief 

		 @author Naoto Nakamura
		 @date Dec. 10, 2008
		 */
		/****************************************/
		class OpenSLESDriver : public SoundDriver
		{
		public:
			OpenSLESDriver(SoundEffector *head, SoundFileDescriptor *fd)
				:SoundDriver(head, fd),
				mIsEnabled(false),
				mIsRepeat(false),
				 mCurrentBuffer(0)
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
            static void callback(SLAndroidSimpleBufferQueueItf bq, void *context);

            void setEnabled(bool enabled);

			void resetWithBufferring();

		private:		
			bool mIsEnabled;
			bool mIsRepeat;

			QueueThread mQueueThread;
			Mutex mLock;

            SLObjectItf mOutputMixObject;
            SLEnvironmentalReverbItf mOutputMixEnvironmentalReverb;
            
            SLObjectItf mPlayerObject;
            SLPlayItf mPlayerInterface;
            SLAndroidSimpleBufferQueueItf mPlayerBufferQueue;
            
            SLEffectSendItf mPlayerEffectSendInterface;
            SLVolumeItf mPlayerVolumeInterface;
            SLPlaybackRateItf mPlaybackRateInterface;
            
            SLpermille mMinPlaybackRate;
            SLpermille mMaxPlaybackRate;
            SLpermille mPlaybackRateStepSize;

            OpenSLES3DRequest *mQueue[STREAMING_NUM_BUFFER];

			int mCurrentBuffer;

            std::queue<int> mBufferQueue;
		};


	};	//namespace Sound
};	//namespace VS


#endif // S3D_OPENSLESDRIVER_H
