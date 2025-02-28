#ifndef S3D_FUNCTION_ENTITYFUNCTION_H
#define S3D_FUNCTION_ENTITYFUNCTION_H

#include "S3D/Common.h"

#include <iostream>
#include <string>

#include "S3D/Game/Entity.h"

namespace S3D
{
    constexpr unsigned long entityNameHash(const std::string_view& str) {
        unsigned long hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash;
    }

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
              mEntity(NULL),
              mIsDirty(true)
        {
        }

        virtual ~EntityFunction() {}

    public:
        constexpr virtual unsigned long getFunctionType() = 0;

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

        virtual const bool isCamera() const { return false; }
        virtual const bool isRenderer() const { return false; }

        bool isDirty() const { return mIsDirty; }
		void resetDirty() { mIsDirty = false; }
    
    protected:
        Entity *mEntity;

    private:
        void added(Entity *entity);
        void removed();
        void cleanuped();
        void updateState();

        EntityFunctionState mState;

        bool mIsDirty;
        bool mIsEnable;
    };
};

#endif // S3D_FUNCTION_ENTITYFUNCTION_H