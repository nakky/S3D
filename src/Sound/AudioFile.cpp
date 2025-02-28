
#include "S3D/Sound/AudioFile.h"

#include "S3D/Sound/SoundFileDescriptor.h"
#include "S3D/Sound/SoundFactory.h"


namespace S3D{
	
	//////////////////////////////////////////////////////////////////////
	//							AudioFile								//
	//////////////////////////////////////////////////////////////////////
	void AudioFile::init()
	{
	}

	void AudioFile::cleanup()
	{
		if(mDataHead != NULL){
			SAFE_DELETE_ARRAY(mDataHead);
		}
	}
	
	void AudioFile::load()
	{
		if(mIsCached) cache();
	}
	
	void AudioFile::unload()
	{
		if(mIsCached) uncache();
	}

	void AudioFile::cache()
	{
		SoundFileDescriptor *descriptor = SoundFactory::createFileDescriptor(mFilePath, mExtension, mInput);

		mFormat = descriptor->getDataFormat();
		mDataHead = new char[mFormat.mDataSize];

		descriptor->seek(0);
		descriptor->load(mDataHead, mFormat.mDataSize);
		mDataSize = mFormat.mDataSize;

		descriptor->close();
		SAFE_DELETE(descriptor);
	}
	
	void AudioFile::uncache()
	{
		delete[] mDataHead;
	}

	unsigned int AudioFile::getData(void* buffer, unsigned int pos, unsigned int size)
	{
		int realSize = size;
		if(pos + size > mDataSize)realSize = mDataSize - pos;
		memcpy(buffer, (void*)(mDataHead + pos), realSize);
		return realSize;
	}

	SoundFileDescriptor *AudioFile::createFileDescriptor()
	{
		if(isCached()){
			SoundFileDescriptor *dsc = new MemoryFileDescriptor(mFormat, this);
			return dsc;
		}
		else return SoundFactory::createFileDescriptor(mFilePath, mExtension);
	}


	
};	//namespace S3D

