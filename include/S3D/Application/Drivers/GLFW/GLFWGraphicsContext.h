/******************************************************************/
/*!
	@file	GLFWGraphicsContext.h
	@brief	
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Apl. 1, 2020
*/
/******************************************************************/


#ifndef S3D_GLFW_GLFWGRAPHICSCONTEXT_H
#define S3D_GLFW_GLFWGRAPHICSCONTEXT_H

#include "S3D/Common.h"
#include "S3D/Application/GraphicsContext.h"

struct GLFWwindow;

namespace S3D
{
    class GLFWGraphicsContext : public S3D::GraphicsContext
    {
    public:
        GLFWGraphicsContext(const Size2 &resolution, GLFWwindow *window):
        S3D::GraphicsContext(resolution),
        mWindow(window)
        {
        }

    public:
        virtual void init();
        virtual void cleanup();

        virtual void bind();
        virtual void release();

        virtual GraphicsContext *createSubContext();

        virtual const Size2 *getFrambufferResolution();


    protected:
        GLFWwindow *mWindow;

        Size2 mFramebufferResolution;

    };

} //namespace S3D

#endif //S3D_GLFW_GLFWGRAPHICSCONTEXT_H
