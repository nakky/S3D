
#include "S3D/Game/RenderList.h"

#include "S3D/Graphics/Mesh.h"
#include "S3D/Graphics/Material.h"

#include "S3D/Game/Function/CameraFunction.h"
#include "S3D/Game/Function/RendererFunction.h"

#include "S3D/Game/Entity.h"

namespace S3D
{
    bool distanceLess(RendererFunction *&v1, RendererFunction *&v2)
    {
        return v1->getDiffFromCamera() < v2->getDiffFromCamera();
    }

    bool distanceGreater(RendererFunction *&v1, RendererFunction *&v2)
    {
        return v1->getDiffFromCamera() > v2->getDiffFromCamera();
    }

    bool orderValueLess(RendererFunction *&v1, RendererFunction *&v2)
    {
        return v1->getOrderValue() < v2->getOrderValue();
    }

    bool orderValueGreater(RendererFunction *&v1, RendererFunction *&v2)
    {
        return v1->getOrderValue() > v2->getOrderValue();
    }

    void RenderList::sortByDistance()
    {
        Vector3 cameraPosition = *(mCameraFunction->getEntity()->getGeometricNode()->getGlobalPosition());

        Material *mat;

        mOpaqueDistanceSortedList.clear();
        mNotOpaqueDistanceSortedList.clear();

        float diff;

        for (auto ite = mRegisteredList.begin(); ite != mRegisteredList.end(); ite++)
        {
            mat = (*ite)->getMaterial();
            if(mat == NULL) mat = &Material::defaultMaterial;

            if (mat->isOpaque())
            {
                mOpaqueDistanceSortedList.push_back((*ite));
            }
            else
            {
                mNotOpaqueDistanceSortedList.push_back((*ite));
            }
            diff = (*((*ite)->getEntity()->getGeometricNode()->getGlobalPosition()) - cameraPosition).length();
            (*ite)->setDiffFromCamera(diff);
        }

        mOpaqueDistanceSortedList.sort(distanceLess);
        mNotOpaqueDistanceSortedList.sort(distanceGreater);
    }

    void RenderList::sortByValue()
    {
        Material *mat;

        mOpaqueValueSortedList.clear();
        mNotOpaqueValueSortedList.clear();

        float diff;

        for (auto ite = mRegisteredList.begin(); ite != mRegisteredList.end(); ite++)
        {
            mat = (*ite)->getMaterial();
            if(mat == NULL) mat = &Material::defaultMaterial;

            if (mat->isOpaque())
            {
                mOpaqueValueSortedList.push_back((*ite));
            }
            else
            {
                mNotOpaqueValueSortedList.push_back((*ite));
            }
        }

        mOpaqueValueSortedList.sort(orderValueLess);
        mNotOpaqueValueSortedList.sort(orderValueGreater);
    }

}; // namespace S3D
