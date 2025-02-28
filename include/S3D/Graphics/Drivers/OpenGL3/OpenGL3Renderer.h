#ifndef S3D_OPENGL3RENDERER_H
#define S3D_OPENGL3RENDERER_H

#include "S3D/Common.h"
#include "S3D/Graphics/Shader.h"
#include "S3D/Graphics/Renderer.h"
#include "S3D/Graphics/Material.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"

namespace S3D
{
    class OpenGL3Renderer : public Renderer
    {
    public:
        OpenGL3Renderer()
            : Renderer(),
            mCurrentMaterial(NULL)

        {
        }

        virtual ~OpenGL3Renderer() {}

        virtual bool setRenderFrame(const RenderFrame *frame);
        
        virtual bool setCullingMode(const CullingMode mode);
        
        virtual bool enableDepthTest(const bool enable);
        virtual bool enableStencilTest(const bool enable);
        
        virtual bool setCamera(const Camera *camera);
        virtual bool setLight(const Light *light, const GeometricState *state, int lightIndex);
        
        virtual bool setTexture2D(const Texture2D *texture, const int texIndex);

        virtual bool setMaterial(const Material *material);

        virtual void clear(const int clearType, const Color4 &colorVal, const float depthVal, const unsigned int stencilVal);
        virtual void setViewport(const Rect4 *vieport);
        
        virtual void setGeometry(const GeometricState *state);
        
        virtual void setMesh(const Mesh *mesh);

        virtual void draw(const DrawMode mode, const int vertexCount, const int indexCount);

        virtual bool attachTextureToRenderFrame(const RenderFrame *frame, Texture2D *texture, const int index);

        virtual void checkError();

    protected:
        Matrix44 mViewProjection;
        const Material *mCurrentMaterial;
    };

}; // namespace S3D

#endif // S3D_OPENGL3RENDERER_H
