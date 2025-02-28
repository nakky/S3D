#include "S3D/Game/Function/RotatingFunction.h"

namespace S3D
{

    void RotatingFunction::onUpdate(const float delta)
    {
        Quaternion4 diff;
        auto orig = getEntity()->getGeometricNode()->getLocalOrientation();
        diff.setUnitQuaternion();
        diff.convert(Vector3(0.0f, 1.0f, 0.0), (mRotatingVelocity * delta) / 360.0f * PIF);
        getEntity()->getGeometricNode()->setLocalOrientation(*orig * diff);
    }

}; //namespace S3D