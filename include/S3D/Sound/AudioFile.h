/******************************************************************/
/*!
	@file  AudioFile.h
	@brief File descriptor class are defined
	@note
	@todo
	@bug

	@author Naoto Nakamura
	@date   Sep 10, 2009
*/
/******************************************************************/

#ifndef S3D_AUDIOFILE_H
#define S3D_AUDIOFILE_H

#include "S3D/Sound/SoundDataFormat.h"

#include "S3D/Foundation/IO.h"

#include <string>

namespace S3D
{
	// required
	class SoundFileDescriptor;

	/****************************************/
	/*!
		@class AudioFile
		@brief Abstract

		@author Naoto Nakamura
		@date Dec. 10, 2008
		*/
	/****************************************/
	class AudioFile : public Resource
	{
	public:
		AudioFile(const std::string &path, const std::string &ext, const bool cache, Input *input)
			: Resource(),
			  mFilePath(path),
			  mExtension(ext),
			  mDataHead(NULL),
			  mIsCached(cache),
			  mDataSize(0)
		{
		}

	public:
		virtual void init();
		virtual void cleanup();

		virtual void load();
		virtual void unload();

		unsigned int getData(void *buffer, unsigned int pos, unsigned int size);

		unsigned int getDataSize() const { return mDataSize; }
		void cache();
		void uncache();

		bool isCached() const { return mIsCached; }

		SoundFileDescriptor *createFileDescriptor();

	private:
		std::string mFilePath;
		std::string mExtension;
		Input *mInput;

		char *mDataHead;
		bool mIsCached;
		unsigned int mDataSize;
		SoundDataFormat mFormat;
	};

}; // namespace S3D

#endif // S3D_AUDIOFILE_H
