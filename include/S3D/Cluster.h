#ifndef S3D_CLUSTER_H
#define S3D_CLUSTER_H

#include "S3D/Entity.h"
#include <list>

namespace S3D
{
    class Cluster : public Entity
    {
    public:
        Cluster()
            : Entity()
        {
        }

        virtual ~Cluster() {}

        virtual void init();
        virtual void cleanup();

        const std::list<Entity *> &getEntityList() { return mEntityList; }

        virtual void addEntity(Entity *entity)
        {
            mEntityList.push_back(entity);
        }

        virtual void removeEntity(Entity *entity)
        {
            mEntityList.remove(entity);
        }

    protected:
        std::list<Entity *> mEntityList;
    };
}

#endif // S3D_CLUSTER_H
