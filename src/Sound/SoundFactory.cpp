

#include "S3D/Sound/SoundFactory.h"

#include "S3D/Sound/WavFileCreator.h"


#if defined OS_ANDROID
#include "S3D/Foundation/Android/AssetSystem.h"
#else
#include "S3D/Foundation/FileIO.h"
#endif


namespace S3D{
	//static
	std::vector<SoundFactory::NamedCreator> SoundFactory::mCreatorArray;

	/****************************************/
	/*!
		@brief	Initialize
		@note

		@author Naoto Nakamura
		@date	Apl. 17, 2009
	*/
	/****************************************/
	void SoundFactory::init()
	{

	}

	/****************************************/
	/*!
		@brief	Cleanup
		@note

		@author Naoto Nakamura
		@date	Apl. 17, 2009
	*/
	/****************************************/
	void SoundFactory::cleanup()
	{
		deleteAllCreator();
	}

	/****************************************/
	/*!
		@brief Register creator
		@note

		@param ext Extension of file path
		@param creator Registered creator

		@author Naoto Nakamura
		@date Apr. 9, 2008
	*/
	/****************************************/
	void SoundFactory::registerCreator(const char *ext, SoundCreator *creator)
	{
		mCreatorArray.push_back(NamedCreator(ext, creator));
	}

	/****************************************/
	/*!
		@brief Unregister creator
		@note

		@param ext Extension of file path

		@author Naoto Nakamura
		@date Apr. 9, 2008
	*/
	/****************************************/
	SoundCreator* SoundFactory::unregisterCreator(const char *ext)
	{
		int numRegist = (int)mCreatorArray.size();

		for(int i = 0 ; i < numRegist ; i++){
			if(!mCreatorArray[i].mName.compare(ext)){
				std::vector<NamedCreator>::iterator ite = mCreatorArray.begin() + i;
				SoundCreator *creator = mCreatorArray[i].mCreator;
				mCreatorArray.erase(ite);
				return creator;
			}
		}
		return NULL;
	}

	/****************************************/
	/*!
		@brief Delete all registered creator
		@note

		@author Naoto Nakamura
		@date Apr. 9, 2008
	*/
	/****************************************/
	void SoundFactory::deleteAllCreator()
	{
		int numRegist = (int)mCreatorArray.size();

		for(int i = 0 ; i < numRegist ; i++){
			std::vector<NamedCreator>::iterator ite = mCreatorArray.begin();
			if(ite == mCreatorArray.end())break;

			SoundCreator *creator = mCreatorArray[0].mCreator;
			mCreatorArray.erase(ite);
			SAFE_DELETE(creator);
		}
	}

	/****************************************/
	/*!
		@brief	Create sound data
		@note	In create process, the appropriate
				registered creator is selected
				according to extension of filepath

		@param group Builded object group instance
		@param path File path
		@return if processing is valid, return true,
				or return false

		@author Naoto Nakamura
		@date Apr. 9, 2008
	*/
	/****************************************/
	SoundFileDescriptor *SoundFactory::createFileDescriptor(const std::string &path, const std::string &ext, Input *input)
	{
		if(input == NULL){
#if defined OS_ANDROID
			input = new AssetInput(path, true);
#else
			input = new FileInput(path, false);
#endif
		}

		int numRegist = (int)mCreatorArray.size();

		SoundFileDescriptor *descriptor = NULL;

		for(int i = 0 ; i < numRegist ; i++){
			if(!mCreatorArray[i].mName.compare(ext)){
				descriptor = mCreatorArray[i].mCreator->createFileDescriptor(input);
				break;
			}
		}

		return descriptor;
	}

	/****************************************/
	/*!
		@brief	Create standard object group
		@note	In create process, the appropriate
				registered creator is selected
				according to extension of filepath

		@param polyDB Polyhedron database set in the creators
		@return NO. created creators

		@author Naoto Nakamura
		@date Apr. 9, 2008
	*/
	/****************************************/
	unsigned int SoundFactory::createStandardCreatorSet()
	{
		unsigned int numCreator = 0;

		SoundCreator *creator = NULL;

		creator = new WavFileCreator();
		registerCreator(BASE_TEXT("wav"),  creator);
		creator = NULL;
		numCreator++;

		return numCreator;

	}

};	// namespace S3D

