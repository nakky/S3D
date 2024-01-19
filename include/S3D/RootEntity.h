#ifndef S3D_ROOTENTITY_H
#define S3D_ROOTENTITY_H

#include "S3D/Entity.h"
#include <list>

namespace S3D
{
    class RootEntity : public Entity
    {
    public:
        RootEntity()
            : Entity()
        {
        }

        virtual ~RootEntity() {}

        virtual const bool needRender();
        virtual void resetNeedRender();

        void updateActiveState();
        void tryUpdate();

    private:
        virtual const bool needRenderInternal(Entity *target);
        virtual void resetNeedRenderInternal(Entity *target);

        void updateActiveStateInternal(Entity *target, bool parentIsActive);
        void tryUpdateInternal(Entity *target, bool parentUpdate);
    };
}

#endif // S3D_ROOTENTITY_H
