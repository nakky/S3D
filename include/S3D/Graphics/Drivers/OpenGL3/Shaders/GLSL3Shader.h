/******************************************************************/
/*!
	@file	GLSL3Shader.h
	@brief	GLSL3 Shader class
	@note
	@todo
	@bug	

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_GLSL3SHADER_H
#define S3D_GLSL3SHADER_H

#include "S3D/Common.h"

#include "S3D/Graphics/Shader.h"

#include <string>

namespace S3D{
    
    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class GLSLShader;
    
    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	GLSLShader
        @brief	GLSL Shader class
        @note	
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class GLSL3Shader : public Shader
    {
    public:
        GLSL3Shader(const char *name)
        :Shader(name),
        mProgramId(0),
        mVertexShaderId(0),
        mGeometryShaderId(0),
        mFragmentShaderId(0)
        {
        }

        virtual void load(GraphicsContext *context);
        virtual void unload(GraphicsContext *context);

        virtual void setParameterInt(const char *key, const int *val);
        virtual void setParameterFloat(const char *key, const float *val);
        virtual void setParameterVector2(const char *key, const Vector2 *val);
        virtual void setParameterVector3(const char *key, const Vector3 *val);
        virtual void setParameterVector4(const char *key, const Vector4 *val);
        virtual void setParameterMatrix33(const char *key, const Matrix33 *val);
        virtual void setParameterMatrix44(const char *key, const Matrix44 *val);

        virtual void setViewProjection(const Matrix44 *mat);
        virtual void setGeometricState(const GeometricState *state);
        virtual void setMesh(const Mesh *mesh);

        unsigned int getProgramId() const { return mProgramId; }

    protected:
        std::string mVertexShader;
        std::string mGeometryShader;
        std::string mFragmentShader;

        unsigned int mProgramId;
        unsigned int mVertexShaderId;
        unsigned int mGeometryShaderId;
        unsigned int mFragmentShaderId;

        int mLocationViewProjection;
        int mLocationTrans;
        int mLocationRot;
        int mLocationScl;

        int mLocationPosition;
        int mLocationNormal;
        int mLocationUv;

    };

};	// namespace S3D

#endif //S3D_GLSL3SHADER_H
