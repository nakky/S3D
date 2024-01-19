
#include "S3D/RenderList.h"

#include "S3D/Mesh/Mesh.h"
#include "S3D/Material.h"
#include "S3D/Entity.h"

namespace S3D
{
    bool distanceLess(Entity *&v1, Entity *&v2)
    {
        return v1->getDiffFromCamera() < v2->getDiffFromCamera();
    }

    bool distanceGreater(Entity *&v1, Entity *&v2)
    {
        return v1->getDiffFromCamera() > v2->getDiffFromCamera();
    }

    bool orderValueLess(Entity *&v1, Entity *&v2)
    {
        return v1->getOrderValue() < v2->getOrderValue();
    }

    bool orderValueGreater(Entity *&v1, Entity *&v2)
    {
        return v1->getOrderValue() > v2->getOrderValue();
    }

    void RenderList::sortByDistance(const Vector3 &cameraPosition)
    {
        Mesh *mesh;
        Material *mat;

        mOpaqueDistanceSortedList.clear();
        mNotOpaqueDistanceSortedList.clear();

        float diff;

        for (auto ite = mRegisteredList.begin(); ite != mRegisteredList.end(); ite++)
        {
            mesh = (*ite)->getMesh();
            mat = (*ite)->getMaterial();
            if (mesh == NULL || mat == NULL)
                continue;

            switch (((*ite)->getOrderType()))
            {
            case ORDERTYPE_DISANCE:
            {
                if (mat->isOpaque())
                {
                    mOpaqueDistanceSortedList.push_back((*ite));
                }
                else
                {
                    mNotOpaqueDistanceSortedList.push_back((*ite));
                }
                diff = (*((*ite)->getGlobalPosition()) - cameraPosition).length();
                (*ite)->setDiffFromCamera(diff);
            }
            break;
            }
        }

        mOpaqueDistanceSortedList.sort(distanceLess);
        mNotOpaqueDistanceSortedList.sort(distanceGreater);
    }

    void RenderList::sortByValue()
    {
        Mesh *mesh;
        Material *mat;

        mOpaqueValueSortedList.clear();
        mNotOpaqueValueSortedList.clear();

        float diff;

        for (auto ite = mRegisteredList.begin(); ite != mRegisteredList.end(); ite++)
        {
            mesh = (*ite)->getMesh();
            mat = (*ite)->getMaterial();
            if (mesh == NULL || mat == NULL)
                continue;

            switch (((*ite)->getOrderType()))
            {
            case ORDERTYPE_VALUE:
            {
                if (mat->isOpaque())
                {
                    mOpaqueValueSortedList.push_back((*ite));
                }
                else
                {
                    mNotOpaqueValueSortedList.push_back((*ite));
                }
            }
            break;
            }
        }

        mOpaqueValueSortedList.sort(orderValueLess);
        mNotOpaqueValueSortedList.sort(orderValueGreater);
    }

}; // namespace S3D
