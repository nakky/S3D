#include "S3D/Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.h"

#include "S3D/Application/GraphicsContext.h"

#include "S3D/Graphics/Mesh.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"

#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace S3D
{
    void OpenGL3MeshDriver::load(GraphicsContext *context)
    {
        context->bind();
        
        int vtype = mMesh->getVertexType();

        glGenVertexArrays(1, &mPositionVao);
        glBindVertexArray(mPositionVao);

        if(vtype & VERTEXTYPE_POSITION != 0){
            glGenBuffers(1, &mPositionBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, mPositionBuffer);
            glBufferData(GL_ARRAY_BUFFER, mMesh->getVerticesBufferSize(), mMesh->getVertices(), GL_STATIC_DRAW);
        }
        
        if(vtype & VERTEXTYPE_NORMAL != 0){
            glGenBuffers(1, &mNormalBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, mNormalBuffer);
            glBufferData(GL_ARRAY_BUFFER, mMesh->getNormalsBufferSize(), mMesh->getNormals(), GL_STATIC_DRAW);
        }

        if(vtype & VERTEXTYPE_UV != 0){
            glGenBuffers(1, &mUVBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, mUVBuffer);
            glBufferData(GL_ARRAY_BUFFER, mMesh->getUvsBufferSize(), mMesh->getUvs(), GL_STATIC_DRAW);
        }

        glGenBuffers(1, &mIndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, mMesh->getIndicesBufferSize(), mMesh->getIndices(), GL_STATIC_DRAW);

        context->release();
    }
    
    void OpenGL3MeshDriver::unload(GraphicsContext *context)
    {
        context->bind();

    
        context->release();
    }

}; //namespace S3D