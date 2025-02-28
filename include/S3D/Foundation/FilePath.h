/******************************************************************/
/*!
	@file	FilePath.h
	@brief	File path processor
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_FILEPATH_H
#define S3D_FILEPATH_H

#include "S3D/Common.h"

#include <string>

namespace S3D{

    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class FilePath;

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	FilePath
        @brief	File path class
        @note
        @author	Naoto Nakamura
        @date	Apl. 1, 2009
        */
    /****************************************/
    class FilePath 
    {
    public:
        FilePath()
        :mSeparator('/')
        {}

        explicit FilePath(const std::string &path);
    public:

        operator std::string &() {return mPath;}
        operator const std::string &() const {return mPath;}

        FilePath& operator = (const std::string &str) {mPath = str; return *this;}
        FilePath& operator += (const std::string &str) {mPath += str; return *this;}

        FilePath& operator = (const char *str) {mPath = str; return *this;}
        FilePath& operator += (const char *str) {mPath += str; return *this;}

    public:
        const std::string getPath() const {return mPath;}

        void setPath(const std::string &path){mPath = path;}

        const std::string getName() const;
        void deleteName();

        const std::string getDirectoryName() const;

        const std::string getExtension() const;

        bool deleteExtension();
        bool changeExtension(const std::string &ext);

        unsigned int length() const {return (unsigned int)mPath.length();}

        const std::string getSystemPath() const;

    private:
        std::string mPath;
        char mSeparator;

    };

};// namespace S3D

#endif //S3D_FILEPATH_H
