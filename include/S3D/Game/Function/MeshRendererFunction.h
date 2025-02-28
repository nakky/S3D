#ifndef S3D_GAME_FUNCTION_MESHRENDERERFUNCTION_H
#define S3D_GAME_FUNCTION_MESHRENDERERFUNCTION_H

#include "S3D/Game/Function/RendererFunction.h"

namespace S3D
{
    class MeshFunction;
    class Renderer;

    class MeshRendererFunction : public RendererFunction
    {
    public:
        MeshRendererFunction()
        :RendererFunction(),
        mMeshFunc(NULL)
        {
        }
        
        constexpr virtual unsigned long getFunctionType() { return entityNameHash("S3D::MeshRendererFunction");}

        void setMeshFunction(MeshFunction *meshFunc) { mMeshFunc = meshFunc; }

        virtual void render(Renderer *renderer, CameraFunction *cameraFunc);

    protected:
        MeshFunction *mMeshFunc;
    };

};

#endif //S3D_GAME_FUNCTION_RENDERERFUNCTION_H

