
#include "Home/HomeContent.h"

#include "S3D/Game/Function/CameraFunction.h"
#include "S3D/Game/Function/MeshFunction.h"
#include "S3D/Game/Function/MeshRendererFunction.h"
#include "S3D/Game/Function/RotatingFunction.h"

#include "S3D/Graphics/ShaderParameters.h"

#include "S3D/Graphics/Mesh/Cuboid.h"

using namespace S3D;

void HomeContent::init()
{
    Content::init();

    printf("HomeContent::init\n");
}

void HomeContent::load(S3D::GraphicsContext *context)
{
    //load
    printf("HomeContent::load\n");

    Entity *entity = NULL;
    Mesh *mesh = NULL;
    Material *mat = NULL;
    MeshFunction *meshF = NULL;
    MeshRendererFunction *meshRendererF = NULL;
    CameraFunction *cameraF = NULL;
    RotatingFunction *rotatingF = NULL;
    Texture2D *tex2D = NULL;

    entity = new Entity();
    mRootEntity.getGeometricNode()->setRelationToChild(entity->getGeometricNode());

    cameraF = new CameraFunction();
    entity->addFunction(cameraF);

    entity->getGeometricNode()->setLocalPosition(Vector3(0.0f, 0.0f, -10.0f));

    entity = new Entity();
    mRootEntity.getGeometricNode()->setRelationToChild(entity->getGeometricNode());

    mesh = new Cuboid();
    mesh->init();

    mesh->setIsStatic(false);
    mesh->setVertexType(VERTEXTYPE_POSITION | VERTEXTYPE_UV);

    mResourceDB.registerResource(mesh);

    meshF = new MeshFunction();
    meshF->setMesh(mesh);
    entity->addFunction(meshF);

    mat = new Material();
    mat->init();
    mat->setShaderName("Unlit/Texture");
    mat->setOpaque(false);
    mResourceDB.registerResource(mat);

    meshRendererF = new MeshRendererFunction();
    meshRendererF->setMeshFunction(meshF);
    meshRendererF->setMaterial(mat);
    entity->addFunction(meshRendererF);

    rotatingF = new RotatingFunction();
    entity->addFunction(rotatingF);

    tex2D = new Texture2D();
    tex2D->init();

    tex2D->setIsStatic(false);
    tex2D->setType(TextureType::TEXTURE_COLOR);
    tex2D->setFilePath("./assets/images/s3d.png");
    mResourceDB.registerResource(tex2D);

    auto entity2 = new Entity();
    entity->getGeometricNode()->setRelationToChild(entity2->getGeometricNode());
    
    meshF = new MeshFunction();
    meshF->setMesh(mesh);
    entity2->addFunction(meshF);

    meshRendererF = new MeshRendererFunction();
    meshRendererF->setMeshFunction(meshF);
    meshRendererF->setMaterial(mat);
    entity2->addFunction(meshRendererF);

    entity2->getGeometricNode()->setLocalPosition(Vector3(0.25f, 0.25f, 0.0f));

    auto rotatingF2 = new RotatingFunction();
    entity2->addFunction(rotatingF2);


    ////////////
    Content::load(context);
    ////////////

    auto tmat = (UnlitTextureShaderParameter*)mat->getShaderParameter();
    tmat->texture = tex2D;
    tmat->color = Color4(1.0f, 1.0f, 1.0f, 0.5f);
    
    cameraF->setBackgroundColor(Color4(0.1f, 0.2f, 0.1f, 1.0f));

    rotatingF->setRotatingVelocity(90.0f);
    rotatingF2->setRotatingVelocity(90.0f);
}

void HomeContent::unload(S3D::GraphicsContext *context)
{
    printf("HomeContent::unload\n");

    Content::unload(context);
}

void HomeContent::cleanup()
{
    printf("HomeContent::cleanup\n");

    Content::cleanup();
}

bool HomeContent::update(float delta)
{
    return Content::update(delta);
}


