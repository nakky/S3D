/******************************************************************/
/*!
	@file	Renderer.h
	@brief	Renderer class
	@note
	@todo
	@bug	

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_RENDERER_H
#define S3D_RENDERER_H

#include "S3D/Common.h"

#include "S3D/Graphics/RenderFrame.h"

namespace S3D{
    
    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class Renderer;
    
    //required
    class Mesh;
    class Texture2D;
    class Material;
    struct GeometricState;
    class Color4;

    class RenderFrame;
    
    class Light;
    class Camera;

    enum CullingMode{
        CULLING_NONE = 0,
        CULLING_BACK,
        CULLING_FRONT,
    };
    
    enum DrawMode{
        DRAW_LINES = 0,
        DRAW_LINE_STRIP,
        DRAW_TRIANGLES,
        DRAW_TRIANGLE_FAN,
    };

    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	Renderer
        @brief	Renderer class
        @note	
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class Renderer
    {
    public:
        Renderer()
        {
        }

    public:

        virtual bool setRenderFrame(const RenderFrame *frame) = 0;
        
        virtual bool setCullingMode(const CullingMode mode) = 0;
        
        virtual bool enableDepthTest(const bool enable) = 0;
        virtual bool enableStencilTest(const bool enable) = 0;
        
        virtual bool setCamera(const Camera *camera) = 0;
        virtual bool setLight(const Light *light, const GeometricState *state, int lightIndex) = 0;
        
        virtual bool setTexture2D(const Texture2D *texture, const int texIndex) = 0;

        virtual bool setMaterial(const Material *material) = 0;

        virtual void clear(const int clearType, const Color4 &colorVal, const float depthVal, const unsigned int stencilVal) = 0;
        
        virtual void setViewport(const Rect4 *vieport) = 0;

        virtual void setGeometry(const GeometricState *state) = 0;
        
        virtual void setMesh(const Mesh *mesh) = 0;

        virtual void draw(const DrawMode mode, const int vertexCount, const int indexCount) = 0;

        virtual bool attachTextureToRenderFrame(const RenderFrame *frame, Texture2D *texture, const int index) = 0;
        
        virtual void checkError() = 0;

        virtual void onPreReset() { }
        virtual void onPostReset() { }

    };

};	// namespace S3D

#endif //S3D_RENDERER_H
