#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3RenderFrameDriver.h"

#include "S3D/Application/GraphicsContext.h"

#include "S3D/Graphics/RenderFrame.h"


#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D
{
    void OpenGL3RenderFrameDriver::load(GraphicsContext *context)
    {
        context->bind();

        glGenFramebuffers(1, &mFrameBufferName);
		glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferName);

        auto res = mRenderFrame->getResolution();

        GLuint colorrenderbuffer = 0;
        if ((mRenderFrame->getBufferType() & FRAMEBUFFER_COLOR) != 0) {
            glGenRenderbuffers(1, &mColorRenderBufferName);
            if (mColorRenderBufferName == 0) {
                glDeleteFramebuffers(1, &mFrameBufferName);
                context->release();
                return;
            }

            glBindRenderbuffer(GL_RENDERBUFFER, mColorRenderBufferName);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_COLOR_INDEX, res->width, res->height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, mColorRenderBufferName);
        }

        GLuint depthrenderbuffer = 0;
        if ((mRenderFrame->getBufferType() & FRAMEBUFFER_DEPTH) != 0) {
            glGenRenderbuffers(1, &mDepthRenderBufferName);
            if (mDepthRenderBufferName == 0) {
                glDeleteFramebuffers(1, &mFrameBufferName);
                context->release();
                return;
            }

            glBindRenderbuffer(GL_RENDERBUFFER, mDepthRenderBufferName);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, res->width, res->height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRenderBufferName);
        }

        GLuint stencilrenderbuffer = 0;
        if ((mRenderFrame->getBufferType() & FRAMEBUFFER_STENCIL) != 0) {
            glGenRenderbuffers(1, &mStencilRenderBufferName);
            if (mStencilRenderBufferName == 0) {
                glDeleteFramebuffers(1, &mFrameBufferName);
                context->release();
                return;
            }

            glBindRenderbuffer(GL_RENDERBUFFER, mStencilRenderBufferName);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX, res->width, res->height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mStencilRenderBufferName);
        }

        context->release();
    }
    
    void OpenGL3RenderFrameDriver::unload(GraphicsContext *context)
    {
        context->bind();

        glBindFramebuffer(GL_FRAMEBUFFER, mFrameBufferName);
        glDeleteFramebuffers(1, &mFrameBufferName);

        context->release();
    }

}; //namespace S3D