
#include "S3D/Graphics/Math/MathematicsTypes.h"

namespace S3D
{
#define VQ_SHUFFLE(z, y, x, w) (((z) << 6) | ((y) << 4) | ((x) << 2) | (w))

#define vshuffleq_f32(a, b, imm8)							\
		vsetq_lane_f32(										\
			vgetq_lane_f32(b, ((imm8) >> 6) & 0x3),			\
			vsetq_lane_f32( 								\
				vgetq_lane_f32(b, ((imm8) >> 4) & 0x3),		\
				vsetq_lane_f32(								\
					vgetq_lane_f32(a, ((imm8) >> 2) & 0x3), \
					vmovq_n_f32(							\
						vgetq_lane_f32(a, (imm8) & (0x3))), 1), 2) , 3)
	

	//////////////////////////////////////////////////////////
	//						Matrix33						//
	//////////////////////////////////////////////////////////
	void (*_addMatrix33Matrix33)(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2) = _addMatrix33Matrix33Usual;
	void (*_subtractMatrix33Matrix33)(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2) = _subtractMatrix33Matrix33Usual;
	void (*_multiplyMatrix33Matrix33)(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2) = _multiplyMatrix33Matrix33Usual;
	void (*_multiplyMatrix33Vector2)(Vector2 &vOut, const Matrix33 &m, const Vector2 &v) = _multiplyMatrix33Vector2Usual;
	void (*_multiplyMatrix33Vector3)(Vector3 &vOut, const Matrix33 &m, const Vector3 &v) = _multiplyMatrix33Vector3Usual;
	void (*_multiplyMatrix33Float)(Matrix33 &mOut, const Matrix33 &m, const float f) = _multiplyMatrix33FloatUsual;
	void (*_divideMatrix33Float)(Matrix33 &mOut, const Matrix33 &m, const float f) = _divideMatrix33FloatUsual;

	void (*_transposeMatrix33)(Matrix33 &mOut, const Matrix33 &m) = _transposeMatrix33Usual;

	//////////////////////////////////////////////////
	//					Usual						//
	//////////////////////////////////////////////////
	void _addMatrix33Matrix33Usual(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.m[0][0] = m1.m[0][0] + m2.m[0][0];
		mOut.m[1][0] = m1.m[1][0] + m2.m[1][0];
		mOut.m[2][0] = m1.m[2][0] + m2.m[2][0];

		mOut.m[0][1] = m1.m[0][1] + m2.m[0][1];
		mOut.m[1][1] = m1.m[1][1] + m2.m[1][1];
		mOut.m[2][1] = m1.m[2][1] + m2.m[2][1];

		mOut.m[0][2] = m1.m[0][2] + m2.m[0][2];
		mOut.m[1][2] = m1.m[1][2] + m2.m[1][2];
		mOut.m[2][2] = m1.m[2][2] + m2.m[2][2];
	}

	void _subtractMatrix33Matrix33Usual(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.m[0][0] = m1.m[0][0] - m2.m[0][0];
		mOut.m[1][0] = m1.m[1][0] - m2.m[1][0];
		mOut.m[2][0] = m1.m[2][0] - m2.m[2][0];

		mOut.m[0][1] = m1.m[0][1] - m2.m[0][1];
		mOut.m[1][1] = m1.m[1][1] - m2.m[1][1];
		mOut.m[2][1] = m1.m[2][1] - m2.m[2][1];

		mOut.m[0][2] = m1.m[0][2] - m2.m[0][2];
		mOut.m[1][2] = m1.m[1][2] - m2.m[1][2];
		mOut.m[2][2] = m1.m[2][2] - m2.m[2][2];
	}

	void _multiplyMatrix33Matrix33Usual(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[1][0] * m2.m[0][1] + m1.m[2][0] * m2.m[0][2];
		mOut.m[1][0] = m1.m[0][0] * m2.m[1][0] + m1.m[1][0] * m2.m[1][1] + m1.m[2][0] * m2.m[1][2];
		mOut.m[2][0] = m1.m[0][0] * m2.m[2][0] + m1.m[1][0] * m2.m[2][1] + m1.m[2][0] * m2.m[2][2];

		mOut.m[0][1] = m1.m[0][1] * m2.m[0][0] + m1.m[1][1] * m2.m[0][1] + m1.m[2][1] * m2.m[0][2];
		mOut.m[1][1] = m1.m[0][1] * m2.m[1][0] + m1.m[1][1] * m2.m[1][1] + m1.m[2][1] * m2.m[1][2];
		mOut.m[2][1] = m1.m[0][1] * m2.m[2][0] + m1.m[1][1] * m2.m[2][1] + m1.m[2][1] * m2.m[2][2];

		mOut.m[0][2] = m1.m[0][2] * m2.m[0][0] + m1.m[1][2] * m2.m[0][1] + m1.m[2][2] * m2.m[0][2];
		mOut.m[1][2] = m1.m[0][2] * m2.m[1][0] + m1.m[1][2] * m2.m[1][1] + m1.m[2][2] * m2.m[1][2];
		mOut.m[2][2] = m1.m[0][2] * m2.m[2][0] + m1.m[1][2] * m2.m[2][1] + m1.m[2][2] * m2.m[2][2];
	}

	void _multiplyMatrix33Vector2Usual(Vector2 &vOut, const Matrix33 &m, const Vector2 &v)
	{
		vOut.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * 1.0f;
		vOut.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * 1.0f;
	}

	void _multiplyMatrix33Vector3Usual(Vector3 &vOut, const Matrix33 &m, const Vector3 &v)
	{
		vOut.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z;
		vOut.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z;
		vOut.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z;
	}

	void _multiplyMatrix33FloatUsual(Matrix33 &mOut, const Matrix33 &m, const float f)
	{
		mOut.m[0][0] = m.m[0][0] * f;
		mOut.m[1][0] = m.m[1][0] * f;
		mOut.m[2][0] = m.m[2][0] * f;

		mOut.m[0][1] = m.m[0][1] * f;
		mOut.m[1][1] = m.m[1][1] * f;
		mOut.m[2][1] = m.m[2][1] * f;

		mOut.m[0][2] = m.m[0][2] * f;
		mOut.m[1][2] = m.m[1][2] * f;
		mOut.m[2][2] = m.m[2][2] * f;
	}

	void _divideMatrix33FloatUsual(Matrix33 &mOut, const Matrix33 &m, const float f)
	{
		mOut.m[0][0] = m.m[0][0] / f;
		mOut.m[1][0] = m.m[1][0] / f;
		mOut.m[2][0] = m.m[2][0] / f;

		mOut.m[0][1] = m.m[0][1] / f;
		mOut.m[1][1] = m.m[1][1] / f;
		mOut.m[2][1] = m.m[2][1] / f;

		mOut.m[0][2] = m.m[0][2] / f;
		mOut.m[1][2] = m.m[1][2] / f;
		mOut.m[2][2] = m.m[2][2] / f;
	}

	void _transposeMatrix33Usual(Matrix33 &mOut, const Matrix33 &m)
	{
		float buf;
		buf = m.m[1][0];
		mOut.m[1][0] = m.m[0][1];
		mOut.m[0][1] = buf;
		buf = m.m[2][0];
		mOut.m[2][0] = m.m[0][2];
		mOut.m[0][2] = buf;

		buf = m.m[2][1];
		mOut.m[2][1] = m.m[1][2];
		mOut.m[1][2] = buf;
	}

#if defined SIMDARCH_SSE
	//////////////////////////////////////////////////
	//					SSE							//
	//////////////////////////////////////////////////
	void _addMatrix33Matrix33SSE(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.row[0] = _mm_add_ps(m1.row[0], m2.row[0]);
		mOut.row[1] = _mm_add_ps(m1.row[1], m2.row[1]);
		mOut.row[2] = _mm_add_ps(m1.row[2], m2.row[2]);
	}

	void _subtractMatrix33Matrix33SSE(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.row[0] = _mm_sub_ps(m1.row[0], m2.row[0]);
		mOut.row[1] = _mm_sub_ps(m1.row[1], m2.row[1]);
		mOut.row[2] = _mm_sub_ps(m1.row[2], m2.row[2]);
	}

	void _multiplyMatrix33Matrix33SSE(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.row[0] = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(_mm_shuffle_ps(m1.row[0], m1.row[0], _MM_SHUFFLE(0, 0, 0, 0)), m2.row[0]),
				_mm_mul_ps(_mm_shuffle_ps(m1.row[0], m1.row[0], _MM_SHUFFLE(1, 1, 1, 1)), m2.row[1])),
			_mm_mul_ps(_mm_shuffle_ps(m1.row[0], m1.row[0], _MM_SHUFFLE(2, 2, 2, 2)), m2.row[2]));

		mOut.row[1] = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(_mm_shuffle_ps(m1.row[1], m1.row[1], _MM_SHUFFLE(0, 0, 0, 0)), m2.row[0]),
				_mm_mul_ps(_mm_shuffle_ps(m1.row[1], m1.row[1], _MM_SHUFFLE(1, 1, 1, 1)), m2.row[1])),
			_mm_mul_ps(_mm_shuffle_ps(m1.row[1], m1.row[1], _MM_SHUFFLE(2, 2, 2, 2)), m2.row[2]));

		mOut.row[2] = _mm_add_ps(
			_mm_add_ps(
				_mm_mul_ps(_mm_shuffle_ps(m1.row[2], m1.row[2], _MM_SHUFFLE(0, 0, 0, 0)), m2.row[0]),
				_mm_mul_ps(_mm_shuffle_ps(m1.row[2], m1.row[2], _MM_SHUFFLE(1, 1, 1, 1)), m2.row[1])),
			_mm_mul_ps(_mm_shuffle_ps(m1.row[2], m1.row[2], _MM_SHUFFLE(2, 2, 2, 2)), m2.row[2]));
	}

	void _multiplyMatrix33Vector2SSE(Vector2 &vOut, const Matrix33 &m, const Vector2 &v)
	{
		vOut.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * 1.0f;
		vOut.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * 1.0f;
	}

	void _multiplyMatrix33Vector3SSE(Vector3 &vOut, const Matrix33 &m, const Vector3 &v)
	{
		vOut.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z;
		vOut.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z;
		vOut.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z;
	}

	void _multiplyMatrix33FloatSSE(Matrix33 &mOut, const Matrix33 &m, const float f)
	{
		__m128 f128;

		f128 = _mm_load_ps1(&f);

		mOut.row[0] = _mm_mul_ps(m.row[0], f128);
		mOut.row[1] = _mm_mul_ps(m.row[1], f128);
		mOut.row[2] = _mm_mul_ps(m.row[2], f128);
	}

	void _divideMatrix33FloatSSE(Matrix33 &mOut, const Matrix33 &m, const float f)
	{
		__m128 f128;

		f128 = _mm_load_ps1(&f);

		mOut.row[0] = _mm_div_ps(m.row[0], f128);
		mOut.row[1] = _mm_div_ps(m.row[1], f128);
		mOut.row[2] = _mm_div_ps(m.row[2], f128);
	}

	void _transposeMatrix33SSE(Matrix33 &mOut, const Matrix33 &m)
	{
		float buf;
		buf = m.m[1][0];
		mOut.m[1][0] = m.m[0][1];
		mOut.m[0][1] = buf;
		buf = m.m[2][0];
		mOut.m[2][0] = m.m[0][2];
		mOut.m[0][2] = buf;

		buf = m.m[2][1];
		mOut.m[2][1] = m.m[1][2];
		mOut.m[1][2] = buf;
	}
#endif // SIMDARCH_SSE

#if defined SIMDARCH_NEON
	//////////////////////////////////////////////////
	//					NEON						//
	//////////////////////////////////////////////////
	void _addMatrix33Matrix33NEON(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.row[0] = vaddq_f32(m1.row[0], m2.row[0]);
		mOut.row[1] = vaddq_f32(m1.row[1], m2.row[1]);
		mOut.row[2] = vaddq_f32(m1.row[2], m2.row[2]);
	}

	void _subtractMatrix33Matrix33NEON(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.row[0] = vsubq_f32(m1.row[0], m2.row[0]);
		mOut.row[1] = vsubq_f32(m1.row[1], m2.row[1]);
		mOut.row[2] = vsubq_f32(m1.row[2], m2.row[2]);
	}

	void _multiplyMatrix33Matrix33NEON(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		mOut.row[0] = vaddq_f32(
			vaddq_f32(
				vmulq_f32(vshuffleq_f32(m1.row[0], m1.row[0], VQ_SHUFFLE(0, 0, 0, 0)), m2.row[0]),
				vmulq_f32(vshuffleq_f32(m1.row[0], m1.row[0], VQ_SHUFFLE(1, 1, 1, 1)), m2.row[1])),
			vmulq_f32(vshuffleq_f32(m1.row[0], m1.row[0], VQ_SHUFFLE(2, 2, 2, 2)), m2.row[2]));

		mOut.row[1] = vaddq_f32(
			vaddq_f32(
				vmulq_f32(vshuffleq_f32(m1.row[1], m1.row[1], VQ_SHUFFLE(0, 0, 0, 0)), m2.row[0]),
				vmulq_f32(vshuffleq_f32(m1.row[1], m1.row[1], VQ_SHUFFLE(1, 1, 1, 1)), m2.row[1])),
			vmulq_f32(vshuffleq_f32(m1.row[1], m1.row[1], VQ_SHUFFLE(2, 2, 2, 2)), m2.row[2]));

		mOut.row[2] = vaddq_f32(
			vaddq_f32(
				vmulq_f32(vshuffleq_f32(m1.row[2], m1.row[2], VQ_SHUFFLE(0, 0, 0, 0)), m2.row[0]),
				vmulq_f32(vshuffleq_f32(m1.row[2], m1.row[2], VQ_SHUFFLE(1, 1, 1, 1)), m2.row[1])),
			vmulq_f32(vshuffleq_f32(m1.row[2], m1.row[2], VQ_SHUFFLE(2, 2, 2, 2)), m2.row[2]));
	}

	void _multiplyMatrix33Vector2NEON(Vector2 &vOut, const Matrix33 &m, const Vector2 &v)
	{
		vOut.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * 1.0f;
		vOut.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * 1.0f;
	}

	void _multiplyMatrix33Vector3NEON(Vector3 &vOut, const Matrix33 &m, const Vector3 &v)
	{
		vOut.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z;
		vOut.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z;
		vOut.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z;
	}

	void _multiplyMatrix33FloatNEON(Matrix33 &mOut, const Matrix33 &m, const float f)
	{
		float32x4_t f128;

		f128 = vld1q_f32(&f);

		mOut.row[0] = vmulq_f32(m.row[0], f128);
		mOut.row[1] = vmulq_f32(m.row[1], f128);
		mOut.row[2] = vmulq_f32(m.row[2], f128);
	}

	void _divideMatrix33FloatNEON(Matrix33 &mOut, const Matrix33 &m, const float f)
	{
		float32x4_t f128;

		f128 = vld1q_f32(&f);

		mOut.row[0] = vdivq_f32(m.row[0], f128);
		mOut.row[1] = vdivq_f32(m.row[1], f128);
		mOut.row[2] = vdivq_f32(m.row[2], f128);
	}

	void _transposeMatrix33NEON(Matrix33 &mOut, const Matrix33 &m)
	{
		float buf;
		buf = m.m[1][0];
		mOut.m[1][0] = m.m[0][1];
		mOut.m[0][1] = buf;
		buf = m.m[2][0];
		mOut.m[2][0] = m.m[0][2];
		mOut.m[0][2] = buf;

		buf = m.m[2][1];
		mOut.m[2][1] = m.m[1][2];
		mOut.m[1][2] = buf;
	}
#endif // SIMDARCH_NEON

	/****************************************/
	/*!
		@brief	Make inverse matrix
		@note

		@param	mOut Made inverse matrix

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	bool Matrix33::inverse()
	{
		Matrix33 tmpMatrix;
		float det = 0.0f;

		tmpMatrix.serial[0] = serial[4] * serial[4] - serial[8] * serial[8];

		tmpMatrix.serial[3] = -serial[3] * serial[8] + serial[5] * serial[6];

		tmpMatrix.serial[6] = serial[3] * serial[7] - serial[4] * serial[6];

		tmpMatrix.serial[1] = -serial[1] * serial[8] + serial[2] * serial[7];

		tmpMatrix.serial[4] = serial[0] * serial[8] - serial[2] * serial[6];

		tmpMatrix.serial[7] = -serial[0] * serial[7] + serial[1] * serial[6];

		tmpMatrix.serial[2] = serial[1] * serial[5] - serial[2] * serial[4];

		tmpMatrix.serial[5] = -serial[0] * serial[5] + serial[2] * serial[3];

		tmpMatrix.serial[8] = serial[0] * serial[4] - serial[1] * serial[3];

		det = serial[0] * tmpMatrix.serial[0] + serial[1] * tmpMatrix.serial[3] + serial[2] * tmpMatrix.serial[6];

		if (det == 0)
			return FALSE;

		det = 1.0f / det;

		for (int i = 0; i < 9; i++)
			serial[i] = tmpMatrix.serial[i] * det;

		return TRUE;
	}

	//////////////////////////////////////////////////////////
	//						Matrix44						//
	//////////////////////////////////////////////////////////
	void (*_addMatrix44Matrix44)(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2) = _addMatrix44Matrix44Usual;
	void (*_subtractMatrix44Matrix44)(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2) = _subtractMatrix44Matrix44Usual;
	void (*_multiplyMatrix44Matrix44)(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2) = _multiplyMatrix44Matrix44Usual;
	void (*_multiplyMatrix44Vector3)(Vector3 &vOut, const Matrix44 &m, const Vector3 &v) = _multiplyMatrix44Vector3Usual;
	void (*_multiplyMatrix44Vector4)(Vector4 &vOut, const Matrix44 &m, const Vector4 &v) = _multiplyMatrix44Vector4Usual;
	void (*_multiplyMatrix44Float)(Matrix44 &mOut, const Matrix44 &m, const float f) = _multiplyMatrix44FloatUsual;
	void (*_divideMatrix44Float)(Matrix44 &mOut, const Matrix44 &m, const float f) = _divideMatrix44FloatUsual;

	void (*_transposeMatrix44)(Matrix44 &mOut, const Matrix44 &m) = _transposeMatrix44Usual;

	//////////////////////////////////////////////////
	//					Usual						//
	//////////////////////////////////////////////////
	void _addMatrix44Matrix44Usual(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		mOut.m[0][0] = m1.m[0][0] + m2.m[0][0];
		mOut.m[1][0] = m1.m[1][0] + m2.m[1][0];
		mOut.m[2][0] = m1.m[2][0] + m2.m[2][0];
		mOut.m[3][0] = m1.m[3][0] + m2.m[3][0];

		mOut.m[0][1] = m1.m[0][1] + m2.m[0][1];
		mOut.m[1][1] = m1.m[1][1] + m2.m[1][1];
		mOut.m[2][1] = m1.m[2][1] + m2.m[2][1];
		mOut.m[3][1] = m1.m[3][1] + m2.m[3][1];

		mOut.m[0][2] = m1.m[0][2] + m2.m[0][2];
		mOut.m[1][2] = m1.m[1][2] + m2.m[1][2];
		mOut.m[2][2] = m1.m[2][2] + m2.m[2][2];
		mOut.m[3][2] = m1.m[3][2] + m2.m[3][2];

		mOut.m[0][3] = m1.m[0][3] + m2.m[0][3];
		mOut.m[1][3] = m1.m[1][3] + m2.m[1][3];
		mOut.m[2][3] = m1.m[2][3] + m2.m[2][3];
		mOut.m[3][3] = m1.m[3][3] + m2.m[3][3];
	}

	void _subtractMatrix44Matrix44Usual(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		mOut.m[0][0] = m1.m[0][0] - m2.m[0][0];
		mOut.m[1][0] = m1.m[1][0] - m2.m[1][0];
		mOut.m[2][0] = m1.m[2][0] - m2.m[2][0];
		mOut.m[3][0] = m1.m[3][0] - m2.m[3][0];

		mOut.m[0][1] = m1.m[0][1] - m2.m[0][1];
		mOut.m[1][1] = m1.m[1][1] - m2.m[1][1];
		mOut.m[2][1] = m1.m[2][1] - m2.m[2][1];
		mOut.m[3][1] = m1.m[3][1] - m2.m[3][1];

		mOut.m[0][2] = m1.m[0][2] - m2.m[0][2];
		mOut.m[1][2] = m1.m[1][2] - m2.m[1][2];
		mOut.m[2][2] = m1.m[2][2] - m2.m[2][2];
		mOut.m[3][2] = m1.m[3][2] - m2.m[3][2];

		mOut.m[0][3] = m1.m[0][3] - m2.m[0][3];
		mOut.m[1][3] = m1.m[1][3] - m2.m[1][3];
		mOut.m[2][3] = m1.m[2][3] - m2.m[2][3];
		mOut.m[3][3] = m1.m[3][3] - m2.m[3][3];
	}

	void _multiplyMatrix44Matrix44Usual(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		mOut.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[1][0] * m2.m[0][1] + m1.m[2][0] * m2.m[0][2] + m1.m[3][0] * m2.m[0][3];
		mOut.m[1][0] = m1.m[0][0] * m2.m[1][0] + m1.m[1][0] * m2.m[1][1] + m1.m[2][0] * m2.m[1][2] + m1.m[3][0] * m2.m[1][3];
		mOut.m[2][0] = m1.m[0][0] * m2.m[2][0] + m1.m[1][0] * m2.m[2][1] + m1.m[2][0] * m2.m[2][2] + m1.m[3][0] * m2.m[2][3];
		mOut.m[3][0] = m1.m[0][0] * m2.m[3][0] + m1.m[1][0] * m2.m[3][1] + m1.m[2][0] * m2.m[3][2] + m1.m[3][0] * m2.m[3][3];

		mOut.m[0][1] = m1.m[0][1] * m2.m[0][0] + m1.m[1][1] * m2.m[0][1] + m1.m[2][1] * m2.m[0][2] + m1.m[3][1] * m2.m[0][3];
		mOut.m[1][1] = m1.m[0][1] * m2.m[1][0] + m1.m[1][1] * m2.m[1][1] + m1.m[2][1] * m2.m[1][2] + m1.m[3][1] * m2.m[1][3];
		mOut.m[2][1] = m1.m[0][1] * m2.m[2][0] + m1.m[1][1] * m2.m[2][1] + m1.m[2][1] * m2.m[2][2] + m1.m[3][1] * m2.m[2][3];
		mOut.m[3][1] = m1.m[0][1] * m2.m[3][0] + m1.m[1][1] * m2.m[3][1] + m1.m[2][1] * m2.m[3][2] + m1.m[3][1] * m2.m[3][3];

		mOut.m[0][2] = m1.m[0][2] * m2.m[0][0] + m1.m[1][2] * m2.m[0][1] + m1.m[2][2] * m2.m[0][2] + m1.m[3][2] * m2.m[0][3];
		mOut.m[1][2] = m1.m[0][2] * m2.m[1][0] + m1.m[1][2] * m2.m[1][1] + m1.m[2][2] * m2.m[1][2] + m1.m[3][2] * m2.m[1][3];
		mOut.m[2][2] = m1.m[0][2] * m2.m[2][0] + m1.m[1][2] * m2.m[2][1] + m1.m[2][2] * m2.m[2][2] + m1.m[3][2] * m2.m[2][3];
		mOut.m[3][2] = m1.m[0][2] * m2.m[3][0] + m1.m[1][2] * m2.m[3][1] + m1.m[2][2] * m2.m[3][2] + m1.m[3][2] * m2.m[3][3];

		mOut.m[0][3] = m1.m[0][3] * m2.m[0][0] + m1.m[1][3] * m2.m[0][1] + m1.m[2][3] * m2.m[0][2] + m1.m[3][3] * m2.m[0][3];
		mOut.m[1][3] = m1.m[0][3] * m2.m[1][0] + m1.m[1][3] * m2.m[1][1] + m1.m[2][3] * m2.m[1][2] + m1.m[3][3] * m2.m[1][3];
		mOut.m[2][3] = m1.m[0][3] * m2.m[2][0] + m1.m[1][3] * m2.m[2][1] + m1.m[2][3] * m2.m[2][2] + m1.m[3][3] * m2.m[2][3];
		mOut.m[3][3] = m1.m[0][3] * m2.m[3][0] + m1.m[1][3] * m2.m[3][1] + m1.m[2][3] * m2.m[3][2] + m1.m[3][3] * m2.m[3][3];
	}

	void _multiplyMatrix44Vector3Usual(Vector3 &vOut, const Matrix44 &m, const Vector3 &v)
	{
		Vector3 tv;
		tv.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * 1.0f;
		tv.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * 1.0f;
		tv.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * 1.0f;
		vOut = tv;
	}

	void _multiplyMatrix44Vector4Usual(Vector4 &vOut, const Matrix44 &m, const Vector4 &v)
	{
		Vector4 tv;
		tv.x = m.m[0][0] * v.x + m.m[1][0] * v.y + m.m[2][0] * v.z + m.m[3][0] * v.w;
		tv.y = m.m[0][1] * v.x + m.m[1][1] * v.y + m.m[2][1] * v.z + m.m[3][1] * v.w;
		tv.z = m.m[0][2] * v.x + m.m[1][2] * v.y + m.m[2][2] * v.z + m.m[3][2] * v.w;
		tv.w = m.m[0][3] * v.x + m.m[1][3] * v.y + m.m[2][3] * v.z + m.m[3][3] * v.w;
		vOut = tv;
	}

	void _multiplyMatrix44FloatUsual(Matrix44 &mOut, const Matrix44 &m, const float f)
	{
		mOut.m[0][0] = m.m[0][0] * f;
		mOut.m[1][0] = m.m[1][0] * f;
		mOut.m[2][0] = m.m[2][0] * f;
		mOut.m[3][0] = m.m[3][0] * f;

		mOut.m[0][1] = m.m[0][1] * f;
		mOut.m[1][1] = m.m[1][1] * f;
		mOut.m[2][1] = m.m[2][1] * f;
		mOut.m[3][1] = m.m[3][1] * f;

		mOut.m[0][1] = m.m[0][1] * f;
		mOut.m[1][1] = m.m[1][1] * f;
		mOut.m[2][1] = m.m[2][1] * f;
		mOut.m[3][1] = m.m[3][1] * f;

		mOut.m[0][1] = m.m[0][1] * f;
		mOut.m[1][1] = m.m[1][1] * f;
		mOut.m[2][1] = m.m[2][1] * f;
		mOut.m[3][1] = m.m[3][1] * f;
	}

	void _divideMatrix44FloatUsual(Matrix44 &mOut, const Matrix44 &m, const float f)
	{
		mOut.m[0][0] = m.m[0][0] / f;
		mOut.m[1][0] = m.m[1][0] / f;
		mOut.m[2][0] = m.m[2][0] / f;
		mOut.m[3][0] = m.m[3][0] / f;

		mOut.m[0][1] = m.m[0][1] / f;
		mOut.m[1][1] = m.m[1][1] / f;
		mOut.m[2][1] = m.m[2][1] / f;
		mOut.m[3][1] = m.m[3][1] / f;

		mOut.m[0][1] = m.m[0][1] / f;
		mOut.m[1][1] = m.m[1][1] / f;
		mOut.m[2][1] = m.m[2][1] / f;
		mOut.m[3][1] = m.m[3][1] / f;

		mOut.m[0][1] = m.m[0][1] / f;
		mOut.m[1][1] = m.m[1][1] / f;
		mOut.m[2][1] = m.m[2][1] / f;
		mOut.m[3][1] = m.m[3][1] / f;
	}

	void _transposeMatrix44Usual(Matrix44 &mOut, const Matrix44 &m)
	{
		float buf;
		buf = m.m[1][0];
		mOut.m[1][0] = m.m[0][1];
		mOut.m[0][1] = buf;
		buf = m.m[2][0];
		mOut.m[2][0] = m.m[0][2];
		mOut.m[0][2] = buf;
		buf = m.m[3][0];
		mOut.m[3][0] = m.m[0][3];
		mOut.m[0][3] = buf;

		buf = m.m[2][1];
		mOut.m[2][1] = m.m[1][2];
		mOut.m[1][2] = buf;
		buf = m.m[3][1];
		mOut.m[3][1] = m.m[1][3];
		mOut.m[1][3] = buf;

		buf = m.m[3][2];
		mOut.m[3][2] = m.m[2][3];
		mOut.m[2][3] = buf;
	}

#if defined SIMDARCH_SSE
	//////////////////////////////////////////////////
	//					SSE							//
	//////////////////////////////////////////////////
	void _addMatrix44Matrix44SSE(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		mOut.row[0] = _mm_add_ps(m1.row[0], m2.row[0]);
		mOut.row[1] = _mm_add_ps(m1.row[1], m2.row[1]);
		mOut.row[2] = _mm_add_ps(m1.row[2], m2.row[2]);
		mOut.row[3] = _mm_add_ps(m1.row[3], m2.row[3]);
	}

	void _subtractMatrix44Matrix44SSE(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		mOut.row[0] = _mm_sub_ps(m1.row[0], m2.row[0]);
		mOut.row[1] = _mm_sub_ps(m1.row[1], m2.row[1]);
		mOut.row[2] = _mm_sub_ps(m1.row[2], m2.row[2]);
		mOut.row[3] = _mm_sub_ps(m1.row[3], m2.row[3]);
	}

	void _multiplyMatrix44Matrix44SSE(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		__m128 e0, e1, e2, e3;
		__m128 mat0, mat1, mat2, mat3;
		__m128 a0, a1, a2;

		e0 = _mm_shuffle_ps(m2.row[0], m2.row[0], _MM_SHUFFLE(0, 0, 0, 0));
		e1 = _mm_shuffle_ps(m2.row[0], m2.row[0], _MM_SHUFFLE(1, 1, 1, 1));
		e2 = _mm_shuffle_ps(m2.row[0], m2.row[0], _MM_SHUFFLE(2, 2, 2, 2));
		e3 = _mm_shuffle_ps(m2.row[0], m2.row[0], _MM_SHUFFLE(3, 3, 3, 3));

		mat0 = _mm_mul_ps(m1.row[0], e0);
		mat1 = _mm_mul_ps(m1.row[1], e1);
		mat2 = _mm_mul_ps(m1.row[2], e2);
		mat3 = _mm_mul_ps(m1.row[3], e3);

		a0 = _mm_add_ps(mat0, mat1);
		a1 = _mm_add_ps(mat2, mat3);
		a2 = _mm_add_ps(a0, a1);

		mOut.row[0] = a2;

		e0 = _mm_shuffle_ps(m2.row[1], m2.row[1], _MM_SHUFFLE(0, 0, 0, 0));
		e1 = _mm_shuffle_ps(m2.row[1], m2.row[1], _MM_SHUFFLE(1, 1, 1, 1));
		e2 = _mm_shuffle_ps(m2.row[1], m2.row[1], _MM_SHUFFLE(2, 2, 2, 2));
		e3 = _mm_shuffle_ps(m2.row[1], m2.row[1], _MM_SHUFFLE(3, 3, 3, 3));

		mat0 = _mm_mul_ps(m1.row[0], e0);
		mat1 = _mm_mul_ps(m1.row[1], e1);
		mat2 = _mm_mul_ps(m1.row[2], e2);
		mat3 = _mm_mul_ps(m1.row[3], e3);

		a0 = _mm_add_ps(mat0, mat1);
		a1 = _mm_add_ps(mat2, mat3);
		a2 = _mm_add_ps(a0, a1);

		mOut.row[1] = a2;

		e0 = _mm_shuffle_ps(m2.row[2], m2.row[2], _MM_SHUFFLE(0, 0, 0, 0));
		e1 = _mm_shuffle_ps(m2.row[2], m2.row[2], _MM_SHUFFLE(1, 1, 1, 1));
		e2 = _mm_shuffle_ps(m2.row[2], m2.row[2], _MM_SHUFFLE(2, 2, 2, 2));
		e3 = _mm_shuffle_ps(m2.row[2], m2.row[2], _MM_SHUFFLE(3, 3, 3, 3));

		mat0 = _mm_mul_ps(m1.row[0], e0);
		mat1 = _mm_mul_ps(m1.row[1], e1);
		mat2 = _mm_mul_ps(m1.row[2], e2);
		mat3 = _mm_mul_ps(m1.row[3], e3);

		a0 = _mm_add_ps(mat0, mat1);
		a1 = _mm_add_ps(mat2, mat3);
		a2 = _mm_add_ps(a0, a1);

		mOut.row[2] = a2;

		e0 = _mm_shuffle_ps(m2.row[3], m2.row[3], _MM_SHUFFLE(0, 0, 0, 0));
		e1 = _mm_shuffle_ps(m2.row[3], m2.row[3], _MM_SHUFFLE(1, 1, 1, 1));
		e2 = _mm_shuffle_ps(m2.row[3], m2.row[3], _MM_SHUFFLE(2, 2, 2, 2));
		e3 = _mm_shuffle_ps(m2.row[3], m2.row[3], _MM_SHUFFLE(3, 3, 3, 3));

		mat0 = _mm_mul_ps(m1.row[0], e0);
		mat1 = _mm_mul_ps(m1.row[1], e1);
		mat2 = _mm_mul_ps(m1.row[2], e2);
		mat3 = _mm_mul_ps(m1.row[3], e3);

		a0 = _mm_add_ps(mat0, mat1);
		a1 = _mm_add_ps(mat2, mat3);
		a2 = _mm_add_ps(a0, a1);

		mOut.row[3] = a2;
	}

	void _multiplyMatrix44Vector3SSE(Vector3 &vOut, const Matrix44 &m, const Vector3 &v)
	{
		__m128 v0 = _mm_shuffle_ps(v.quad, v.quad, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 v1 = _mm_shuffle_ps(v.quad, v.quad, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 v2 = _mm_shuffle_ps(v.quad, v.quad, _MM_SHUFFLE(2, 2, 2, 2));

		__m128 m0 = _mm_mul_ps(m.row[0], v0);
		__m128 m1 = _mm_mul_ps(m.row[1], v1);
		__m128 m2 = _mm_mul_ps(m.row[2], v2);

		__m128 s0 = _mm_add_ps(m0, m1);

		vOut.quad = _mm_add_ps(s0, m2);
	}

	void _multiplyMatrix44Vector4SSE(Vector4 &vOut, const Matrix44 &m, const Vector4 &v)
	{
		__m128 v0 = _mm_shuffle_ps(v.quad, v.quad, _MM_SHUFFLE(0, 0, 0, 0));
		__m128 v1 = _mm_shuffle_ps(v.quad, v.quad, _MM_SHUFFLE(1, 1, 1, 1));
		__m128 v2 = _mm_shuffle_ps(v.quad, v.quad, _MM_SHUFFLE(2, 2, 2, 2));
		__m128 v3 = _mm_shuffle_ps(v.quad, v.quad, _MM_SHUFFLE(3, 3, 3, 3));

		__m128 m0 = _mm_mul_ps(m.row[0], v0);
		__m128 m1 = _mm_mul_ps(m.row[1], v1);
		__m128 m2 = _mm_mul_ps(m.row[2], v2);
		__m128 m3 = _mm_mul_ps(m.row[3], v3);

		__m128 s0 = _mm_add_ps(m0, m1);
		__m128 s1 = _mm_add_ps(m2, m3);

		vOut.quad = _mm_add_ps(s0, s1);
	}

	void _multiplyMatrix44FloatSSE(Matrix44 &mOut, const Matrix44 &m, const float f)
	{

		__m128 fv = _mm_load1_ps(&f);

		mOut.row[0] = _mm_mul_ps(m.row[0], fv);
		mOut.row[1] = _mm_mul_ps(m.row[1], fv);
		mOut.row[2] = _mm_mul_ps(m.row[2], fv);
		mOut.row[3] = _mm_mul_ps(m.row[3], fv);
	}

	void _divideMatrix44FloatSSE(Matrix44 &mOut, const Matrix44 &m, const float f)
	{

		__m128 fv = _mm_load1_ps(&f);

		mOut.row[0] = _mm_div_ps(m.row[0], fv);
		mOut.row[1] = _mm_div_ps(m.row[1], fv);
		mOut.row[2] = _mm_div_ps(m.row[2], fv);
		mOut.row[3] = _mm_div_ps(m.row[3], fv);
	}

	void _transposeMatrix44SSE(Matrix44 &mOut, const Matrix44 &m)
	{

		__m128 b0 = _mm_shuffle_ps(m.row[0], m.row[1], 0x44);
		__m128 b2 = _mm_shuffle_ps(m.row[0], m.row[1], 0xEE);
		__m128 b1 = _mm_shuffle_ps(m.row[2], m.row[3], 0x44);
		__m128 b3 = _mm_shuffle_ps(m.row[2], m.row[3], 0xEE);

		mOut.row[0] = _mm_shuffle_ps(b0, b1, 0x88);
		mOut.row[1] = _mm_shuffle_ps(b0, b1, 0xDD);
		mOut.row[2] = _mm_shuffle_ps(b2, b3, 0x88);
		mOut.row[3] = _mm_shuffle_ps(b2, b3, 0xDD);
	}
#endif // SIMDARCH_SSE

#if defined SIMDARCH_NEON
	//////////////////////////////////////////////////
	//					NEON						//
	//////////////////////////////////////////////////

	void
	_addMatrix44Matrix44NEON(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		mOut.row[0] = vaddq_f32(m1.row[0], m2.row[0]);
		mOut.row[1] = vaddq_f32(m1.row[1], m2.row[1]);
		mOut.row[2] = vaddq_f32(m1.row[2], m2.row[2]);
		mOut.row[3] = vaddq_f32(m1.row[3], m2.row[3]);
	}

	void _subtractMatrix44Matrix44NEON(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		mOut.row[0] = vsubq_f32(m1.row[0], m2.row[0]);
		mOut.row[1] = vsubq_f32(m1.row[1], m2.row[1]);
		mOut.row[2] = vsubq_f32(m1.row[2], m2.row[2]);
		mOut.row[3] = vsubq_f32(m1.row[3], m2.row[3]);
	}

	void _multiplyMatrix44Matrix44NEON(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		float32x4_t e0, e1, e2, e3;
		float32x4_t mat0, mat1, mat2, mat3;
		float32x4_t a0, a1, a2;

		e0 = vshuffleq_f32(m2.row[0], m2.row[0], VQ_SHUFFLE(0, 0, 0, 0));
		e1 = vshuffleq_f32(m2.row[0], m2.row[0], VQ_SHUFFLE(1, 1, 1, 1));
		e2 = vshuffleq_f32(m2.row[0], m2.row[0], VQ_SHUFFLE(2, 2, 2, 2));
		e3 = vshuffleq_f32(m2.row[0], m2.row[0], VQ_SHUFFLE(3, 3, 3, 3));

		mat0 = vmulq_f32(m1.row[0], e0);
		mat1 = vmulq_f32(m1.row[1], e1);
		mat2 = vmulq_f32(m1.row[2], e2);
		mat3 = vmulq_f32(m1.row[3], e3);

		a0 = vaddq_f32(mat0, mat1);
		a1 = vaddq_f32(mat2, mat3);
		a2 = vaddq_f32(a0, a1);

		mOut.row[0] = a2;

		e0 = vshuffleq_f32(m2.row[1], m2.row[1], VQ_SHUFFLE(0, 0, 0, 0));
		e1 = vshuffleq_f32(m2.row[1], m2.row[1], VQ_SHUFFLE(1, 1, 1, 1));
		e2 = vshuffleq_f32(m2.row[1], m2.row[1], VQ_SHUFFLE(2, 2, 2, 2));
		e3 = vshuffleq_f32(m2.row[1], m2.row[1], VQ_SHUFFLE(3, 3, 3, 3));

		mat0 = vmulq_f32(m1.row[0], e0);
		mat1 = vmulq_f32(m1.row[1], e1);
		mat2 = vmulq_f32(m1.row[2], e2);
		mat3 = vmulq_f32(m1.row[3], e3);

		a0 = vaddq_f32(mat0, mat1);
		a1 = vaddq_f32(mat2, mat3);
		a2 = vaddq_f32(a0, a1);

		mOut.row[1] = a2;

		e0 = vshuffleq_f32(m2.row[2], m2.row[2], VQ_SHUFFLE(0, 0, 0, 0));
		e1 = vshuffleq_f32(m2.row[2], m2.row[2], VQ_SHUFFLE(1, 1, 1, 1));
		e2 = vshuffleq_f32(m2.row[2], m2.row[2], VQ_SHUFFLE(2, 2, 2, 2));
		e3 = vshuffleq_f32(m2.row[2], m2.row[2], VQ_SHUFFLE(3, 3, 3, 3));

		mat0 = vmulq_f32(m1.row[0], e0);
		mat1 = vmulq_f32(m1.row[1], e1);
		mat2 = vmulq_f32(m1.row[2], e2);
		mat3 = vmulq_f32(m1.row[3], e3);

		a0 = vaddq_f32(mat0, mat1);
		a1 = vaddq_f32(mat2, mat3);
		a2 = vaddq_f32(a0, a1);

		mOut.row[2] = a2;

		e0 = vshuffleq_f32(m2.row[3], m2.row[3], VQ_SHUFFLE(0, 0, 0, 0));
		e1 = vshuffleq_f32(m2.row[3], m2.row[3], VQ_SHUFFLE(1, 1, 1, 1));
		e2 = vshuffleq_f32(m2.row[3], m2.row[3], VQ_SHUFFLE(2, 2, 2, 2));
		e3 = vshuffleq_f32(m2.row[3], m2.row[3], VQ_SHUFFLE(3, 3, 3, 3));

		mat0 = vmulq_f32(m1.row[0], e0);
		mat1 = vmulq_f32(m1.row[1], e1);
		mat2 = vmulq_f32(m1.row[2], e2);
		mat3 = vmulq_f32(m1.row[3], e3);

		a0 = vaddq_f32(mat0, mat1);
		a1 = vaddq_f32(mat2, mat3);
		a2 = vaddq_f32(a0, a1);

		mOut.row[3] = a2;
	}

	void _multiplyMatrix44Vector3NEON(Vector3 &vOut, const Matrix44 &m, const Vector3 &v)
	{
		float32x4_t v0 = vshuffleq_f32(v.quad, v.quad, VQ_SHUFFLE(0, 0, 0, 0));
		float32x4_t v1 = vshuffleq_f32(v.quad, v.quad, VQ_SHUFFLE(1, 1, 1, 1));
		float32x4_t v2 = vshuffleq_f32(v.quad, v.quad, VQ_SHUFFLE(2, 2, 2, 2));

		float32x4_t m0 = vmulq_f32(m.row[0], v0);
		float32x4_t m1 = vmulq_f32(m.row[1], v1);
		float32x4_t m2 = vmulq_f32(m.row[2], v2);

		float32x4_t s0 = vaddq_f32(m0, m1);

		vOut.quad = vaddq_f32(s0, m2);
	}

	void _multiplyMatrix44Vector4NEON(Vector4 &vOut, const Matrix44 &m, const Vector4 &v)
	{
		float32x4_t v0 = vshuffleq_f32(v.quad, v.quad, VQ_SHUFFLE(0, 0, 0, 0));
		float32x4_t v1 = vshuffleq_f32(v.quad, v.quad, VQ_SHUFFLE(1, 1, 1, 1));
		float32x4_t v2 = vshuffleq_f32(v.quad, v.quad, VQ_SHUFFLE(2, 2, 2, 2));
		float32x4_t v3 = vshuffleq_f32(v.quad, v.quad, VQ_SHUFFLE(3, 3, 3, 3));

		float32x4_t m0 = vmulq_f32(m.row[0], v0);
		float32x4_t m1 = vmulq_f32(m.row[1], v1);
		float32x4_t m2 = vmulq_f32(m.row[2], v2);
		float32x4_t m3 = vmulq_f32(m.row[3], v3);

		float32x4_t s0 = vaddq_f32(m0, m1);
		float32x4_t s1 = vaddq_f32(m2, m3);

		vOut.quad = vaddq_f32(s0, s1);
	}

	void _multiplyMatrix44FloatNEON(Matrix44 &mOut, const Matrix44 &m, const float f)
	{
		float32x4_t fv = vld1q_f32(&f);

		mOut.row[0] = vmulq_f32(m.row[0], fv);
		mOut.row[1] = vmulq_f32(m.row[1], fv);
		mOut.row[2] = vmulq_f32(m.row[2], fv);
		mOut.row[3] = vmulq_f32(m.row[3], fv);
	}

	void _divideMatrix44FloatNEON(Matrix44 &mOut, const Matrix44 &m, const float f)
	{
		float32x4_t fv = vld1q_f32(&f);

		mOut.row[0] = vdivq_f32(m.row[0], fv);
		mOut.row[1] = vdivq_f32(m.row[1], fv);
		mOut.row[2] = vdivq_f32(m.row[2], fv);
		mOut.row[3] = vdivq_f32(m.row[3], fv);
	}

	void _transposeMatrix44NEON(Matrix44 &mOut, const Matrix44 &m)
	{
		float32x4_t b0 = vshuffleq_f32(m.row[0], m.row[1], 0x44);
		float32x4_t b2 = vshuffleq_f32(m.row[0], m.row[1], 0xEE);
		float32x4_t b1 = vshuffleq_f32(m.row[2], m.row[3], 0x44);
		float32x4_t b3 = vshuffleq_f32(m.row[2], m.row[3], 0xEE);

		mOut.row[0] = vshuffleq_f32(b0, b1, 0x88);
		mOut.row[1] = vshuffleq_f32(b0, b1, 0xDD);
		mOut.row[2] = vshuffleq_f32(b2, b3, 0x88);
		mOut.row[3] = vshuffleq_f32(b2, b3, 0xDD);
	}

#endif // SIMDARCH_NEON

	/****************************************/
	/*!
		@brief	Make inverse matrix
		@note

		@param	mOut Made inverse matrix

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	bool Matrix44::inverse()
	{
		Matrix44 tmpMatrix;
		float det = 0.0f;

		tmpMatrix.serial[0] = serial[5] * serial[10] * serial[15] - serial[5] * serial[11] * serial[14] - serial[9] * serial[6] * serial[15] + serial[9] * serial[7] * serial[14] + serial[13] * serial[6] * serial[11] - serial[13] * serial[7] * serial[10];

		tmpMatrix.serial[4] = -serial[4] * serial[10] * serial[15] + serial[4] * serial[11] * serial[14] + serial[8] * serial[6] * serial[15] - serial[8] * serial[7] * serial[14] - serial[12] * serial[6] * serial[11] + serial[12] * serial[7] * serial[10];

		tmpMatrix.serial[8] = serial[4] * serial[9] * serial[15] - serial[4] * serial[11] * serial[13] - serial[8] * serial[5] * serial[15] + serial[8] * serial[7] * serial[13] + serial[12] * serial[5] * serial[11] - serial[12] * serial[7] * serial[9];

		tmpMatrix.serial[12] = -serial[4] * serial[9] * serial[14] + serial[4] * serial[10] * serial[13] + serial[8] * serial[5] * serial[14] - serial[8] * serial[6] * serial[13] - serial[12] * serial[5] * serial[10] + serial[12] * serial[6] * serial[9];

		tmpMatrix.serial[1] = -serial[1] * serial[10] * serial[15] + serial[1] * serial[11] * serial[14] + serial[9] * serial[2] * serial[15] - serial[9] * serial[3] * serial[14] - serial[13] * serial[2] * serial[11] + serial[13] * serial[3] * serial[10];

		tmpMatrix.serial[5] = serial[0] * serial[10] * serial[15] - serial[0] * serial[11] * serial[14] - serial[8] * serial[2] * serial[15] + serial[8] * serial[3] * serial[14] + serial[12] * serial[2] * serial[11] - serial[12] * serial[3] * serial[10];

		tmpMatrix.serial[9] = -serial[0] * serial[9] * serial[15] + serial[0] * serial[11] * serial[13] + serial[8] * serial[1] * serial[15] - serial[8] * serial[3] * serial[13] - serial[12] * serial[1] * serial[11] + serial[12] * serial[3] * serial[9];

		tmpMatrix.serial[13] = serial[0] * serial[9] * serial[14] - serial[0] * serial[10] * serial[13] - serial[8] * serial[1] * serial[14] + serial[8] * serial[2] * serial[13] + serial[12] * serial[1] * serial[10] - serial[12] * serial[2] * serial[9];

		tmpMatrix.serial[2] = serial[1] * serial[6] * serial[15] - serial[1] * serial[7] * serial[14] - serial[5] * serial[2] * serial[15] + serial[5] * serial[3] * serial[14] + serial[13] * serial[2] * serial[7] - serial[13] * serial[3] * serial[6];

		tmpMatrix.serial[6] = -serial[0] * serial[6] * serial[15] + serial[0] * serial[7] * serial[14] + serial[4] * serial[2] * serial[15] - serial[4] * serial[3] * serial[14] - serial[12] * serial[2] * serial[7] + serial[12] * serial[3] * serial[6];

		tmpMatrix.serial[10] = serial[0] * serial[5] * serial[15] - serial[0] * serial[7] * serial[13] - serial[4] * serial[1] * serial[15] + serial[4] * serial[3] * serial[13] + serial[12] * serial[1] * serial[7] - serial[12] * serial[3] * serial[5];

		tmpMatrix.serial[14] = -serial[0] * serial[5] * serial[14] + serial[0] * serial[6] * serial[13] + serial[4] * serial[1] * serial[14] - serial[4] * serial[2] * serial[13] - serial[12] * serial[1] * serial[6] + serial[12] * serial[2] * serial[5];

		tmpMatrix.serial[3] = -serial[1] * serial[6] * serial[11] + serial[1] * serial[7] * serial[10] + serial[5] * serial[2] * serial[11] - serial[5] * serial[3] * serial[10] - serial[9] * serial[2] * serial[7] + serial[9] * serial[3] * serial[6];

		tmpMatrix.serial[7] = serial[0] * serial[6] * serial[11] - serial[0] * serial[7] * serial[10] - serial[4] * serial[2] * serial[11] + serial[4] * serial[3] * serial[10] + serial[8] * serial[2] * serial[7] - serial[8] * serial[3] * serial[6];

		tmpMatrix.serial[11] = -serial[0] * serial[5] * serial[11] + serial[0] * serial[7] * serial[9] + serial[4] * serial[1] * serial[11] - serial[4] * serial[3] * serial[9] - serial[8] * serial[1] * serial[7] + serial[8] * serial[3] * serial[5];

		tmpMatrix.serial[15] = serial[0] * serial[5] * serial[10] - serial[0] * serial[6] * serial[9] - serial[4] * serial[1] * serial[10] + serial[4] * serial[2] * serial[9] + serial[8] * serial[1] * serial[6] - serial[8] * serial[2] * serial[5];

		det = serial[0] * tmpMatrix.serial[0] + serial[1] * tmpMatrix.serial[4] + serial[2] * tmpMatrix.serial[8] + serial[3] * tmpMatrix.serial[12];

		if (det == 0)
			return FALSE;

		det = 1.0f / det;

		for (int i = 0; i < 16; i++)
			serial[i] = tmpMatrix.serial[i] * det;

		return TRUE;
	}

}; // namespace S3D
