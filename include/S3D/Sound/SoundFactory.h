/******************************************************************/
/*!
	@file	Object3DGroupFactory.h
	@brief	Object3DGroup factory class(creator container)
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Apl. 17, 2009
*/
/******************************************************************/

#ifndef S3D_SOUNDFACTORY_H
#define S3D_SOUNDFACTORY_H

#include "S3D/Sound/SoundDataFormat.h"
#include "S3D/Sound/SoundObject.h"

#include <vector>

namespace S3D
{
	//////////////////////////////////////////////////////
	//				forward declarations				//
	//////////////////////////////////////////////////////
	// implemented
	class SoundFactory;
	class SoundCreator;

	//////////////////////////////////////////////////////
	//				class declarations					//
	//////////////////////////////////////////////////////

	/****************************************/
	/*!
		@class	SoundFactory
		@brief	Factory class which is creator conatainer
		@note

		@author	Naoto Nakamura
		@date	Apl. 17, 2009
	*/
	/******************************************/
	class SoundFactory
	{
	private:
		SoundFactory();

	public:
		class NamedCreator
		{
		public:
			NamedCreator()
				: mCreator(NULL)
			{
			}

		public:
			NamedCreator(const char *name, SoundCreator *creator)
				: mName(name),
				  mCreator(creator) {}

			std::string mName;
			SoundCreator *mCreator;
		};

	public:
		static void init();
		static void cleanup();

		static void registerCreator(const char *ext, SoundCreator *creator);
		static SoundCreator *unregisterCreator(const char *ext);
		static void deleteAllCreator();

		static unsigned int createStandardCreatorSet();

		static SoundFileDescriptor *createFileDescriptor(const std::string &path, const std::string &ext, Input *input = NULL);

	private:
		static std::vector<NamedCreator> mCreatorArray;
	};

	/****************************************/
	/*!
		@class SoundCreator
		@brief 3D object group creator (abstract)
		@note

		@author Naoto Nakamura
		@date	Apl. 17, 2009
	*/
	/******************************************/
	class SoundCreator
	{
	public:
		SoundCreator() {}

	protected:
		void setSoundFileDescriptor(SoundObject &sound, SoundFileDescriptor *sfd) { sound.mFileDescriptor = sfd; }
		void setFileFormat(SoundFileDescriptor &sfd, SoundDataFormat &format) { sfd.mDataFormat = format; }

	public:
		virtual SoundFileDescriptor *createFileDescriptor(Input *input) = 0;
	};

}; // namespace SSound

#endif // S3D_SOUNDFACTORY_H
