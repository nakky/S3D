/******************************************************************/
/*!
	@file	Shader.h
	@brief	Shader class
	@note
	@todo
	@bug	

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_SHADER_H
#define S3D_SHADER_H

#include "S3D/Common.h"

#include "S3D/Foundation/Resource.h"
#include "S3D/Graphics/Math/MathematicsTypes.h"
#include "S3D/Graphics/GeometricNode.h"
#include "S3D/Graphics/Mesh.h"
#include "S3D/Application/GraphicsContext.h"

#include <string>
#include <map>

namespace S3D{
    
    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class Shader;

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	Shader
        @brief	Shader class
        @note	
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class ShaderParameter
    {
    public:
        ShaderParameter(){}
        virtual ~ShaderParameter(){}
    };
    /****************************************/
    /*!
        @class	Shader
        @brief	Shader class
        @note	
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class Shader : public Resource
    {
    public:
        Shader(const char *name)
        :mName(name)
        {
        }

    public:
        virtual void init(){}
        virtual void cleanup(){}

        const char *getName(){ return mName.c_str(); }

        virtual const short getResourceType() { return RESOURCETYPE_SHADER; }

        virtual void setParameterInt(const char *key, const int *val) = 0;
        virtual void setParameterFloat(const char *key, const float *val) = 0;
        virtual void setParameterVector2(const char *key, const Vector2 *val) = 0;
        virtual void setParameterVector3(const char *key, const Vector3 *val) = 0;
        virtual void setParameterVector4(const char *key, const Vector4 *val) = 0;
        virtual void setParameterMatrix33(const char *key, const Matrix33 *val) = 0;
        virtual void setParameterMatrix44(const char *key, const Matrix44 *val) = 0;

        virtual void setViewProjection(const Matrix44 *mat) = 0;
        virtual void setGeometricState(const GeometricState *state) = 0;
        virtual void setMesh(const Mesh *mesh) = 0;

        virtual ShaderParameter *createParameter() = 0;
        virtual void applyParameter(const ShaderParameter *params) = 0;

    protected:
        std::string mName;

    };

};	// namespace S3D

#endif //S3D_SHADER_H
