

#include "S3D/Graphics/GraphicsSystem.h"

#include <math.h>

#include "S3D/Graphics/Math/MathematicsTypes.h"
#include "S3D/Graphics/Material.h"
#include "S3D/Graphics/ImageFactory.h"

namespace S3D
{
	CPU GraphicsSystem::mCPU;
	SIMDInstructionType GraphicsSystem::mSIMDInstructionType = SIMD_NONE;

    void GraphicsSystem::init()
    {
        mCPU.init();

#if defined SIMDARCH_SSE
		if (mCPU.isSSE2Enabled() && mCPU.isSSEEnabled())
			mSIMDInstructionType = SIMD_SSE;
#elif defined SIMDARCH_NEON
		if (mCPU.isNEONEnabled())
			mSIMDInstructionType = SIMD_NEON;
#endif
		ImageFactory::init();

		setSIMDInstructionType(mSIMDInstructionType);

		Material::defaultMaterial.init();
		//Material::defaultMaterial.setShader(new Shader)

    }

    void GraphicsSystem::cleanup()
    {
		ImageFactory::cleanup();

		Material::defaultMaterial.cleanup();
    }

    /****************************************/
	/*!
	 @brief	Set SIMD instruction type
	 @note	static

	 @author Naoto Nakamura
	 @date	Mar. 30, 2009
	 */
	/****************************************/
	void GraphicsSystem::setSIMDInstructionType(const SIMDInstructionType type)
	{

		switch (type)
		{
		case SIMD_NONE:
		{
			// Matrix33
			_addMatrix33Matrix33 = _addMatrix33Matrix33Usual;
			_subtractMatrix33Matrix33 = _subtractMatrix33Matrix33Usual;
			_multiplyMatrix33Matrix33 = _multiplyMatrix33Matrix33Usual;
			_multiplyMatrix33Vector2 = _multiplyMatrix33Vector2Usual;
			_multiplyMatrix33Vector3 = _multiplyMatrix33Vector3Usual;
			_multiplyMatrix33Float = _multiplyMatrix33FloatUsual;
			_divideMatrix33Float = _divideMatrix33FloatUsual;

			_transposeMatrix33 = _transposeMatrix33Usual;

			// Matrix44
			_addMatrix44Matrix44 = _addMatrix44Matrix44Usual;
			_subtractMatrix44Matrix44 = _subtractMatrix44Matrix44Usual;
			_multiplyMatrix44Matrix44 = _multiplyMatrix44Matrix44Usual;
			_multiplyMatrix44Vector3 = _multiplyMatrix44Vector3Usual;
			_multiplyMatrix44Vector4 = _multiplyMatrix44Vector4Usual;
			_multiplyMatrix44Float = _multiplyMatrix44FloatUsual;
			_divideMatrix44Float = _divideMatrix44FloatUsual;

			_transposeMatrix44 = _transposeMatrix44Usual;
		}
		break;

#if defined SIMDARCH_SSE
		case SIMD_SSE:
		{
			// Matrix33
			_addMatrix33Matrix33 = _addMatrix33Matrix33SSE;
			_subtractMatrix33Matrix33 = _subtractMatrix33Matrix33SSE;
			_multiplyMatrix33Matrix33 = _multiplyMatrix33Matrix33SSE;
			_multiplyMatrix33Vector2 = _multiplyMatrix33Vector2SSE;
			_multiplyMatrix33Vector3 = _multiplyMatrix33Vector3SSE;
			_multiplyMatrix33Float = _multiplyMatrix33FloatSSE;
			_divideMatrix33Float = _divideMatrix33FloatSSE;

			_transposeMatrix33 = _transposeMatrix33SSE;

			// Matrix44
			_addMatrix44Matrix44 = _addMatrix44Matrix44SSE;
			_subtractMatrix44Matrix44 = _subtractMatrix44Matrix44SSE;
			_multiplyMatrix44Matrix44 = _multiplyMatrix44Matrix44SSE;
			_multiplyMatrix44Vector3 = _multiplyMatrix44Vector3SSE;
			_multiplyMatrix44Vector4 = _multiplyMatrix44Vector4SSE;
			_multiplyMatrix44Float = _multiplyMatrix44FloatSSE;
			_divideMatrix44Float = _divideMatrix44FloatSSE;

			_transposeMatrix44 = _transposeMatrix44SSE;
		}
		break;
		case SIMD_VMX:
		{
		}
		break;
		case SIMD_VMX128:
		{
		}
		break;
#endif // SIMDARCH_SSE

#if defined SIMDARCH_NEON
		case SIMD_NEON:
		{
			// Matrix33
			_addMatrix33Matrix33 = _addMatrix33Matrix33NEON;
			_subtractMatrix33Matrix33 = _subtractMatrix33Matrix33NEON;
			_multiplyMatrix33Matrix33 = _multiplyMatrix33Matrix33NEON;
			_multiplyMatrix33Vector2 = _multiplyMatrix33Vector2NEON;
			_multiplyMatrix33Vector3 = _multiplyMatrix33Vector3NEON;
			_multiplyMatrix33Float = _multiplyMatrix33FloatNEON;
			_divideMatrix33Float = _divideMatrix33FloatNEON;

			_transposeMatrix33 = _transposeMatrix33NEON;

			// Matrix44
			_addMatrix44Matrix44 = _addMatrix44Matrix44NEON;
			_subtractMatrix44Matrix44 = _subtractMatrix44Matrix44NEON;
			_multiplyMatrix44Matrix44 = _multiplyMatrix44Matrix44NEON;
			_multiplyMatrix44Vector3 = _multiplyMatrix44Vector3NEON;
			_multiplyMatrix44Vector4 = _multiplyMatrix44Vector4NEON;
			_multiplyMatrix44Float = _multiplyMatrix44FloatNEON;
			_divideMatrix44Float = _divideMatrix44FloatNEON;

			_transposeMatrix44 = _transposeMatrix44NEON;
		}
		break;
#endif // SIMDARCH_NEON
		}
	}

} //namespace S3D