#ifndef S3D_GAME_FUNCTION_RENDERERFUNCTION_H
#define S3D_GAME_FUNCTION_RENDERERFUNCTION_H

#include "S3D/Game/Function/EntityFunction.h"
#include "S3D/Graphics/Material.h"

namespace S3D
{
    class Material;
    class Renderer;

    class RendererFunction : public EntityFunction
    {
        friend class RenderList;

    public:
        RendererFunction()
        :EntityFunction(),
        mOrderValue(0),
        mDiffFromCamera(100000000000.0f)

        {
        }

        virtual const bool isRenderer() const { return true; }

        float getDiffFromCamera() { return mDiffFromCamera; }

        short getOrderValue() { return mOrderValue; }
        void setOrderValue(short value) { mOrderValue = value; }

        void setMaterial(Material *mat) { mMaterial = mat; }
        Material *getMaterial() { return mMaterial; }

        virtual void render(Renderer *renderer, CameraFunction *cameraFunc) = 0;

    protected:
        void setDiffFromCamera(const float diff) { mDiffFromCamera = diff; }

    protected:
        float mDiffFromCamera;
        short mOrderValue;

        Material *mMaterial;

    };

};

#endif //S3D_GAME_FUNCTION_RENDERERFUNCTION_H

