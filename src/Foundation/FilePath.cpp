
#include "S3D/Foundation/FilePath.h"

#include <stdio.h>
#include <filesystem>

#if defined OS_WINDOWS
#include <windows.h>
#elif defined OS_MACOSX
#include <mach-o/dyld.h>
#endif


namespace S3D{

    //////////////////////////////////////////////////////
    //				Global definition					//
    //////////////////////////////////////////////////////
    namespace{
        /****************************************/
        /*!
            @brief	Delete file name
            @note

            @param	path Focused file path
            @param	separator separator charactor

            @author	Naoto Nakamura
            @date	Mar. 30, 2009
        */
        /****************************************/
        void _deleteName(std::string &path, char separator){
            unsigned int length = (unsigned int)path.length();
            if(length == 0 || path[length - 1] == separator)return;

            for(int pos = (int)length - 1; pos >= 0 ; pos--){
                if(path[pos] == separator){
                    path = path.substr(0, pos + 1);
                    return;
                }else if(pos == 0){
                    path = "";
                    return;
                }
            }
        }

        /****************************************/
        /*!
            @brief	Add Separator to the tail of path
            @note

            @param	path Focused file path
            @param	separator separator charactor

            @author	Naoto Nakamura
            @date	Mar. 30, 2009
        */
        /****************************************/
        bool _addLastSeparator(std::string &path, char separator){
            unsigned int length = (unsigned int)path.length();
            if(length == 0){
                path += separator;
                return TRUE;
            }
            else if(path[length - 1] != separator){
                path += separator;
                return TRUE;
            }
            return FALSE;
        }

        /****************************************/
        /*!
            @brief	Delete Separator to the tail of path
            @note

            @param	path Focused file path
            @param	separator separator charactor

            @author	Naoto Nakamura
            @date	Mar. 30, 2009
        */
        /****************************************/
        bool _deleteLastSeparator(std::string &path, char separator){
            unsigned int length = (unsigned int)path.length();

            if(length == 0) return FALSE;
            else if(path[length - 1] == separator){
                path.reserve(length - 1);
                return TRUE;
            }
            return FALSE;
        }

        /****************************************/
        /*!
            @brief	Delete redundant suffix
            @note

            @param	str Focused string

            @author	Naoto Nakamura
            @date	Mar. 30, 2009
        */
        /****************************************/
        bool _deleteRedundantSuffix(std::string &str){
            bool retVal = FALSE;
            int strlen = (int)str.length();

            for(int i = strlen - 1 ; i > 0 ; i--){
                if(str[i] != 0){
                    if(retVal)str.reserve(i + 1);
                    return retVal;
                }else{
                    retVal = TRUE;
                }
            }
            return FALSE;
        }

        const std::string _getExePath()
        {
            std::string path;
#if defined OS_WINDOWS
            char szModulePath[MAX_PATH];
	        GetModuleFileNameA(NULL, szModulePath, sizeof(szModulePath)/sizeof(szModulePath[0]));
            path = std::string(szModulePath);
#elif defined OS_MACOSX
            uint32_t bufsize = PATH_MAX;
            char buf[PATH_MAX];
            _NSGetExecutablePath(buf, &bufsize);
            path = std::string(buf);
#elif defined OS_LINUX
            path = std::filesystem::canonical("/proc/self/exe");
#endif
            return path;
        }

    };

    //////////////////////////////////////////////////////
    //					FilePath						//
    //////////////////////////////////////////////////////

    /****************************************/
    /*!
        @brief	Constructor
        @note

        @param	absolutePath Base absolute path
        @param	separator separator

        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    FilePath::FilePath(const std::string &path)
            :mPath(path),
            mSeparator('/')
    {
        _deleteRedundantSuffix(mPath);

    }

    /****************************************/
    /*!
        @brief	Get file name
        @note

        @param	name Got file name

        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    const std::string FilePath::getName() const
    {
        std::string name = BASE_TEXT("");
        unsigned int len = length();
        if(len == 0 || mPath[len - 1] == mSeparator) return name;

        for(int pos = (int)len - 1; pos >= 0 ; pos--){
            if(mPath[pos] == mSeparator){
                name = mPath.substr(pos + 1);
                return name;
            }else if(pos == 0){
                name = mPath;
                return name;
            }
        }
    }


    /****************************************/
    /*!
        @brief	Delete name
        @note	Delete file name and mPath is
                modified directory name

        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    void FilePath::deleteName()
    {
        _deleteName(mPath, mSeparator);
    }

    /****************************************/
    /*!
        @brief	Get cuurent directory name
        @note

        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    const std::string FilePath::getDirectoryName() const
    {
        std::string directory = mPath;
        _deleteName(directory, mSeparator);
        return directory;
    }

    /****************************************/
    /*!
        @brief	Get extension
        @note

        @param	ext Achieved extension

        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    const std::string FilePath::getExtension() const
    {
        std::string ext = BASE_TEXT("");
        unsigned int len = length();
        if(len == 0)return ext;

        for(int i = (int)len - 2 ; i >= 0 ; i--){
            if(mPath[i] == '.'){
                ext = mPath.substr(i + 1);
                return ext;
            }
        }
    }

    /****************************************/
    /*!
        @brief	Delete extension
        @note

        @return	if processing is valid, return TRUE,
                or return FALSE

        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    bool FilePath::deleteExtension(){
        unsigned int len = length();
        if(len == 0)return FALSE;

        for(int i = (int)len - 2 ; i >= 0 ; i--){
            if(mPath[i] == BASE_TEXT('.')){
                mPath.reserve(i);
                return TRUE;
            }
        }
        return FALSE;
    }


    /****************************************/
    /*!
        @brief	Change extension
        @note

        @param	ext New extension
        @return	if processing is valid, return TRUE,
                or return FALSE

        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    bool FilePath::changeExtension(const std::string &ext){
        if(!deleteExtension())return FALSE;
        mPath + "." + ext;
        return TRUE;
    };

    const std::string FilePath::getSystemPath() const
    {
        FilePath exePath(_getExePath());
        exePath.deleteName();
        exePath += mPath;
        
        return exePath;
    }
    
};// namespace S3D
