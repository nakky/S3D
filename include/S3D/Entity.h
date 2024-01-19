#ifndef S3D_ENTITY_H
#define S3D_ENTITY_H

#include "S3D/Math/GeometricNode.h"
#include "S3D/Mesh/Mesh.h"
#include "S3D/Material.h"
#include "S3D/Function/EntityFunction.h"
#include "S3D/Resource.h"

namespace S3D
{
    enum OrderType
    {
        ORDERTYPE_DISANCE,
        ORDERTYPE_VALUE,
    };

    class RootEntity;
    class RenderList;

    class Entity : public Resource
    {
        friend class RootEntity;
        friend class RenderList;

    public:
        Entity()
            : Resource(),
              mIsActive(true),
              mIsActiveInTree(true),
              mNeedStateUpdate(true),
              mMesh(NULL),
              mMaterial(NULL),
              mPivot(0.0f, 0.0f, 0.0f),
              mOrderType(ORDERTYPE_DISANCE),
              mOrderValue(0)
        {
            mNode.setUserData(this);
        }

        virtual ~Entity() {}

        virtual const short getResourceType() { return RESOURCETYPE_ENTITY; }

        virtual void init();
        virtual void cleanup();

        bool isActive() { return mIsActive; }
        bool activate()
        {
            mNeedStateUpdate = true;
            mIsActive = true;
        }
        bool deactivate()
        {
            mNeedStateUpdate = true;
            mIsActive = false;
        }

        bool isActiveInTree() { return mIsActiveInTree; }

        Mesh *getMesh() { return mMesh; }
        void setMesh(Mesh *mesh) { mMesh = mesh; }

        Material *getMaterial() { return mMaterial; }
        void setMaterial(Material *mat) { mMaterial = mat; }

        OrderType getOrderType() { return mOrderType; }
        void setOrderType(OrderType type) { mOrderType = type; }

        short getOrderValue() { return mOrderValue; }
        void setOrderValue(short value) { mOrderValue = value; }

        virtual const bool needRender()
        {
            if (mMesh != NULL && mMesh->needRender())
                return true;
            else if (mMaterial != NULL && mMaterial->needRender())
                return true;
            return mNeedStateUpdate;
        }

        virtual void resetNeedRender()
        {
            if (mMesh != NULL)
                mMesh->resetNeedRender();
            if (mMaterial != NULL)
                mMaterial->resetNeedRender();
            mNeedStateUpdate = false;
        }

        virtual bool needUpdateState() { return mNeedStateUpdate; }
        virtual void updateState();

        void addChild(Entity *child);
        void removeChild(Entity *child);

        void setLocalPosition(const Vector3 &pos);
        const Vector3 *getLocalPosition() const { return mNode.getLocalPosition(); }
        void setLocalRotation(const Quaternion4 &rot);
        const Quaternion4 *getLocalOrientation() const { return mNode.getLocalOrientation(); }
        void setLocalScale(const Vector3 &scl);
        const Vector3 *getLocalScale() const { return mNode.getLocalScale(); }

        const Vector3 *getGlobalPosition() const { return mNode.getGlobalPosition(); }
        const Quaternion4 *getGlobalOrientation() const { return mNode.getGlobalOrientation(); }
        const Vector3 *getGlobalScale() const { return mNode.getGlobalScale(); }

        const Vector3 *getPivot() { return &mPivot; }
        const void setPivot(const Vector3 &pivot) { mPivot = pivot; }

        EntityFunction *getFunction(const unsigned int functionType);
        const bool addFunction(EntityFunction *function);
        const bool removeFunction(EntityFunction *function);
        const bool removeFunction(const unsigned int functionType);

        float getDiffFromCamera() { return mDiffFromCamera; }

        virtual void functionFixedUpdate(const float delta);
        virtual bool functionUpdate(const float delta);

        virtual void functionLoad();
        virtual void functionRegisterGraphics();
        virtual void functionUnregisterGraphics();
        virtual void functionUnload();

    protected:
        void setDiffFromCamera(const float diff) { mDiffFromCamera = diff; }

    protected:
        bool mIsActive;
        bool mIsActiveInTree;

        Vector3 mPivot;

        GeometricNode mNode;
        bool mNeedStateUpdate;

        Mesh *mMesh;
        Material *mMaterial;

        std::list<EntityFunction *> mFunctions;

        float mDiffFromCamera;

        OrderType mOrderType;

        short mOrderValue;
    };
}

#endif // S3D_ENTITY_H
