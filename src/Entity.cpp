

#include "S3D/Entity.h"

namespace S3D
{
    void Entity::init()
    {
        Resource::init();
        mNode.init();
    }

    void Entity::cleanup()
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            (*ite)->cleanuped();
            SAFE_DELETE((*ite));
        }
        mFunctions.clear();

        mNode.cleanup();

        Resource::cleanup();
    }

    void Entity::addChild(Entity *child)
    {
        mNode.setRelationToChild(&(child->mNode));
    }

    void Entity::removeChild(Entity *child)
    {
        mNode.cutOffRelationToChild(&(child->mNode));
    }

    void Entity::setLocalPosition(const Vector3 &pos)
    {
        mNode.setLocalPosition(pos);
        mNeedStateUpdate = true;
    }

    void Entity::setLocalRotation(const Quaternion4 &rot)
    {
        mNode.setLocalOrientation(rot);
        mNeedStateUpdate = true;
    }

    void Entity::setLocalScale(const Vector3 &scl)
    {
        mNode.setLocalScale(scl);
        mNeedStateUpdate = true;
    }

    void Entity::updateState()
    {
        mNode.calculateGlobalState();
    }

    EntityFunction *Entity::getFunction(const unsigned int functionType)
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            if ((*ite)->getFunctionType() == functionType)
                return (*ite);
        }
        return NULL;
    }

    const bool Entity::addFunction(EntityFunction *function)
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            if ((*ite)->getFunctionType() == function->getFunctionType())
                return false;
        }

        mFunctions.push_back(function);
        function->added(this);
        return true;
    }

    const bool Entity::removeFunction(EntityFunction *function)
    {
        mFunctions.remove(function);
        function->removed();
        return true;
    }

    const bool Entity::removeFunction(const unsigned int functionType)
    {
        auto func = getFunction(functionType);
        if (func == NULL)
            return false;
        return removeFunction(func);
    }

    void Entity::functionFixedUpdate(const float delta)
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            if ((*ite)->isEnable())
            {
                (*ite)->updateState();
                (*ite)->onFixedUpdate(delta);
            }
        }
    }

    bool Entity::functionUpdate(const float delta)
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            if ((*ite)->isEnable())
                (*ite)->onUpdate(delta);
        }
        return true;
    }

    void Entity::functionLoad()
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            (*ite)->onLoad();
        }
    }

    void Entity::functionRegisterGraphics()
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            (*ite)->onRegisterGraphics();
        }
    }

    void Entity::functionUnregisterGraphics()
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            (*ite)->onUnregisterGraphics();
        }
    }

    void Entity::functionUnload()
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            (*ite)->onUnload();
        }
    }

}; // namespace S3D