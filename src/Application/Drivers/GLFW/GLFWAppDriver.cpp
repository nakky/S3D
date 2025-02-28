

#include "S3D/Application/Drivers/GLFW/GLFWAppDriver.h"
#include "S3D/Application/Drivers/GLFW/GLFWGraphicsContext.h"
#include "S3D/Application/ContentApp.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


namespace S3D
{

    static void error_callback(int error, const char *description)
    {
        fprintf(stderr, "Error: %s\n", description);
    }

    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }


    void GLFWAppDriver::init()
    {
        AppDriver::init();

        glfwSetErrorCallback(error_callback);

        if (!glfwInit())
            exit(EXIT_FAILURE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mGlMajor);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mGlMinor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void GLFWAppDriver::cleanup()
    {
        AppDriver::cleanup();
    }

    bool GLFWAppDriver::runningProcessQueue()
    {
        glfwPollEvents();

        if(glfwWindowShouldClose(mWindow)) return false;
        return true;
    }

    void GLFWAppDriver::getDisplayModes(std::vector<DisplayMode> &modes) const
    {
        modes.clear();

        GLFWmonitor* monitor = glfwGetPrimaryMonitor();
        
        int count;
        const GLFWvidmode* gmodes = glfwGetVideoModes(monitor, &count);
        for(int i = 0 ; i < count ; i++){
            modes.push_back(DisplayMode(false, Size2(gmodes[i].width, gmodes[i].height), gmodes[i].refreshRate));
        }
    }

    void GLFWAppDriver::changeDisplayMode(const DisplayMode &mode)
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();

        if(!mode.isFullscreen) monitor = NULL;
        
        glfwSetWindowMonitor(mWindow, monitor, 0, 0, mode.resolution.width, mode.resolution.height, mode.refreshRate);
            
        //int width, height;
        //glfwGetWindowSize(mWindow, &width, &height);
        //printf("resolution: %d, %d\n", width, height);
    }

    GraphicsContext *GLFWAppDriver::createMainContext()
    {
        GLFWmonitor* monitor = glfwGetPrimaryMonitor();

        auto dispalyMode = mApplication->getDisplayMode();
        auto mode = glfwGetVideoMode(monitor);
        
        int width = dispalyMode->resolution.width;
        int height = dispalyMode->resolution.height;
        int refreshRate = dispalyMode->refreshRate;

        if(width == 0 || height == 0) {
            width = mode->width;
            height = mode->height;
        }

        if(refreshRate == 0)
        {
            refreshRate = mode->refreshRate;
        }
        
        GLFWmonitor *mon = monitor;
        if(!dispalyMode->isFullscreen) mon = NULL;

        glfwWindowHint(GLFW_RESIZABLE, false);

        mWindow = glfwCreateWindow(width, height, "S3D Example", mon, NULL);
        if (!mWindow)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        if(dispalyMode->isFullscreen)
        {
            glfwSetWindowMonitor(mWindow, monitor, 0, 0, width, height, refreshRate);
            
            //glfwGetWindowSize(mWindow, &width, &height);
            //printf("resolution: %d, %d\n", width, height);
        }
        
        glfwSetKeyCallback(mWindow, key_callback);

        glfwMakeContextCurrent(mWindow);
        gladLoadGL();
        glfwSwapInterval(1);

        return new GLFWGraphicsContext(Size2(width, height), mWindow);
    }

    void GLFWAppDriver::swapBuffers(S3D::GraphicsContext *context)
    {
        glfwMakeContextCurrent(mWindow);
        if(mApplication->getGraphicsMode()->vSync) glfwSwapInterval(1);
        else  glfwSwapInterval(0);

        glfwSwapBuffers(mWindow);
    }

}; //namespace S3D