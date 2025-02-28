
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3Shader.h"

#include "S3D/Application/GraphicsContext.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.h"


#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D{
    
    void GLSL3Shader::load(GraphicsContext *context)
    {
        context->bind();

        mProgramId = glCreateProgram();

        int length;
        GLint compiled;

        //Vertex
        mVertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        const char *vsource = mVertexShader.c_str();
        length = mVertexShader.length();
        glShaderSource(mVertexShaderId, 1, &vsource, &length);

        glCompileShader(mVertexShaderId);
        glGetShaderiv(mVertexShaderId, GL_COMPILE_STATUS, &compiled);

        if (compiled == GL_FALSE) {
            context->release();

            GLint maxLength = 0;
            glGetShaderiv(mVertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);
            GLchar *errorLog =(GLchar *)malloc(maxLength);
            glGetShaderInfoLog(mVertexShaderId, maxLength, &maxLength, errorLog);
            printf("vert shader error:(%s)%s\n", mName.c_str(), errorLog);
            free(errorLog);

            return;
        }
        mVertexShader.clear();

        glAttachShader(mProgramId, mVertexShaderId);

        //Fragment
        mFragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        const char *fsource = mFragmentShader.c_str();
        length = mFragmentShader.length();
        glShaderSource(mFragmentShaderId, 1, &fsource, &length);

        glCompileShader(mFragmentShaderId);
        glGetShaderiv(mFragmentShaderId, GL_COMPILE_STATUS, &compiled);

        if (compiled == GL_FALSE) {
            context->release();

            GLint maxLength = 0;
            glGetShaderiv(mFragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);
            GLchar *errorLog =(GLchar *)malloc(maxLength);
            glGetShaderInfoLog(mFragmentShaderId, maxLength, &maxLength, &errorLog[0]);
            printf("frag shader error:(%s)%s\n", mName.c_str(), errorLog);
            free(errorLog);

            return;
        }
        mFragmentShader.clear();

        glAttachShader(mProgramId, mFragmentShaderId);

        //Geometry
        if(mGeometryShader.length() > 0){
            mGeometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);
            const char *gsource = mGeometryShader.c_str();
            length = mGeometryShader.length();
            glShaderSource(mGeometryShaderId, 1, &gsource, &length);

            glCompileShader(mGeometryShaderId);
            glGetShaderiv(mGeometryShaderId, GL_COMPILE_STATUS, &compiled);

            if (compiled == GL_FALSE) {
                context->release();

                GLint maxLength = 0;
                glGetShaderiv(mGeometryShaderId, GL_INFO_LOG_LENGTH, &maxLength);
                GLchar *errorLog =(GLchar *)malloc(maxLength);
                glGetShaderInfoLog(mGeometryShaderId, maxLength, &maxLength, errorLog);
                printf("geo shader error:(%s)%s\n", mName.c_str(), errorLog);
                free(errorLog);
                
                return;
            }
            mGeometryShader.clear();

            glAttachShader(mProgramId, mGeometryShaderId);
        }

        glLinkProgram(mProgramId);

        mLocationViewProjection = glGetUniformLocation(mProgramId, "_projection");
        mLocationTrans = glGetUniformLocation(mProgramId, "_trans");
        mLocationRot = glGetUniformLocation(mProgramId, "_rot");
        mLocationScl = glGetUniformLocation(mProgramId, "_scl");

        mLocationPosition = glGetAttribLocation(mProgramId, "_position");
        mLocationNormal = glGetAttribLocation(mProgramId, "_normal");
        mLocationUv = glGetAttribLocation(mProgramId, "_uv");

        context->release();

    }

    void GLSL3Shader::unload(GraphicsContext *context)
    {
        context->bind();

        glDeleteShader(mVertexShaderId);
        glDeleteShader(mFragmentShaderId);
        if(mGeometryShaderId != 0) glDeleteShader(mGeometryShaderId);

        glDeleteProgram(mProgramId);
     
        context->release();
    }

    void GLSL3Shader::setParameterInt(const char *key, const int *val)
    {
        glUniform1i(glGetUniformLocation(mProgramId, key), *val);
    }

    void GLSL3Shader::setParameterFloat(const char *key, const float *val)
    {
        glUniform1f(glGetUniformLocation(mProgramId, key), *val);
    }

    void GLSL3Shader::setParameterVector2(const char *key, const Vector2 *val)
    {
        glUniform2fv(glGetUniformLocation(mProgramId, key), 1, val->data);
    }

    void GLSL3Shader::setParameterVector3(const char *key, const Vector3 *val)
    {
        glUniform3fv(glGetUniformLocation(mProgramId, key), 1, val->data);
    }

    void GLSL3Shader::setParameterVector4(const char *key, const Vector4 *val)
    {
        glUniform4fv(glGetUniformLocation(mProgramId, key), 1, val->data);
    }
    
    void GLSL3Shader::setParameterMatrix33(const char *key, const Matrix33 *val)
    {
        glUniformMatrix3fv(glGetUniformLocation(mProgramId, key), 1, GL_FALSE, val->serial);
    }

    void GLSL3Shader::setParameterMatrix44(const char *key, const Matrix44 *val)
    {
        glUniformMatrix4fv(glGetUniformLocation(mProgramId, key), 1, GL_FALSE, val->serial);
    }

    void GLSL3Shader::setViewProjection(const Matrix44 *mat)
    {
        glUniformMatrix4fv(mLocationViewProjection, 1, GL_FALSE, (const GLfloat *)mat->serial);
    }

    void GLSL3Shader::setGeometricState(const GeometricState *state)
    {
        glUniform3fv(mLocationTrans, 1, (const GLfloat *)&state->position.data);
        glUniform4fv(mLocationRot, 1, (const GLfloat *)&state->rotation.data);
        glUniform3fv(mLocationScl, 1, (const GLfloat *)&state->scale.data);
    }

    void GLSL3Shader::setMesh(const Mesh *mesh)
    {
        OpenGL3MeshDriver *driver = (OpenGL3MeshDriver*)mesh->getDriver();

        auto type = mesh->getVertexType();

        glBindVertexArray(driver->getPositionVao());

        if(type & VERTEXTYPE_POSITION != 0)
        {
            glBindBuffer(GL_ARRAY_BUFFER, driver->getPositionBuffer());
            glVertexAttribPointer(mLocationPosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), NULL);
            glEnableVertexAttribArray(mLocationPosition);
        } 

        if(type & VERTEXTYPE_NORMAL)
        {
            glBindBuffer(GL_ARRAY_BUFFER, driver->getNormalBuffer());
            glVertexAttribPointer(mLocationNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), NULL);
            glEnableVertexAttribArray(mLocationNormal);
        } 

        if(type & VERTEXTYPE_UV)
        {
            glBindBuffer(GL_ARRAY_BUFFER, driver->getUVBuffer());
            glVertexAttribPointer(mLocationUv, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), NULL);
            glEnableVertexAttribArray(mLocationUv);
        } 
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, driver->getIndexBuffer());
    
    }


};	// namespace S3D
