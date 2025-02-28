/******************************************************************/
/*!
	@file	GLFWAppDriver.h
	@brief	
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Apl. 1, 2020
*/
/******************************************************************/

#ifndef S3D_GLFW_GLFWAPPDRIVER_H
#define S3D_GLFW_GLFWAPPDRIVER_H

#include "S3D/Common.h"
#include "S3D/Application/AppDriver.h"

struct GLFWwindow;

namespace S3D
{
    class GLFWAppDriver : public AppDriver
    {
    public:
        GLFWAppDriver(ContentApp *app, int glMajor, int glMinor)
        :AppDriver(app),
        mWindow(NULL),
        mGlMajor(glMajor),
        mGlMinor(glMinor)
        {
        }

        virtual ~GLFWAppDriver(){};

        virtual void init();
        virtual void cleanup();

        virtual bool runningProcessQueue();

        virtual GraphicsContext *createMainContext();

        virtual void swapBuffers(S3D::GraphicsContext *context);

        virtual bool isCreateSubContextInMainThread(){ return true; }

        virtual void getDisplayModes(std::vector<DisplayMode> &modes) const;
        virtual void changeDisplayMode(const DisplayMode &mode);

    protected:
        GLFWwindow *mWindow;
        int mGlMajor;
        int mGlMinor;
    };

} //namespace S3D


#endif //S3D_GLFW_GLFWAPPDRIVER_H
