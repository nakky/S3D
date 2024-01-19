
#include "S3D/Function/EntityFunction.h"

#include "S3D/Entity.h"

namespace S3D
{
    void EntityFunction::added(Entity *entity)
    {
        mEntity = entity;
        switch (mState)
        {
        case FUNCTIONSTATE_LOADED:
        {
            onInitialize();
            mState = FUNCTIONSTATE_INITIALIZED;
            if (mIsEnable)
                onEnable();
            else
                onDisable();
            if (mEntity->isActive())
                onActivate();
            else
                onDeactivate();
        }
        break;
        case FUNCTIONSTATE_INITIALIZED:
        {
        }
        break;
        case FUNCTIONSTATE_STARTED:
        {
        }
        break;
        case FUNCTIONSTATE_TERMINATED:
        {
        }
        break;

        default:
            break;
        }
    }

    void EntityFunction::removed()
    {
        mEntity = NULL;
    }

    void EntityFunction::cleanuped()
    {
        switch (mState)
        {
        case FUNCTIONSTATE_LOADED:
        {
            onInitialize();
            mState = FUNCTIONSTATE_INITIALIZED;
            if (mIsEnable)
                onEnable();
            else
                onDisable();
            if (mEntity->isActive())
                onActivate();
            else
                onDeactivate();
        }
        break;
        case FUNCTIONSTATE_INITIALIZED:
        {
        }
        break;
        case FUNCTIONSTATE_STARTED:
        {
        }
        break;
        case FUNCTIONSTATE_TERMINATED:
        {
        }
        break;

        default:
            break;
        }

        switch (mState)
        {
        case FUNCTIONSTATE_LOADED:
        {
        }
        break;
        case FUNCTIONSTATE_INITIALIZED:
        {
        }
        break;
        case FUNCTIONSTATE_STARTED:
        {
            onTerminate();
            mState = FUNCTIONSTATE_TERMINATED;
        }
        break;
        case FUNCTIONSTATE_TERMINATED:
        {
        }
        break;

        default:
            break;
        }
        mEntity = NULL;
    }

    void EntityFunction::updateState()
    {
        switch (mState)
        {
        case FUNCTIONSTATE_LOADED:
        {
        }
        break;
        case FUNCTIONSTATE_INITIALIZED:
        {
            onStart();
            mState = FUNCTIONSTATE_STARTED;
        }
        break;
        case FUNCTIONSTATE_STARTED:
        {
        }
        break;
        case FUNCTIONSTATE_TERMINATED:
        {
        }
        break;

        default:
            break;
        }
    }

}; // namespace S3D