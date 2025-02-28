#ifndef S3D_GAME_FUNCTION_MESHFUNCTION_H
#define S3D_GAME_FUNCTION_MESHFUNCTION_H

#include "S3D/Game/Function/EntityFunction.h"

namespace S3D
{
    class Mesh;

    class MeshFunction : public EntityFunction
    {
    public:
        MeshFunction()
        :EntityFunction()
        {
        }

        virtual ~MeshFunction() {}

        constexpr virtual unsigned long getFunctionType() { return entityNameHash("S3D::MeshFunction");}

        void setMesh(Mesh *mesh) { mMesh = mesh; }
        Mesh *getMesh() { return mMesh; }
         
    protected:
        Mesh *mMesh;
    };

};

#endif //S3D_GAME_FUNCTION_MESHFUNCTION_H

