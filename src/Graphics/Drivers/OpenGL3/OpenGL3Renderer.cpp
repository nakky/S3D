
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3Renderer.h"

#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3RenderFrameDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.h"
#include "S3D/Graphics/Drivers/OpenGL3/Shaders/GLSL3Shader.h"

#include "S3D/Graphics/Camera.h"
#include "S3D/Graphics/Light.h"
#include "S3D/Graphics/Texture.h"


#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D
{
    bool OpenGL3Renderer::setRenderFrame(const RenderFrame *frame)
    {
        if (frame != NULL) {
            OpenGL3RenderFrameDriver *driver = (OpenGL3RenderFrameDriver*)frame;
            glBindFramebuffer(GL_FRAMEBUFFER, driver->getFrameBufferName());
        }
        else {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        return true;
    }

    bool OpenGL3Renderer::setCullingMode(const CullingMode mode)
    {
        if(mode & CULLING_FRONT != 0) glCullFace(GL_FRONT);
        if(mode & CULLING_BACK != 0) glCullFace(GL_BACK);
        if(!mode) glCullFace(GL_NONE);
        return true;
    }
    
    bool OpenGL3Renderer::enableDepthTest(const bool enable)
    {
        if(enable) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
        return true;
    }

    bool OpenGL3Renderer::enableStencilTest(const bool enable)
    {
         if(enable) glEnable(GL_STENCIL_TEST);
        else glDisable(GL_STENCIL_TEST);
        return true;
    }
    
    bool OpenGL3Renderer::setCamera(const Camera *camera)
    {
        mViewProjection.setUnitMatrix();

        mCurrentMaterial->getShader()->setViewProjection(camera->getViewProjection());

        return TRUE;
    }

    bool OpenGL3Renderer::setLight(const Light *light, const GeometricState *state, int lightIndex)
    {
        GLenum glIndex = GL_LIGHT0 + lightIndex;
        
        if(light != NULL){
            glEnable(glIndex);
            
            float buffer[4];

            const Color4 *diffuseref = light->getColor();
            ::glLightfv(glIndex, GL_DIFFUSE, diffuseref->data);

            const Color4 *specularref = light->getColor();
            ::glLightfv(glIndex, GL_SPECULAR, specularref->data);
            
            LightType type = light->getLightType();
            switch (type) {
                case LIGHT_DIRECTIONAL:
                {
                    Vector3 direction = Vector3(0.0f, 0.0f, 1.0f);
                    Vector3 actual;
                    state->rotation.convertVector(actual, direction);
                    
                    buffer[0] = -actual.x; buffer[1] = -actual.y; buffer[2] = -actual.z; buffer[3] = 0.0f;
                    ::glLightfv(glIndex, GL_POSITION, buffer);
                }
                    break;
                case LIGHT_SPOT:
                {
                    buffer[0] = state->position.x; buffer[1] = state->position.y; buffer[2] = state->position.z; buffer[3] = 1.0f;
                    ::glLightfv(glIndex, GL_POSITION, buffer);

                    Vector3 direction = Vector3(0.0f, 0.0f, 1.0f);
                    Vector3 actual;
                    state->rotation.convertVector(actual, direction);
                    buffer[0] = actual.x; buffer[1] = actual.y; buffer[2] = actual.z; buffer[3] = 1.0f;
                    ::glLightfv(glIndex, GL_SPOT_DIRECTION, buffer);

                    ::glLightf(glIndex, GL_SPOT_EXPONENT, (light->getSpotInnerConeAngle() / light->getSpotOuterConeAngle() * 128.0f));
                    ::glLightf(glIndex, GL_SPOT_CUTOFF, light->getSpotOuterConeAngle() / 2.0f);

                    float constant, linear, quadratic;

                    light->getAttenuation(&constant, &linear, &quadratic);

                    ::glLightf(glIndex, GL_CONSTANT_ATTENUATION, constant);
                    ::glLightf(glIndex, GL_LINEAR_ATTENUATION, linear);
                    ::glLightf(glIndex, GL_QUADRATIC_ATTENUATION, quadratic);
                    
                    
                }
                    break;
                case LIGHT_POINT:
                {
                    buffer[0] = state->position.x; buffer[1] = state->position.y; buffer[2] = state->position.z; buffer[3] = 1.0f;
                    ::glLightfv(glIndex, GL_POSITION, buffer);

                    ::glLightf(glIndex, GL_SPOT_CUTOFF, 180.0f);

                    float constant, linear, quadratic;

                    light->getAttenuation(&constant, &linear, &quadratic);

                    ::glLightf(glIndex, GL_CONSTANT_ATTENUATION, constant);
                    ::glLightf(glIndex, GL_LINEAR_ATTENUATION, linear);
                    ::glLightf(glIndex, GL_QUADRATIC_ATTENUATION, quadratic);
                }
                    break;
                    
            }

        }else{
            glDisable(glIndex);
        }
            
        return true;
    }
    
    bool OpenGL3Renderer::setTexture2D(const Texture2D *texture, const int texIndex)
    {
        int glIndex = GL_TEXTURE0 + texIndex;
        if(texture != NULL) {
            ::glActiveTexture(glIndex);

            OpenGL3Texture2DDriver *driver = (OpenGL3Texture2DDriver*)texture->getDriver();
            
            ::glBindTexture(GL_TEXTURE_2D, driver->getTextureName());
            
            ::glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
            ::glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        }else{
            glActiveTexture(glIndex);
            ::glBindTexture(GL_TEXTURE_2D, 0);
        }
        return true;
    }

    bool OpenGL3Renderer::setMaterial(const Material *material)
    {
        mCurrentMaterial = material;

        GLSL3Shader *glshader = (GLSL3Shader*)mCurrentMaterial->getShader();
        glUseProgram(glshader->getProgramId());
        glshader->applyParameter(mCurrentMaterial->getShaderParameter());

        if(material->isOpaque()){
            glDisable(GL_BLEND);
        }else{
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        }

        
        return true;
    }

    void OpenGL3Renderer::clear(const int clearType, const Color4 &colorVal, const float depthVal, const unsigned int stencilVal)
    {
        GLbitfield bits = 0;
            
        if ((clearType & FRAMEBUFFER_COLOR) != 0){
            bits |= GL_COLOR_BUFFER_BIT;
            glClearColor(colorVal.r, colorVal.g, colorVal.b, colorVal.a);
        }
        
        if ((clearType & FRAMEBUFFER_DEPTH) != 0){
            bits |= GL_DEPTH_BUFFER_BIT;
            glClearDepth(depthVal);
        }
        
        if ((clearType & FRAMEBUFFER_STENCIL) != 0){
            bits |= GL_STENCIL_BUFFER_BIT;
            glClearStencil(stencilVal);
        }
        
        if (bits){
            glClear(bits);
        }
    }

    void OpenGL3Renderer::setViewport(const Rect4 *vieport)
    {
        glViewport(vieport->x, vieport->y, vieport->width, vieport->height);
    }
    
    void OpenGL3Renderer::setGeometry(const GeometricState *state)
    {
        GLSL3Shader *shader = (GLSL3Shader*)mCurrentMaterial->getShader();
        shader->setGeometricState(state);
    }

    void OpenGL3Renderer::setMesh(const Mesh *mesh)
    {
        if(mesh != NULL){
            GLSL3Shader *shader = (GLSL3Shader*)mCurrentMaterial->getShader();
            shader->setMesh(mesh);
        }
    }

    void OpenGL3Renderer::draw(const DrawMode mode, const int vertexCount, const int indexCount)
    {
        switch (mode) {
            case DRAW_LINES:
                glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);
                break;
            case DRAW_LINE_STRIP:
                glDrawElements(GL_LINE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
                break;
            case DRAW_TRIANGLES:
                glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
                break;
            case DRAW_TRIANGLE_FAN:
                glDrawElements(GL_TRIANGLE_FAN, indexCount, GL_UNSIGNED_INT, 0);
                break;
            default:
                break;
            
        }
    }

    bool OpenGL3Renderer::attachTextureToRenderFrame(const RenderFrame *frame, Texture2D *texture, const int index)
    {

        return true;
    }
    
    void OpenGL3Renderer::checkError()
    {
        printf("GL Error:%d\n", glGetError());
    }


}; //namespace S3D