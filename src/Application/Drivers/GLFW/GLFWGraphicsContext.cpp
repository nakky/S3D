
#include "S3D/Application/Drivers/GLFW/GLFWGraphicsContext.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D
{

    void GLFWGraphicsContext::init()
    {
    }

    void GLFWGraphicsContext::cleanup()
    {
        glfwDestroyWindow(mWindow);
    }


    void GLFWGraphicsContext::bind()
    {
        glfwMakeContextCurrent(mWindow);
    }

    void GLFWGraphicsContext::release()
    {
        glfwMakeContextCurrent(NULL);
    }

    GraphicsContext *GLFWGraphicsContext::createSubContext()
    {
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        GLFWwindow *context = glfwCreateWindow(mResolution.width, mResolution.height, "", NULL, mWindow);
        return new GLFWGraphicsContext(mResolution, context);
    }

    const Size2 *GLFWGraphicsContext::getFrambufferResolution() 
    {
        glfwGetFramebufferSize(mWindow, &mFramebufferResolution.width, &mFramebufferResolution.height);
        return &mFramebufferResolution;
    }


}; //namespace S3D