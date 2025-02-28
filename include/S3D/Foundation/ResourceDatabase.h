#ifndef S3D_RESOURCEDATABASE_H
#define S3D_RESOURCEDATABASE_H

#include <map>

#include "S3D/Common.h"

#include "S3D/Foundation/Lock.h"
#include "S3D/Foundation/Resource.h"

namespace S3D
{
    class ResourceDatabase
    {
        public:
        ResourceDatabase()
        :mMaxId(DEFAULT_MAX_ID)
        {}

        void init();
        void cleanup();

        void clear();

        Resource *getResource(unsigned int id);
        unsigned int registerResource(Resource *resource);
        Resource *unregisterResource(unsigned int id);

        std::map<unsigned int, Resource*>::iterator begin(){return mResourceMap.begin();}
        std::map<unsigned int, Resource*>::iterator end(){return mResourceMap.end();}
    
        private:
        unsigned int lookupBlankId();

        private:
        std::map<unsigned int, Resource*> mResourceMap;

        Mutex *mLocker;

        int mMaxId;

        static const int DEFAULT_MAX_ID = 4096;
    }; 

};//namespace S3D


#endif //S3D_RESOURCEDATABASE_H