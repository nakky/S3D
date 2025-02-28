/******************************************************************/
/*!
	@file	GLSL3StandardShader.h
	@brief	GLSL Shader class
	@note
	@todo
	@bug	

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_GLSL3DEFAULTSHADER_H
#define S3D_GLSL3DEFAULTSHADER_H

#include "S3D/Common.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3Shader.h"

#include <string>

namespace S3D{
    
    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class GLSL3DefaultShader;

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	GLSL3DefaultShader
        @brief	GLSL Shader class
        @note	
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class GLSL3DefaultShader : public GLSL3Shader
    {
    public:
        GLSL3DefaultShader()
        :GLSL3Shader("Default")
        {
        }

        virtual void init();

        virtual void load(GraphicsContext *context);

        virtual ShaderParameter *createParameter();
        virtual void applyParameter(const ShaderParameter *params);

    };

};	// namespace S3D

#endif //S3D_GLSL3DEFAULTSHADER_H
