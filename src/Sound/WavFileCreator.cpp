

#include "S3D/Sound/WavFileCreator.h"

namespace S3D {

	//////////////////////////////////////////////////////////////////
	//						WavFileDescriptor						//
	//////////////////////////////////////////////////////////////////
	/*************************************************/
	/*!
	@brief		Load sound data from file

	@param		data Data buffer
	@param		size Data size you want to read
	@return	Read data size

	@author	Naoto Nakamura
	@date		Dec. 11, 2009
	*/
	/*************************************************/
	size_t WavFileDescriptor::load(void *data, const size_t size)
	{
		size_t retSize = mInput->read((char*)data, size);
		mCurrentSample += (unsigned int)(retSize / mDataFormat.mChannelsPerSample / mDataFormat.mBytesPerSample);

		return retSize;
	}

	/*************************************************/
	/*!
	@brief		Seek reading position in sound file

	@param		pos Reading position
	@return	If processing is done validly,
	return true, else return false

	@author	Naoto Nakamura
	@date		Dec. 11, 2009
	*/
	/*************************************************/
	bool WavFileDescriptor::seek(unsigned int pos)
	{
		unsigned long diff = (pos - mCurrentSample) * mDataFormat.mChannelsPerSample * mDataFormat.mBytesPerSample;
		mInput->seek(diff, std::ios::cur);
		return TRUE;
	}

	/*************************************************/
	/*!
	@brief		Close file descriptor

	@return	If processing is done validly,
	return true, else return false

	@author	Naoto Nakamura
	@date		Dec. 11, 2009
	*/
	/*************************************************/
	bool WavFileDescriptor::close()
	{
		mInput->close();
		SAFE_DELETE(mInput);
		mCurrentSample = 0;
		return TRUE;
	}


	//////////////////////////////////////////////////////////////////
	//						WavFileCreator							//
	//////////////////////////////////////////////////////////////////
	/*************************************************/
	/*!
	@brief		Get file descriptor from file

	@param		filePath File path
	@param		fd Achieved file descriptor
	@return	If processing is done validly,
	return FR_SUCCESS, else return FR_FAIL_TO_READ

	@author	Naoto Nakamura
	@date		Dec. 11, 2009
	*/
	/*************************************************/
	SoundFileDescriptor *WavFileCreator::createFileDescriptor(Input *input)
	{
		input->open();

		if (!input->isOpened()) { input->close(); return NULL; }

		int bufInt = 0;
		char bufString[5] = { 0, 0, 0, 0, '\0' };

		input->read(bufString, sizeof(char) * 4); //"RIFF"

		input->read((char*)&bufInt, sizeof(char) * 4); //file size

		input->read(bufString, sizeof(char) * 4); //"WAVE"
		input->read(bufString, sizeof(char) * 4); //"fmt "

		int byteOfFmtChunk = 0;

		input->read((char*)&byteOfFmtChunk, sizeof(char) * 4); //16:Linear PCM

		short formatID = 0;
		input->read((char*)&formatID, sizeof(char) * 2); //format ID, PCM:1(01 00)

																//Only lenear PCM is supported
		if (formatID != 1) { input->close(); return NULL; }

		short numChannel = 0;
		input->read((char*)&numChannel, sizeof(char) * 2); //Num of chnnel monaural:1(01 00) stereo:2(02 00)

		int samplingRate = 0;
		input->read((char*)&samplingRate, sizeof(char) * 4); //sampling rate. ex.44100(44 AC 00 00)

		int bytePerSec = 0;
		input->read((char*)&bytePerSec, sizeof(char) * 4); //byte per sec

		short blockSize = 0;
		input->read((char*)&blockSize, sizeof(char) * 2); //byte/sample?~channel

		short bitsPerSample = 0;
		input->read((char*)&bitsPerSample, sizeof(char) * 2); //bits per sample. ex.16bit(10 00)

		input->read(bufString, sizeof(char) * 4); //"data"

		int numByte = 0;
		input->read((char*)&numByte, sizeof(char) * 4);//Num of byte of the data

		SoundDataFormat dataFormat;

		dataFormat.mSampleRate = samplingRate;
		dataFormat.mChannelsPerSample = numChannel;
		dataFormat.mBytesPerSample = (bitsPerSample / 8);
		dataFormat.mDataSize = numByte;
		dataFormat.mNumSample = dataFormat.mDataSize / dataFormat.mBytesPerSample / dataFormat.mChannelsPerSample;

		WavFileDescriptor *wfd = new WavFileDescriptor(dataFormat, input);

		return wfd;
	}

}; //namespace S3D

