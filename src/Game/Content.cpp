
#include "S3D/Game/Content.h"

#include "S3D/Application/GraphicsContext.h"
#include "S3D/Application/GraphicsQueueThread.h"

namespace S3D
{
    void Content::init()
    {
        mResourceDB.init();
    }

    void Content::load(GraphicsContext *loadingContext)
    {
        for(auto ite = mResourceDB.begin() ; ite != mResourceDB.end() ; ite++){            
            (*ite).second->load(loadingContext);
        }
    }
    
    void Content::unload(GraphicsContext *loadingContext)
    {
        for(auto ite = mResourceDB.begin() ; ite != mResourceDB.end() ; ite++){
            (*ite).second->unload(loadingContext);
        }
    }
    
    void Content::cleanup()
    {
        mResourceDB.clear();
    }

    bool Content::update(float delta)
    {
        updateFunctions(delta, &mRootEntity);
        return false;
    }

    void Content::updateFunctions(float delta, Entity *entity)
    {
        entity->functionUpdate(delta);

        std::list<GeometricNode *> &children = entity->getGeometricNode()->getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (*ite)->getEntity();
            updateFunctions(delta, next);
        }
    }

    void Content::fixedUpdate(float delta)
    {
        fixedUpdateFunctions(delta, &mRootEntity);
    }

    bool Content::fixedUpdateFunctions(float delta, Entity *entity)
    {
        entity->functionFixedUpdate(delta);

        std::list<GeometricNode *> &children = entity->getGeometricNode()->getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (*ite)->getEntity();
            updateFunctions(delta, next);
        }
        
        return false;
    }

}; //namespace S3D
