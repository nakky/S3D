#ifndef S3D_FUNCTION_ENTITYFUNCTION_H
#define S3D_FUNCTION_ENTITYFUNCTION_H

#include "S3D/Common.h"

namespace S3D
{
    class Entity;

    enum EntityFunctionState
    {
        FUNCTIONSTATE_LOADED,
        FUNCTIONSTATE_INITIALIZED,
        FUNCTIONSTATE_STARTED,
        FUNCTIONSTATE_TERMINATED
    };

    class EntityFunction
    {
        friend class Entity;

    public:
        EntityFunction()
            : mState(FUNCTIONSTATE_LOADED),
              mIsEnable(true),
              mEntity(NULL)
        {
        }

        virtual ~EntityFunction() {}

    public:
        virtual unsigned int getFunctionType() = 0;

        Entity *getEntity() { return mEntity; }
        EntityFunctionState getState() { return mState; }

        bool isEnable() { return mIsEnable; }
        void enable()
        {
            bool prev = mIsEnable;
            mIsEnable = true;
            if (!prev)
                onEnable();
        }
        void disable()
        {
            bool prev = mIsEnable;
            mIsEnable = false;
            if (prev)
                onDisable();
        }

    protected:
        Entity *mEntity;

        virtual void onInitialize() {}
        virtual void onTerminate() {}

        virtual void onLoad() {}
        virtual void onRegisterGraphics() {}
        virtual void onUnload() {}
        virtual void onUnregisterGraphics() {}

        virtual void onStart() {}

        virtual void onActivate() {}
        virtual void onDeactivate() {}

        virtual void onFixedUpdate(const float delta) {}
        virtual void onUpdate(const float delta) {}

        virtual void onEnable() {}
        virtual void onDisable() {}

    private:
        void added(Entity *entity);
        void removed();
        void cleanuped();
        void updateState();

        EntityFunctionState mState;

        bool mIsEnable;
    };
};

#endif // S3D_FUNCTION_ENTITYFUNCTION_H