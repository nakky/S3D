/******************************************************************/
/*!
	@file	ShaderParameters.h
	@brief	Shader Parameters class
	@note
	@todo
	@bug	

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_SHADERPARAMETERS_H
#define S3D_SHADERPARAMETERS_H

#include "S3D/Common.h"

#include "S3D/Graphics/Shader.h"
#include "S3D/Graphics/Texture.h"

namespace S3D{

    //Unlit
    class UnlitColorShaderParameter : public ShaderParameter
    {
    public:
        UnlitColorShaderParameter()
        :ShaderParameter()
        {}
        
        virtual ~UnlitColorShaderParameter(){}

        Color4 color;
    };

    class UnlitTextureShaderParameter : public ShaderParameter
    {
    public:
        UnlitTextureShaderParameter()
        :ShaderParameter()
        {}
        
        virtual ~UnlitTextureShaderParameter(){}

        Color4 color;
        Texture2D *texture;
    };
  
};	// namespace S3D

#endif //S3D_SHADERPARAMETERS_H
