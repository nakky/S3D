/******************************************************************/
/*!
 @file	WavReader.h
 @brief	Wave file reader class definition
 @note
 @todo
 @bug

 @author	Naoto Nakamura
 @date   Dec. 11, 2009
 */
/******************************************************************/
#ifndef S3D_WAVFILECREATOR_H
#define S3D_WAVFILECREATOR_H

#include "S3D/Sound/SoundDataFormat.h"
#include "S3D/Sound/SoundFileDescriptor.h"
#include "S3D/Sound/SoundFactory.h"

#include "S3D/Foundation/IO.h"

#include <fstream>

namespace S3D
{

	//////////////////////////////////////////////////
	//				forward declarations			//
	//////////////////////////////////////////////////
	// defined class
	class WavFileDescriptor;
	class WavCreator;

	// required class
	//////////////////////////////////////////////////
	//				class declarations				//
	//////////////////////////////////////////////////

	/****************************************/
	/*!
		@class	 WavFileDescriptor
		@brief	 Wave file descriptor class
		@author	Naoto Nakamura
		@date	Dec. 11, 2009
		*/
	/****************************************/
	class WavFileDescriptor : public SoundFileDescriptor
	{
		friend class WavFileCreator;

	public:
		WavFileDescriptor(SoundDataFormat &format, Input *input)
			: SoundFileDescriptor(format),
			  mCurrentSample(0),
			  mInput(input)
		{
		}

		virtual unsigned int getCurrentSample() const { return mCurrentSample; }

		virtual size_t load(void *data, const size_t size);
		virtual bool seek(unsigned int pos);
		virtual bool close();

	private:
		Input *mInput;
		unsigned int mCurrentSample;
	};

	/****************************************/
	/*!
		@class	 WavFileCreator
		@brief	 Wave file creator class
		@author	Naoto Nakamura
		@date	Dec. 11, 2009
		*/
	/****************************************/
	class WavFileCreator : public SoundCreator
	{
	public:
		// constructor
		explicit WavFileCreator() : SoundCreator() {}

		// read
		virtual SoundFileDescriptor *createFileDescriptor(Input *input);
	};

}; // namespace S3D

#endif // S3D_WAVFILECREATOR_H
