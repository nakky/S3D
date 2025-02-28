#ifndef S3D_GAME_FUNCTION_ROTATINGFUNCTION_H
#define S3D_GAME_FUNCTION_ROTATINGFUNCTION_H

#include "S3D/Game/Function/EntityFunction.h"

namespace S3D
{
    class RotatingFunction : public EntityFunction
    {
    public:
        RotatingFunction()
        :EntityFunction(),
        mRotatingVelocity(0.0f)
        {
        }

        virtual ~RotatingFunction() {}

        constexpr virtual unsigned long getFunctionType() { return entityNameHash("S3D::RotatingFunction");}
         
        void setRotatingVelocity(float vel){ mRotatingVelocity = vel; }

    protected:

        virtual void onUpdate(const float delta);

    protected:
        float mRotatingVelocity;
    };

};

#endif //S3D_GAME_FUNCTION_ROTATINGFUNCTION_H

