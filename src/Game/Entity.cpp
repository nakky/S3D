

#include "S3D/Game/Entity.h"

#include "S3D/Game/Function/CameraFunction.h"
#include "S3D/Game/Function/RendererFunction.h"


namespace S3D
{
    void Entity::init()
    {
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
    }
    
    bool Entity::isDirty()
    {
        if(mNode.isDirty()) return true;
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            if((*ite)->isDirty()) return true;
        }
        return false;
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

    void Entity::getFunctions(const unsigned int functionType, std::list<EntityFunction*> *list)
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            if ((*ite)->getFunctionType() == functionType)list->push_back(*ite);
        }
    }

    void Entity::getCameras(std::list<CameraFunction*> *list)
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            if ((*ite)->isCamera())list->push_back((CameraFunction*)*ite);
        }
    }

    void Entity::getRenderers(std::list<RendererFunction*> *list)
    {
        for (auto ite = mFunctions.begin(); ite != mFunctions.end(); ite++)
        {
            if ((*ite)->isRenderer())list->push_back((RendererFunction*)*ite);
        }
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

    const bool Entity::removeFunctions(const unsigned int functionType)
    {
        bool ret = false;
        for (auto ite = mFunctions.begin() ; ite != mFunctions.end() ; )
        {
            if ((*ite)->getFunctionType() == functionType)
            {
                mFunctions.erase(ite);
                ret = true;
            }
            else ite++;
        }
        return ret;
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