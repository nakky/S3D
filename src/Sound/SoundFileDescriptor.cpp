


#include "S3D/Foundation/QueueThread.h"

#include "S3D/Sound/SoundBuffer.h"
#include "S3D/Sound/SoundSystem.h"
#include "S3D/Sound/SoundEffector.h"
#include "S3D/Sound/AudioFile.h"

namespace S3D{

    //////////////////////////////////////////////////////////////////////
    //							MemoryFileDescriptor					//
    //////////////////////////////////////////////////////////////////////
    size_t MemoryFileDescriptor::load(void *data, const size_t size)
    {
        unsigned int dataPos = mCurrentSample * mDataFormat.mChannelsPerSample * mDataFormat.mBytesPerSample;
        int realSize = mAudioFile->getData(data, dataPos, (int)size);
        mCurrentSample += realSize / mDataFormat.mChannelsPerSample / mDataFormat.mBytesPerSample;		
        return realSize;
    }

    bool MemoryFileDescriptor::seek(unsigned int pos)
    {
        if(pos > mAudioFile->getDataSize())return FALSE;
        mCurrentSample = pos;
        return TRUE;
    }

	
};	//namespace S3D

