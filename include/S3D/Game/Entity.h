#ifndef S3D_ENTITY_H
#define S3D_ENTITY_H

#include "S3D/Graphics/GeometricNode.h"
#include "S3D/Graphics/Material.h"
#include "S3D/Foundation/Resource.h"

namespace S3D
{
    class RenderList;
    class CameraFunction;
    class RendererFunction;
    class EntityFunction;

    class Entity 
    {
    public:
        Entity()
            : mIsActive(true),
              mNeedStateUpdate(true)
        {
            mNode.setEntity(this);
        }

        virtual ~Entity() {}

        virtual void init();
        virtual void cleanup();

        bool isActive() { return mIsActive; }
        bool activate()
        {
            mNeedStateUpdate = true;
            mIsActive = true;
        }
        bool deactivate()
        {
            mNeedStateUpdate = true;
            mIsActive = false;
        }

        bool isDirty();
        
        GeometricNode *getGeometricNode(){ return &mNode; }

        EntityFunction *getFunction(const unsigned int functionType);
        void getFunctions(const unsigned int functionType, std::list<EntityFunction*> *list);
        void getCameras(std::list<CameraFunction*> *list);
        void getRenderers(std::list<RendererFunction*> *list);

        const bool addFunction(EntityFunction *function);
        const bool removeFunction(EntityFunction *function);
        const bool removeFunction(const unsigned int functionType);
        const bool removeFunctions(const unsigned int functionType);

        virtual void functionFixedUpdate(const float delta);
        virtual bool functionUpdate(const float delta);

        virtual void functionLoad();
        virtual void functionRegisterGraphics();
        virtual void functionUnregisterGraphics();
        virtual void functionUnload();

    protected:
        bool mIsActive;

        GeometricNode mNode;
        bool mNeedStateUpdate;

        std::list<EntityFunction *> mFunctions;
    };
}

#endif // S3D_ENTITY_H
