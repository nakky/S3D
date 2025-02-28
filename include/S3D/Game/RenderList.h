/******************************************************************/
/*!
    @file	RenderList.h
    @brief	Render target container
    @note
    @todo
    @bug

    @author	Naoto Nakamura
    @date	Mar. 10, 2020
*/
/******************************************************************/

#ifndef S3D_RENDERLIST_H
#define S3D_RENDERLIST_H

#include "S3D/Common.h"

#include "S3D/Graphics/Math/MathematicsTypes.h"
#include "S3D/Game/Entity.h"

#include <list>

namespace S3D
{
    class Entity;
    class CameraFunction;
    class RendererFunction;
    
    class RenderList
    {
    public:
        RenderList(CameraFunction *camera)
        :mCameraFunction(camera)
        {}

        void add(RendererFunction *renderer) { mRegisteredList.push_back(renderer); }
        void remove(RendererFunction *renderer) { mRegisteredList.remove(renderer); }

        void sortByDistance();
        void sortByValue();

        CameraFunction *getCameraFunction() { return mCameraFunction; }

        const std::list<RendererFunction *> *getOpaqueDistanceSortedList() const { return &mOpaqueDistanceSortedList; }
        const std::list<RendererFunction *> *getNotOpaqueDistanceSortedList() const { return &mNotOpaqueDistanceSortedList; }
        const std::list<RendererFunction *> *getOpaqueValueSortedList() const { return &mOpaqueValueSortedList; }
        const std::list<RendererFunction *> *getNotOpaqueValueSortedList() const { return &mNotOpaqueValueSortedList; }

    protected:
        CameraFunction *mCameraFunction;

        std::list<RendererFunction *> mRegisteredList;

        std::list<RendererFunction *> mOpaqueDistanceSortedList;
        std::list<RendererFunction *> mNotOpaqueDistanceSortedList;
        std::list<RendererFunction *> mOpaqueValueSortedList;
        std::list<RendererFunction *> mNotOpaqueValueSortedList;
    };

}; // namespace S3D

#endif // S3D_RENDERLIST_H
