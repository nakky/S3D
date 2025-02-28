/******************************************************************/
/*!
	@file	GLSL3UnlitShader.h
	@brief	GLSL Shader class
	@note
	@todo
	@bug	

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_GLSL3UNLITSHADER_H
#define S3D_GLSL3UNLITSHADER_H

#include "S3D/Common.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3Shader.h"

#include <string>

namespace S3D{
    
    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class GLSL3UnlitColorShader;
    class GLSL3UnlitTextureShader;

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	GLSL3UnlitColorShader
        @brief	GLSL Shader class
        @note	
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class GLSL3UnlitColorShader : public GLSL3Shader
    {
    public:
        GLSL3UnlitColorShader()
        :GLSL3Shader("Unlit/Color")
        {
        }

        ~GLSL3UnlitColorShader(){}

        virtual void init();

        virtual void load(GraphicsContext *context);

        virtual ShaderParameter *createParameter();
        virtual void applyParameter(const ShaderParameter *params);
        virtual void setMesh(const Mesh *mesh);

    protected:
        int mLocationColor;

    };

    /****************************************/
    /*!
        @class	GLSL3UnlitTextureShader
        @brief	GLSL Shader class
        @note	
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class GLSL3UnlitTextureShader : public GLSL3Shader
    {
    public:
        GLSL3UnlitTextureShader()
        :GLSL3Shader("Unlit/Texture")
        {
        }

        ~GLSL3UnlitTextureShader(){}

        virtual void init();

        virtual void load(GraphicsContext *context);

        virtual ShaderParameter *createParameter();
        virtual void applyParameter(const ShaderParameter *params);
        virtual void setMesh(const Mesh *mesh);

    protected:
        int mLocationColor;
        int mLocationAlbedo;

    };

};	// namespace S3D

#endif //S3D_GLSL3UNLITSHADER_H
