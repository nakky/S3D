
#include "S3D/Cluster.h"

namespace S3D
{
    void Cluster::init()
    {
        Entity::init();
    }

    void Cluster::cleanup()
    {
        for (auto ite = mEntityList.begin(); ite != mEntityList.end(); ite++)
        {
            (*ite)->cleanup();
            SAFE_DELETE(*ite);
        }
        mEntityList.clear();

        Entity::cleanup();
    }

}; // namespace S3D