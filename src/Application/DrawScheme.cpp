
#include "S3D/Application/DrawScheme.h"

#include "S3D/Application/ContentApp.h"
#include "S3D/Graphics/Renderer.h"
#include "S3D/Application/GraphicsFactory.h"
#include "S3D/Graphics/RenderFrame.h"
#include "S3D/Game/Function/CameraFunction.h"
#include "S3D/Game/Function/RendererFunction.h"

namespace S3D
{
    void DrawScheme::init()
    {
        mRenderer = GraphicsFactory::createRenderer();
    }

    void DrawScheme::cleanup()
    {
        SAFE_DELETE(mRenderer);
    }

}; //namespace S3D