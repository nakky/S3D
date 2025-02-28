/******************************************************************/
/*!
	@file	Shaderlibrary.h
	@brief	Shader Library class
	@note
	@todo
	@bug	

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_SHADERLIBRARY_H
#define S3D_SHADERLIBRARY_H

#include "S3D/Common.h"

#include <map>
#include <string>

namespace S3D{
    
    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class ShaderLibrary;

    //required
    class Shader;

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	ShaderLibrary
        @brief	Shader Library class
        @note	
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class ShaderLibrary
    {
    public:
        ShaderLibrary()
        {
        }

    public:
        static void retisterShader(const char* name, Shader *shader);
        static void unretisterShader(const char* name);

        static Shader *getDefaultShader(){ return mDefaultShader; }
        static Shader *getShader(const char *name);

    private:
        static Shader *mDefaultShader;
        static std::map<std::string, Shader*> mShaderMap;
    };

};	// namespace S3D

#endif //S3D_SHADER_H
