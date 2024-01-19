#ifndef S3D_RESOURCE_H
#define S3D_RESOURCE_H

#include "S3D/Common.h"

namespace S3D
{
    enum ResourceType
    {
        RESOURCETYPE_ENTITY = 50000,
        RESOURCETYPE_MESH = 50001,
        RESOURCETYPE_MATERIAL = 50002
    };

    class Resource
    {
    public:
        Resource()
            : mUserData(NULL),
              mResourceId(0)
        {
        }

        virtual void init() {}
        virtual void cleanup() {}

        virtual const short getResourceType() = 0;

        void *getUserData() { return mUserData; }
        void setUserData(void *data) { mUserData = data; }

        unsigned int getResourceId() { return mResourceId; }
        void setResourceId(unsigned id) { mResourceId = id; }

    protected:
        void *mUserData;
        unsigned int mResourceId;
    };

}; // namespace S3D

#endif // S3D_RESOURCE_H
