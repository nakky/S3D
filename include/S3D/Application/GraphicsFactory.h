#ifndef S3D_APPLICATION_GRAPHICSFACTORY_H
#define S3D_APPLICATION_GRAPHICSFACTORY_H

#include "S3D/Common.h"

#include <stdio.h>

namespace S3D
{
    class ContentApp;
    class AppDriver;
    class Renderer;

    class RenderFrame;
    class Mesh;
    class Texture2D;

    class RenderFrameDriver;
    class MeshDriver;
    class Texture2DDriver;

    class GraphicsContext;

    enum GraphicsDriverType
    {
        //0 is default driver
#if defined OS_WINDOWS

        GRAPHICSDRIVER_OPENGL3 = 0,

#elif defined OS_MACOSX

        GRAPHICSDRIVER_OPENGL3 = 0,

#elif defined OS_LINUX

        GRAPHICSDRIVER_OPENGL3 = 0,

#endif
    };

    class GraphicsFactory
    {
    
    public:
        static bool isLoaded(){ return sIsLoaded; }
        static void load(GraphicsContext *loadContext);

        static GraphicsDriverType setGraphicsDriverType(GraphicsDriverType type){ sGraphicsDriverType = type; }

        static AppDriver *createAppDriver(ContentApp *app);
        static Renderer *createRenderer();
        static RenderFrameDriver *createRenderFrameDriver(RenderFrame *renderFrame);
        static Texture2DDriver *createTexture2DDriver(Texture2D *texture);
        static MeshDriver *createMeshDriver(Mesh *mesh);
    private:
        static GraphicsDriverType sGraphicsDriverType;
        static bool sIsLoaded;
       
    };

}; //namespace S3D

#endif //S3D_APPLICATION_GRAPHICSFACTORY_H
