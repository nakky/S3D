
#include "S3D/Application/DrawScheme/SimpleDrawScheme.h"

#include "S3D/Application/ContentApp.h"
#include "S3D/Graphics/Renderer.h"
#include "S3D/Application/GraphicsFactory.h"
#include "S3D/Graphics/RenderFrame.h"
#include "S3D/Game/Function/CameraFunction.h"
#include "S3D/Game/Function/RendererFunction.h"

namespace S3D
{
    bool SimpleDrawScheme::update()
    {
        auto contents = mApplication->getCurrentContents();
        
        bool isDirty = false;
        //Check
        for(auto ite = contents->begin() ; ite != contents->end(); ite++)
        {
            Entity *entity = (*ite)->getRootEntity();
            bool d = checkFunction(entity);
            if(d) isDirty = true;
        }

        //Update Geometry
        for(auto ite = contents->begin() ; ite != contents->end(); ite++)
        {
            Entity *entity = (*ite)->getRootEntity();
            updateGeometry(entity, false);
        }

        return isDirty;
    }
    
    bool SimpleDrawScheme::checkFunction(Entity *entity)
    {
        if(!entity->isActive()) return false;

        bool dirty = false;

        std::list<CameraFunction*> funcs;
        entity->getCameras(&funcs) ;

        for(auto ite = funcs.begin() ; ite != funcs.end() ; ite++)
        {
            mRenderLists.push_back(new RenderList(*ite));
        }

        //Children
        std::list<GeometricNode *> &children = entity->getGeometricNode()->getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (*ite)->getEntity();
            dirty = checkFunction(next);
        }

        return entity->isDirty() | dirty;
    }

    void SimpleDrawScheme::updateGeometry(Entity *entity, bool parentIsDirty)
    {
        if(!entity->isActive()) return;

        //Update
        bool needCalculate = parentIsDirty || entity->getGeometricNode()->isDirty();
        if(needCalculate) entity->getGeometricNode()->calculateGlobalState(); 

        //Entity
        std::list<RendererFunction*> funcs;
        entity->getRenderers(&funcs) ;

        for (auto iteList = mRenderLists.begin(); iteList != mRenderLists.end(); iteList++)
        {
            for(auto ite = funcs.begin() ; ite != funcs.end() ; ite++){
                (*iteList)->add(*ite);
            }
        }

        //Children
        std::list<GeometricNode *> &children = entity->getGeometricNode()->getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (*ite)->getEntity();
            updateGeometry(next, needCalculate);
        }
    }

    void SimpleDrawScheme::draw()
    {
        for (auto ite = mRenderLists.begin(); ite != mRenderLists.end(); ite++)
        {
            (*ite)->sortByDistance();
        }

        for (auto ite = mRenderLists.begin(); ite != mRenderLists.end(); ite++)
        {
            auto cameraFunc = (*ite)->getCameraFunction();
            auto camera = cameraFunc->getCamera();

            mApplication->getMainGraphicsContext()->bind();

            camera->setResolution(*mApplication->getMainGraphicsContext()->getFrambufferResolution());            
            camera->updateViewProjection(cameraFunc->getEntity()->getGeometricNode()->getGlobalState());

            auto res = mApplication->getMainGraphicsContext()->getFrambufferResolution();
            //printf("res: %d, %d\n", res->width, res->height);

            auto viewPort = camera->getViewport();

            auto resolution = camera->getResolution();

            Rect4 vieport = Rect4(
                (int)(viewPort->x * (float)resolution->width), (int)(viewPort->y * (float)resolution->height), 
                (int)(viewPort->width * (float)resolution->width), (int)(viewPort->height * (float)resolution->height)
            );
            mRenderer->setViewport(&vieport);

            auto bgcolor = camera->getBackgroundColor();

            mRenderer->clear(FRAMEBUFFER_COLOR | FRAMEBUFFER_DEPTH, bgcolor, 0.0f, 0);

            for(
                auto iteRenderer = (*ite)->getOpaqueDistanceSortedList()->begin() ;
                iteRenderer != (*ite)->getOpaqueDistanceSortedList()->end();
                iteRenderer++
                )
            {
                (*iteRenderer)->render(mRenderer, cameraFunc);
            }

            for(
                auto iteRenderer = (*ite)->getNotOpaqueDistanceSortedList()->begin() ;
                iteRenderer != (*ite)->getNotOpaqueDistanceSortedList()->end();
                iteRenderer++
                )
            {
                (*iteRenderer)->render(mRenderer, cameraFunc);
            }

            mApplication->getMainGraphicsContext()->release();
        }

        mApplication->swapBuffers(mApplication->getMainGraphicsContext());

        //Clear RenderLists
        for(auto ite = mRenderLists.begin() ; ite != mRenderLists.end() ; ite++)
        {
            SAFE_DELETE((*ite));
        }
        mRenderLists.clear();
    }

}; //namespace S3D