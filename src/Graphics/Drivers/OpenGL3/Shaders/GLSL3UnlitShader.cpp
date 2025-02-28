
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3UnlitShader.h"

#include "S3D/Graphics/ShaderParameters.h"

#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D
{    
    void GLSL3UnlitColorShader::init()
    {
        mVertexShader = 
            "#version 330\n"
            "vec3 mul(vec3 v1, vec3 v2){\n"
            "   return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);\n"
            "}\n"
            "vec3 rotate(vec3 v, vec4 q){\n"
            "   float rx = v.x * q.w + v.y * -q.z + v.z * q.y;\n"
            "   float ry = v.x * q.z + v.y * q.w + v.z * -q.x;\n"
            "   float rz = v.x * -q.y + v.y * q.x + v.z * q.w;\n"
            "	float rw = v.x * q.x + v.y * q.y + v.z * q.z;\n"
            "	return vec3( q.x * rw + q.y * rz + q.z * -ry + q.w * rx,\n"
            "	    q.x * -rz + q.y * rw + q.z * rx + q.w * ry,\n"
            "	    q.x * ry + q.y * -rx + q.z * rw + q.w * rz);\n"
            "}\n"
            "uniform mat4 _projection;\n"
            "uniform vec3 _trans;\n"
            "uniform vec4 _rot;\n"
            "uniform vec3 _scl;\n"
            "in vec3 _position;\n"
            "void main()\n"
            "{\n"
            "   vec4 vec = vec4(rotate(mul(_position, _scl), _rot) + _trans, 1.0);\n"
            "   gl_Position = _projection * vec;\n"
            "}\n";

        mFragmentShader = 
            "#version 330\n"
            "uniform vec4 color;\n"
            "out vec4 fragment;\n"
            "void main()\n"
            "{\n"
            "    fragment = color;\n"
            "}\n";
    }

    void GLSL3UnlitColorShader::load(GraphicsContext *context)
    {
        GLSL3Shader::load(context);

        context->bind();

        mLocationColor = glGetUniformLocation(mProgramId, "color");
     
        context->release();
    }

    ShaderParameter *GLSL3UnlitColorShader::createParameter()
    {
        return new UnlitColorShaderParameter();
    }
    
    void GLSL3UnlitColorShader::applyParameter(const ShaderParameter *params)
    {
        UnlitColorShaderParameter *sparams = (UnlitColorShaderParameter*)params;   
        glUniform4fv(mLocationColor, 1, sparams->color.data);
    }

    void GLSL3UnlitColorShader::setMesh(const Mesh *mesh)
    {
        GLSL3Shader::setMesh(mesh);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);  
    }

    void GLSL3UnlitTextureShader::init()
    {
        mVertexShader = 
            "#version 330\n"
            "vec3 mul(vec3 v1, vec3 v2){\n"
            "   return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);\n"
            "}\n"
            "vec3 rotate(vec3 v, vec4 q){\n"
            "   float rx = v.x * q.w + v.y * -q.z + v.z * q.y;\n"
            "   float ry = v.x * q.z + v.y * q.w + v.z * -q.x;\n"
            "   float rz = v.x * -q.y + v.y * q.x + v.z * q.w;\n"
            "	float rw = v.x * q.x + v.y * q.y + v.z * q.z;\n"
            "	return vec3( q.x * rw + q.y * rz + q.z * -ry + q.w * rx,\n"
            "	    q.x * -rz + q.y * rw + q.z * rx + q.w * ry,\n"
            "	    q.x * ry + q.y * -rx + q.z * rw + q.w * rz);\n"
            "}\n"
            "uniform mat4 _projection;\n"
            "uniform vec3 _trans;\n"
            "uniform vec4 _rot;\n"
            "uniform vec3 _scl;\n"
            "in vec3 _position;\n"
            "in vec2 _uv;\n"
            "out vec2 _texCoord;\n"
            "void main()\n"
            "{\n"
            "   vec4 vec = vec4(rotate(mul(_position, _scl), _rot) + _trans, 1.0);\n"
            "   gl_Position = _projection * vec;\n"
            "   _texCoord = _uv;\n"
            "}\n";

        mFragmentShader = 
            "#version 330\n"
            "uniform vec4 color;\n"
            "uniform sampler2D albedo;\n"
            "in vec2 _texCoord;\n"
            "out vec4 fragment;\n"
            "void main()\n"
            "{\n"
            "    vec4 texcolor = texture(albedo, _texCoord);\n"
            "    fragment = vec4(texcolor.x * color.x, texcolor.y * color.y, texcolor.z * color.z, texcolor.w * color.w );\n"
            "}\n";
    }

    void GLSL3UnlitTextureShader::load(GraphicsContext *context)
    {
        GLSL3Shader::load(context);

        context->bind();

        mLocationColor = glGetUniformLocation(mProgramId, "color");
        mLocationAlbedo = glGetUniformLocation(mProgramId, "albedo");
     
        context->release();
    }

    ShaderParameter *GLSL3UnlitTextureShader::createParameter()
    {
        return new UnlitTextureShaderParameter();
    }
    
    void GLSL3UnlitTextureShader::applyParameter(const ShaderParameter *params)
    {
        UnlitTextureShaderParameter *sparams = (UnlitTextureShaderParameter*)params;   
        glUniform4fv(mLocationColor, 1, sparams->color.data);

        OpenGL3Texture2DDriver *driver = (OpenGL3Texture2DDriver*)sparams->texture->getDriver();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, driver->getTextureName());
    }

    void GLSL3UnlitTextureShader::setMesh(const Mesh *mesh)
    {
        GLSL3Shader::setMesh(mesh);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);  
    }

}; //namespace S3D