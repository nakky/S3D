
#include "S3D/Foundation/ResourceDatabase.h"

namespace S3D{

    void ResourceDatabase::init()
    {
        mLocker = new Mutex();
    }

    void ResourceDatabase::cleanup()
    {
        clear();
        SAFE_DELETE(mLocker);
    }

    void ResourceDatabase::clear()
    {
        mLocker->lock();
        for(auto ite = mResourceMap.begin() ; ite != mResourceMap.end() ; ite++)
        {
            (*ite).second->cleanup();
            SAFE_DELETE((*ite).second);
        }
        mResourceMap.clear();
        mLocker->unlock();
    }

    Resource *ResourceDatabase::getResource(unsigned int id)
    {
        if(id == 0 || id >= mMaxId) return NULL;
        mLocker->lock();
        if(mResourceMap.count(id)){
            mLocker->unlock();
            return mResourceMap[id];
        } else {
            mLocker->unlock();
            return NULL;
        }
    }

    unsigned int ResourceDatabase::registerResource(Resource *resource)
    {
        mLocker->lock();
        if(mMaxId <= mResourceMap.size()) mMaxId += 1024;

        unsigned int id = lookupBlankId();
        if(id != 0){
            mResourceMap.insert(std::make_pair(id, resource));
        }
        mLocker->unlock();

        return id;
    }

    Resource *ResourceDatabase::unregisterResource(unsigned int id)
    {
        if(id == 0 || id >= mMaxId) return NULL;
        Resource *res = NULL;
        mLocker->lock();
        if(mResourceMap.count(id)){
            res = mResourceMap[id];
            mResourceMap.erase(id);
            mLocker->unlock();
            return res;
        }else {
            mLocker->unlock();
            return NULL;
        }
    }

    unsigned int ResourceDatabase::lookupBlankId()
    {
        unsigned int rid = rand() % (mMaxId - 1) + 1;
        int num = 0;
        while(true){
            if(!mResourceMap.count(rid)) return rid;
            rid++;
            num++;
            if(rid == mMaxId) rid = 1;
            if(num >= mMaxId) return 0;
        }
    }

}; //namespace S3D