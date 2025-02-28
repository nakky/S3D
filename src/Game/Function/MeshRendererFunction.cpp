#include "S3D/Game/Function/MeshRendererFunction.h"

#include "S3D/Graphics/Renderer.h"
#include "S3D/Graphics/Mesh.h"
#include "S3D/Game/Function/MeshFunction.h"
#include "S3D/Game/Function/CameraFunction.h"

namespace S3D
{
    void MeshRendererFunction::render(Renderer *renderer, CameraFunction *cameraFunc)
    {
        Mesh *mesh = mMeshFunc->getMesh();
        
        renderer->setMaterial(mMaterial);

        renderer->setCamera(cameraFunc->getCamera());

        renderer->setGeometry(mMeshFunc->getEntity()->getGeometricNode()->getGlobalState());
        renderer->setMesh(mesh);

        renderer->draw(DRAW_TRIANGLES, mesh->getNumVertices(), mesh->getNumIndices());
    }

}; //namespace S3D