/******************************************************************/
/*!
	@file	Light.h
	@brief	Light class
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 30, 2009
*/
/******************************************************************/

#ifndef S3D_LIGHT_H
#define S3D_LIGHT_H

#include "S3D/Common.h"
#include "S3D/Graphics/Math/MathematicsTypes.h"

namespace S3D{

    //////////////////////////////////////////////////////
    //				forward declarations				//
    //////////////////////////////////////////////////////
    //implemented
    class Light;
    
    enum LightType
    {
        LIGHT_DIRECTIONAL,
        LIGHT_SPOT,
        LIGHT_POINT
    };


    //////////////////////////////////////////////////////
    //				class declarations					//
    //////////////////////////////////////////////////////
    /****************************************/
    /*!
        @class	Light
        @brief	Light class
        @note
        @author	Naoto Nakamura
        @date	Mar. 30, 2009
    */
    /****************************************/
    class Light
    {

    public:
        Light(const LightType type)
        :mLightType(type),
        mLightColor(Color4::white),
        mSpotInnerConeAngle(10.0f),
        mSpotOuterConeAngle(30.0f),
        mConstantAttenuation(0.1f),
        mLinearAttenuation(0.01f),
        mQuadraticAttenuation(0.01f)
        {}

    public:

        void setLightType(const LightType type) { mLightType = type; }
        LightType getLightType() const { return mLightType; }
        
        void setColor(const Color4 &color){ mLightColor = color;}
        const Color4* getColor() const {return &mLightColor;}
        
        void setSpotInnerConeAngle(const float angle){ mSpotInnerConeAngle = angle;}
        float getSpotInnerConeAngle() const {return mSpotInnerConeAngle;}
        
        void setSpotOuterConeAngle(const float angle){ mSpotOuterConeAngle = angle;}
        float getSpotOuterConeAngle() const {return mSpotOuterConeAngle;}
        
        void setAttenuation(const float constant, const float linear = 0.0f, const float quadratic = 0.0f)
        {mConstantAttenuation = constant; mLinearAttenuation = linear; mQuadraticAttenuation = quadratic;}
        
        void getAttenuation(float *constant, float *linear, float *quadratic) const
        {*constant = mConstantAttenuation; *linear = mLinearAttenuation; *quadratic = mQuadraticAttenuation;}
    
    protected:
        LightType mLightType;
        
        Color4 mLightColor;
        
        float mSpotInnerConeAngle;
        float mSpotOuterConeAngle;
        
        float mConstantAttenuation;
        float mLinearAttenuation;
        float mQuadraticAttenuation;
    
    };

};// namespace S3D

#endif //VS_GRAPHICS_LIGHT_H

