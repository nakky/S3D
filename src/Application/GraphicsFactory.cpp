
#include "S3D/Application/GraphicsFactory.h"
#include "S3D/Application/GraphicsContext.h"
#include "S3D/Graphics/ShaderLibrary.h"


#if defined OS_WINDOWS

#include "S3D/Application/Drivers/GLFW/GLFWAppDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3Renderer.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3RenderFrameDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.h"

#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3DefaultShader.h"
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3UnlitShader.h"

#elif defined OS_MACOSX

#include "S3D/Application/Drivers/GLFW/GLFWAppDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3Renderer.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3RenderFrameDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.h"

#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3DefaultShader.h"
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3UnlitShader.h"


#elif defined OS_LINUX

#include "S3D/Application/Drivers/GLFW/GLFWAppDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3Renderer.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3RenderFrameDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.h"

#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3DefaultShader.h"
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3UnlitShader.h"

#endif

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D
{
    //static
    GraphicsDriverType GraphicsFactory::sGraphicsDriverType = (GraphicsDriverType)0;
    bool GraphicsFactory::sIsLoaded = false;

    void GraphicsFactory::load(GraphicsContext *loadContext)
    {
        std::list<Shader *> shaderList;

#if defined OS_WINDOWS
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            {
                shaderList.push_back(new GLSL3DefaultShader());
                shaderList.push_back(new GLSL3UnlitColorShader());
                shaderList.push_back(new GLSL3UnlitTextureShader());
            }
            break;
        }
#elif defined OS_MACOSX
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            {
                shaderList.push_back(new GLSL3DefaultShader());
                shaderList.push_back(new GLSL3UnlitColorShader());
                shaderList.push_back(new GLSL3UnlitTextureShader());
            }
            break;
        }
#elif defined OS_LINUX
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            {
                shaderList.push_back(new GLSL3DefaultShader());
                shaderList.push_back(new GLSL3UnlitColorShader());
                shaderList.push_back(new GLSL3UnlitTextureShader());
            }
            break;
        }
#endif

        for(auto ite = shaderList.begin() ; ite != shaderList.end() ; ite++){
            (*ite)->init();
            (*ite)->load(loadContext);
            ShaderLibrary::retisterShader((*ite)->getName(), (*ite));
        }
        sIsLoaded = true;
    }

    AppDriver *GraphicsFactory::createAppDriver(ContentApp *app)
    {
#if defined OS_WINDOWS
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new GLFWAppDriver(app, 3, 3);
        }

#elif defined OS_MACOSX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new GLFWAppDriver(app, 3, 3);
        }

#elif defined OS_LINUX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new GLFWAppDriver(app, 3, 3);
        }

#endif
        return NULL;
    }

    Renderer *GraphicsFactory::createRenderer()
    {
#if defined OS_WINDOWS
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3Renderer();
        }
        
#elif defined OS_MACOSX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3Renderer();
        }

#elif defined OS_LINUX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3Renderer();
        }

#endif
        return NULL;
    }

    RenderFrameDriver *GraphicsFactory::createRenderFrameDriver(RenderFrame *renderFrame)
    {
#if defined OS_WINDOWS
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3RenderFrameDriver(renderFrame);
        }

#elif defined OS_MACOSX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3RenderFrameDriver(renderFrame);
        }

#elif defined OS_LINUX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3RenderFrameDriver(renderFrame);
        }
#endif
        return NULL;
    }

    Texture2DDriver *GraphicsFactory::createTexture2DDriver(Texture2D *texture)
    {
#if defined OS_WINDOWS
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3Texture2DDriver(texture);
        }

#elif defined OS_MACOSX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3Texture2DDriver(texture);
        }

#elif defined OS_LINUX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3Texture2DDriver(texture);
        }
#endif
        return NULL;
    }

    MeshDriver *GraphicsFactory::createMeshDriver(Mesh *mesh)
    {
#if defined OS_WINDOWS
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3MeshDriver(mesh);
        }

#elif defined OS_MACOSX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3MeshDriver(mesh);
        }

#elif defined OS_LINUX
        
        switch (sGraphicsDriverType)
        {
        case GRAPHICSDRIVER_OPENGL3:
            return new OpenGL3MeshDriver(mesh);
        }
#endif
        return NULL;
    }


}; //namespace S3D
