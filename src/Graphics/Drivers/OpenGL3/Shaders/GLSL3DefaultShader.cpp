
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3DefaultShader.h"

#include "S3D/Graphics/ShaderParameters.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D
{    
    void GLSL3DefaultShader::init()
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
            "void main()"
            "{"
            "    fragment = vec4(1.0, 0.0, 1.0, 1.0);"
            "}\n";
    }

    void GLSL3DefaultShader::load(GraphicsContext *context)
    {
        GLSL3Shader::load(context);
    }

    ShaderParameter *GLSL3DefaultShader::createParameter()
    {
        return new ShaderParameter();
    }
    
    void GLSL3DefaultShader::applyParameter(const ShaderParameter *params)
    {
        ShaderParameter *sparams = (ShaderParameter*)params;   
    }

}; //namespace S3D