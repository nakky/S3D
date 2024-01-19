
#include "S3D/RootEntity.h"

namespace S3D
{
    void RootEntity::updateActiveState()
    {
        updateActiveStateInternal(this, true);
    }

    void RootEntity::updateActiveStateInternal(Entity *target, bool parentIsActive)
    {
        target->mIsActiveInTree = target->isActive() && parentIsActive;

        std::list<GeometricNode *> &children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            updateActiveStateInternal(next, target->isActiveInTree());
        }
    }

    void RootEntity::tryUpdate()
    {
        tryUpdateInternal(this, false);
    }

    void RootEntity::tryUpdateInternal(Entity *target, bool parentUpdate)
    {
        bool needUpdate = parentUpdate || target->needUpdateState();
        if (target->isActiveInTree() && needUpdate)
        {
            target->updateState();
        }

        std::list<GeometricNode *> &children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            tryUpdateInternal(next, needUpdate);
        }
    }

    const bool RootEntity::needRender()
    {
        if (Entity::needRender())
            return true;

        std::list<GeometricNode *> &children = mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            bool ret = needRenderInternal(next);
            if (ret)
                return true;
        }
        return false;
    }

    const bool RootEntity::needRenderInternal(Entity *target)
    {
        if (target->needRender())
            return true;
        std::list<GeometricNode *> &children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            bool ret = needRenderInternal(next);
            if (ret)
                return true;
        }
        return false;
    }

    void RootEntity::resetNeedRender()
    {
        Entity::resetNeedRender();

        std::list<GeometricNode *> &children = mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            resetNeedRenderInternal(next);
        }
    }

    void RootEntity::resetNeedRenderInternal(Entity *target)
    {
        target->resetNeedRender();
        std::list<GeometricNode *> &children = target->mNode.getChildList();
        for (auto ite = children.begin(); ite != children.end(); ite++)
        {
            Entity *next = (Entity *)(*ite)->getUserData();
            resetNeedRenderInternal(next);
        }
    }

}; // namespace S3D