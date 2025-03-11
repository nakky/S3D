/******************************************************************/
/*!
	@file	Matrix-inl.h
	@brief	Inline definition for mrix
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 10, 2020
*/
/******************************************************************/

#ifndef S3D_MATH_MATRIX_INL_H
#define S3D_MATH_MATRIX_INL_H

#include "S3D/Common.h"

#include <string.h>

namespace S3D
{

	//////////////////////////////////////////////////////////
	//						Matrix33						//
	//////////////////////////////////////////////////////////
	extern void (*_addMatrix33Matrix33)(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	extern void (*_subtractMatrix33Matrix33)(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	extern void (*_multiplyMatrix33Matrix33)(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	extern void (*_multiplyMatrix33Vector2)(Vector2 &vOut, const Matrix33 &m, const Vector2 &v);
	extern void (*_multiplyMatrix33Vector3)(Vector3 &vOut, const Matrix33 &m, const Vector3 &v);
	extern void (*_multiplyMatrix33Float)(Matrix33 &mOut, const Matrix33 &m, const float f);
	extern void (*_divideMatrix33Float)(Matrix33 &mOut, const Matrix33 &m, const float f);

	extern void (*_transposeMatrix33)(Matrix33 &mOut, const Matrix33 &m);

	void _addMatrix33Matrix33Usual(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _subtractMatrix33Matrix33Usual(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _multiplyMatrix33Matrix33Usual(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _multiplyMatrix33Vector2Usual(Vector2 &vOut, const Matrix33 &m, const Vector2 &v);
	void _multiplyMatrix33Vector3Usual(Vector3 &vOut, const Matrix33 &m, const Vector3 &v);
	void _multiplyMatrix33FloatUsual(Matrix33 &mOut, const Matrix33 &m, const float f);
	void _divideMatrix33FloatUsual(Matrix33 &mOut, const Matrix33 &m, const float f);

	void _transposeMatrix33Usual(Matrix33 &mOut, const Matrix33 &m);

#if defined SIMDARCH_SSE
	void _addMatrix33Matrix33SSE(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _subtractMatrix33Matrix33SSE(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _multiplyMatrix33Matrix33SSE(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _multiplyMatrix33Vector2SSE(Vector2 &vOut, const Matrix33 &m, const Vector2 &v);
	void _multiplyMatrix33Vector3SSE(Vector3 &vOut, const Matrix33 &m, const Vector3 &v);
	void _multiplyMatrix33FloatSSE(Matrix33 &mOut, const Matrix33 &m, const float f);
	void _divideMatrix33FloatSSE(Matrix33 &mOut, const Matrix33 &m, const float f);

	void _transposeMatrix33SSE(Matrix33 &mOut, const Matrix33 &m);
#endif // SIMDARCH_SSE

#if defined SIMDARCH_NEON
	void _addMatrix33Matrix33NEON(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _subtractMatrix33Matrix33NEON(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _multiplyMatrix33Matrix33NEON(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2);
	void _multiplyMatrix33Vector2NEON(Vector2 &vOut, const Matrix33 &m, const Vector2 &v);
	void _multiplyMatrix33Vector3NEON(Vector3 &vOut, const Matrix33 &m, const Vector3 &v);
	void _multiplyMatrix33FloatNEON(Matrix33 &mOut, const Matrix33 &m, const float f);
	void _divideMatrix33FloatNEON(Matrix33 &mOut, const Matrix33 &m, const float f);

	void _transposeMatrix33NEON(Matrix33 &mOut, const Matrix33 &m);
#endif // SIMDARCH_NEON

	inline void addMatrix33Matrix33(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		_addMatrix33Matrix33(mOut, m1, m2);
	}

	inline void subtractMatrix33Matrix33(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		_subtractMatrix33Matrix33(mOut, m1, m2);
	}

	inline void multiplyMatrix33Matrix33(Matrix33 &mOut, const Matrix33 &m1, const Matrix33 &m2)
	{
		_multiplyMatrix33Matrix33(mOut, m1, m2);
	}

	inline void multiplyMatrix33Vector2(Vector2 &vOut, const Matrix33 &m, const Vector2 &v)
	{
		_multiplyMatrix33Vector2(vOut, m, v);
	}

	inline void multiplyMatrix33Vector3(Vector3 &vOut, const Matrix33 &m, const Vector3 &v)
	{
		_multiplyMatrix33Vector3(vOut, m, v);
	}

	inline void multiplyMatrix33Float(Matrix33 &mOut, const Matrix33 &m, const float f)
	{
		_multiplyMatrix33Float(mOut, m, f);
	}

	inline void divideMatrix33Float(Matrix33 &mOut, const Matrix33 &m, const float f)
	{
		_divideMatrix33Float(mOut, m, f);
	}

	inline void Matrix33::add(Matrix33 &mOut, const Matrix33 &m) const
	{
		addMatrix33Matrix33(mOut, *this, m);
	}

	inline void Matrix33::subtract(Matrix33 &mOut, const Matrix33 &m) const
	{
		subtractMatrix33Matrix33(mOut, *this, m);
	}

	inline void Matrix33::multiply(Matrix33 &mOut, const Matrix33 &m) const
	{
		multiplyMatrix33Matrix33(mOut, *this, m);
	}

	inline void Matrix33::multiply(Vector2 &vOut, const Vector2 &v) const
	{
		multiplyMatrix33Vector2(vOut, *this, v);
	}

	inline void Matrix33::multiply(Vector3 &vOut, const Vector3 &v) const
	{
		multiplyMatrix33Vector3(vOut, *this, v);
	}

	inline void Matrix33::multiply(Matrix33 &mOut, const float f) const
	{
		multiplyMatrix33Float(mOut, *this, f);
	}

	inline void Matrix33::divide(Matrix33 &mOut, const float f) const
	{
		divideMatrix33Float(mOut, *this, f);
	}

	inline Matrix33 Matrix33::operator+(const Matrix33 &m) const
	{
		Matrix33 retMat;
		addMatrix33Matrix33(retMat, *this, m);
		return retMat;
	}

	inline Matrix33 Matrix33::operator-(const Matrix33 &m) const
	{
		Matrix33 retMat;
		subtractMatrix33Matrix33(retMat, *this, m);
		return retMat;
	}

	inline Matrix33 Matrix33::operator*(const Matrix33 &m) const
	{
		Matrix33 retMat;
		multiplyMatrix33Matrix33(retMat, *this, m);
		return retMat;
	}

	inline Vector2 Matrix33::operator*(const Vector2 &v) const
	{
		Vector2 retVec;
		multiplyMatrix33Vector2(retVec, *this, v);
		return retVec;
	}

	inline Vector3 Matrix33::operator*(const Vector3 &v) const
	{
		Vector3 retVec;
		multiplyMatrix33Vector3(retVec, *this, v);
		return retVec;
	}

	inline Matrix33 Matrix33::operator*(const float f) const
	{
		Matrix33 retMat;
		multiplyMatrix33Float(retMat, *this, f);
		return retMat;
	}

	inline Matrix33 Matrix33::operator/(const float f) const
	{
		Matrix33 retMat;
		divideMatrix33Float(retMat, *this, f);
		return retMat;
	}

	inline void Matrix33::setUnitMatrix()
	{
		m[0][0] = 1.0f;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = 1.0f;
		m[2][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
	}

	inline void Matrix33::transpose()
	{
		_transposeMatrix33(*this, *this);
	}

	/****************************************/
	/*!
		@brief	Set translation matrix
		@note

		@param	v displacement

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix33::setTransrationMatrix(const Vector2 &v)
	{
		m[0][0] = 1.0f;
		m[1][0] = 0.0f;
		m[2][0] = v.x;
		m[0][1] = 0.0f;
		m[1][1] = 1.0f;
		m[2][1] = v.y;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set translation matrix
		@note

		@param	fx displacement of x direction
		@param	fy displacement of y direction
		@param	fz displacement of z direction

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix33::setTransrationMatrix(const float fx, const float fy)
	{
		m[0][0] = 1.0f;
		m[1][0] = 0.0f;
		m[2][0] = fx;
		m[0][1] = 0.0f;
		m[1][1] = 1.0f;
		m[2][1] = fy;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set rotation matrix
		@note

		@param	axis of rotation
		@param	radian angle of rotation (radian)
				radian = (2.0f * PI) * (degree / 360.0f)

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix33::setRotationMarix(const float radian)
	{
		float s = cos(radian);
		float c = cos(radian);

		m[0][0] = c;
		m[1][0] = s;
		m[2][0] = 0.0f;
		m[0][1] = -s;
		m[1][1] = c;
		m[2][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set scaling matrix
		@note

		@param	factor enlargement factor

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix33::setScalingMatrix(const float factor)
	{
		m[0][0] = factor;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = factor;
		m[2][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set scaling matrix
		@note

		@param	v enlargement vtor

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix33::setScalingMatrix(const Vector2 &v)
	{
		m[0][0] = v.x;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = v.y;
		m[2][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set scaling matrix
		@note

		@param	fx enlargement factor of x direction
		@param	fy enlargement factor of y direction
		@param	fz enlargement factor of z direction

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix33::setScalingMatrix(const float fx, const float fy)
	{
		m[0][0] = fx;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = fy;
		m[2][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Copy constructor
		@note

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline Matrix33::Matrix33(const Matrix33 &m)
	{
		memcpy(serial, m.serial, sizeof(float) * 9);
	}

	/****************************************/
	/*!
		@brief	Constructor
		@note

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline Matrix33::Matrix33(
		const float f00, const float f01, const float f02,
		const float f10, const float f11, const float f12,
		const float f20, const float f21, const float f22)
	{
		set(f00, f01, f02, f10, f11, f12, f20, f21, f22);
	}

	/****************************************/
	/*!
		@brief	Set parameter
		@note

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix33::set(
		const float f00, const float f01, const float f02,
		const float f10, const float f11, const float f12,
		const float f20, const float f21, const float f22)
	{
		m[0][0] = f00;
		m[1][0] = f01;
		m[2][0] = f02;
		m[0][1] = f10;
		m[1][1] = f11;
		m[2][1] = f12;
		m[0][2] = f20;
		m[1][2] = f21;
		m[2][2] = f22;
	}

	/****************************************/
	/*!
		@brief	Unary operator (-)
		@note

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline Matrix33 Matrix33::operator-() const
	{
		return Matrix33(
			-m[0][0], -m[1][0], -m[2][0],
			-m[0][1], -m[1][1], -m[2][1],
			-m[0][2], -m[1][2], -m[2][2]);
	}

	//////////////////////////////////////////////////////////
	//						Matrix44						//
	//////////////////////////////////////////////////////////
	extern void (*_addMatrix44Matrix44)(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	extern void (*_subtractMatrix44Matrix44)(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	extern void (*_multiplyMatrix44Matrix44)(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	extern void (*_multiplyMatrix44Vector3)(Vector3 &vOut, const Matrix44 &m, const Vector3 &v);
	extern void (*_multiplyMatrix44Vector4)(Vector4 &vOut, const Matrix44 &m, const Vector4 &v);
	extern void (*_multiplyMatrix44Float)(Matrix44 &mOut, const Matrix44 &m, const float f);
	extern void (*_divideMatrix44Float)(Matrix44 &mOut, const Matrix44 &m, const float f);

	extern void (*_transposeMatrix44)(Matrix44 &mOut, const Matrix44 &m);
	extern void (*_inverseMatrix44)(Matrix44 &mOut, const Matrix44 &m);

	void _addMatrix44Matrix44Usual(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _subtractMatrix44Matrix44Usual(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _multiplyMatrix44Matrix44Usual(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _multiplyMatrix44Vector3Usual(Vector3 &vOut, const Matrix44 &m, const Vector3 &v);
	void _multiplyMatrix44Vector4Usual(Vector4 &vOut, const Matrix44 &m, const Vector4 &v);
	void _multiplyMatrix44FloatUsual(Matrix44 &mOut, const Matrix44 &m, const float f);
	void _divideMatrix44FloatUsual(Matrix44 &mOut, const Matrix44 &m, const float f);

	void _transposeMatrix44Usual(Matrix44 &mOut, const Matrix44 &m);
	void _setRotationMatrix44Usual(Matrix44 &m, const Vector3 &v, const float radian);

#if defined SIMDARCH_SSE
	void _addMatrix44Matrix44SSE(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _subtractMatrix44Matrix44SSE(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _multiplyMatrix44Matrix44SSE(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _multiplyMatrix44Vector3SSE(Vector3 &vOut, const Matrix44 &m, const Vector3 &v);
	void _multiplyMatrix44Vector4SSE(Vector4 &vOut, const Matrix44 &m, const Vector4 &v);
	void _multiplyMatrix44FloatSSE(Matrix44 &mOut, const Matrix44 &m, const float f);
	void _divideMatrix44FloatSSE(Matrix44 &mOut, const Matrix44 &m, const float f);

	void _transposeMatrix44SSE(Matrix44 &mOut, const Matrix44 &m);
	void _setRotationMatrix44SSE(Matrix44 &m, const Vector3 &v, const float radian);
#endif // SIMDARCH_SSE

#if defined SIMDARCH_NEON
	void _addMatrix44Matrix44NEON(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _subtractMatrix44Matrix44NEON(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _multiplyMatrix44Matrix44NEON(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2);
	void _multiplyMatrix44Vector3NEON(Vector3 &vOut, const Matrix44 &m, const Vector3 &v);
	void _multiplyMatrix44Vector4NEON(Vector4 &vOut, const Matrix44 &m, const Vector4 &v);
	void _multiplyMatrix44FloatNEON(Matrix44 &mOut, const Matrix44 &m, const float f);
	void _divideMatrix44FloatNEON(Matrix44 &mOut, const Matrix44 &m, const float f);

	void _transposeMatrix44NEON(Matrix44 &mOut, const Matrix44 &m);
	void _setRotationMatrix44NEON(Matrix44 &m, const Vector3 &v, const float radian);
#endif // SIMDARCH_NEON

	inline void addMatrix44Matrix44(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		_addMatrix44Matrix44(mOut, m1, m2);
	}

	inline void subtractMatrix44Matrix44(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		_subtractMatrix44Matrix44(mOut, m1, m2);
	}

	inline void multiplyMatrix44Matrix44(Matrix44 &mOut, const Matrix44 &m1, const Matrix44 &m2)
	{
		_multiplyMatrix44Matrix44(mOut, m1, m2);
	}

	inline void multiplyMatrix44Vector3(Vector3 &vOut, const Matrix44 &m, const Vector3 &v)
	{
		_multiplyMatrix44Vector3(vOut, m, v);
	}

	inline void multiplyMatrix44Vector4(Vector4 &vOut, const Matrix44 &m, const Vector4 &v)
	{
		_multiplyMatrix44Vector4(vOut, m, v);
	}

	inline void multiplyMatrix44Float(Matrix44 &mOut, const Matrix44 &m, const float f)
	{
		_multiplyMatrix44Float(mOut, m, f);
	}

	inline void divideMatrix44Float(Matrix44 &mOut, const Matrix44 &m, const float f)
	{
		_divideMatrix44Float(mOut, m, f);
	}

	inline void Matrix44::add(Matrix44 &mOut, const Matrix44 &m) const
	{
		addMatrix44Matrix44(mOut, *this, m);
	}

	inline void Matrix44::subtract(Matrix44 &mOut, const Matrix44 &m) const
	{
		subtractMatrix44Matrix44(mOut, *this, m);
	}

	inline void Matrix44::multiply(Matrix44 &mOut, const Matrix44 &m) const
	{
		multiplyMatrix44Matrix44(mOut, *this, m);
	}

	inline void Matrix44::multiply(Vector3 &vOut, const Vector3 &v) const
	{
		multiplyMatrix44Vector3(vOut, *this, v);
	}

	inline void Matrix44::multiply(Vector4 &vOut, const Vector4 &v) const
	{
		multiplyMatrix44Vector4(vOut, *this, v);
	}

	inline void Matrix44::multiply(Matrix44 &mOut, const float f) const
	{
		multiplyMatrix44Float(mOut, *this, f);
	}

	inline void Matrix44::divide(Matrix44 &mOut, const float f) const
	{
		divideMatrix44Float(mOut, *this, f);
	}

	inline Matrix44 Matrix44::operator+(const Matrix44 &m) const
	{
		Matrix44 retMat;
		addMatrix44Matrix44(retMat, *this, m);
		return retMat;
	}

	inline Matrix44 Matrix44::operator-(const Matrix44 &m) const
	{
		Matrix44 retMat;
		subtractMatrix44Matrix44(retMat, *this, m);
		return retMat;
	}

	inline Matrix44 Matrix44::operator*(const Matrix44 &m) const
	{
		Matrix44 retMat;
		multiplyMatrix44Matrix44(retMat, *this, m);
		return retMat;
	}

	inline Vector3 Matrix44::operator*(const Vector3 &v) const
	{
		Vector3 retVec;
		multiplyMatrix44Vector3(retVec, *this, v);
		return retVec;
	}

	inline Vector4 Matrix44::operator*(const Vector4 &v) const
	{
		Vector4 retVec;
		multiplyMatrix44Vector4(retVec, *this, v);
		return retVec;
	}

	inline Matrix44 Matrix44::operator*(const float f) const
	{
		Matrix44 retMat;
		multiplyMatrix44Float(retMat, *this, f);
		return retMat;
	}

	inline Matrix44 Matrix44::operator/(const float f) const
	{
		Matrix44 retMat;
		divideMatrix44Float(retMat, *this, f);
		return retMat;
	}

	inline void Matrix44::setUnitMatrix()
	{
		m[0][0] = 1.0f;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[3][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = 1.0f;
		m[2][1] = 0.0f;
		m[3][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
		m[3][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	inline void Matrix44::transpose()
	{
		_transposeMatrix44(*this, *this);
	}

	/****************************************/
	/*!
		@brief	Set translation matrix
		@note

		@param	v displacement

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setTransrationMatrix(const Vector3 &v)
	{
		m[0][0] = 1.0f;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[3][0] = v.x;
		m[0][1] = 0.0f;
		m[1][1] = 1.0f;
		m[2][1] = 0.0f;
		m[3][1] = v.y;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
		m[3][2] = v.z;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set translation matrix
		@note

		@param	fx displacement of x direction
		@param	fy displacement of y direction
		@param	fz displacement of z direction

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setTransrationMatrix(const float fx, const float fy, const float fz)
	{
		m[0][0] = 1.0f;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[3][0] = fx;
		m[0][1] = 0.0f;
		m[1][1] = 1.0f;
		m[2][1] = 0.0f;
		m[3][1] = fy;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
		m[3][2] = fz;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set rotation matrix
		@note

		@param	axis of rotation
		@param	radian angle of rotation (radian)
				radian = (2.0f * PI) * (degree / 360.0f)

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setRotationMarix(const Vector3 &v, const float radian)
	{
		//_setRotationMatrix44SSE(*this, v, radian);
	}

	/****************************************/
	/*!
		@brief	Set x axis rotation matrix
		@note

		@param	radian angle of rotation (radian)
				radian = (2.0f * PI) * (degree / 360.0f)

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setXRotationMatrix(const float radian)
	{
		float s, c;
		s = sin(radian);
		c = cos(radian);

		m[0][0] = 1.0f;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[3][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = c;
		m[2][1] = -s;
		m[3][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = s;
		m[2][2] = c;
		m[3][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set y axis rotation matrix
		@note

		@param	radian angle of rotation (radian)
				radian = (2.0f * PI) * (degree / 360.0f)

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setYRotationMatrix(const float radian)
	{
		float s, c;
		s = sin(radian);
		c = cos(radian);

		m[0][0] = c;
		m[1][0] = 0.0f;
		m[2][0] = s;
		m[3][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = 1.0f;
		m[2][1] = 0.0f;
		m[3][1] = 0.0f;
		m[0][2] = -s;
		m[1][2] = 0.0f;
		m[2][2] = c;
		m[3][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set z axis rotation matrix
		@note

		@param	radian angle of rotation (radian)
				radian = (2.0f * PI) * (degree / 360.0f)

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setZRotationMatrix(const float radian)
	{
		float s, c;
		s = sin(radian);
		c = cos(radian);

		m[0][0] = c;
		m[1][0] = -s;
		m[2][0] = 0.0f;
		m[3][0] = 0.0f;
		m[0][1] = s;
		m[1][1] = c;
		m[2][1] = 0.0f;
		m[3][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = 1.0f;
		m[3][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set scaling matrix
		@note

		@param	factor enlargement factor

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setScalingMatrix(const float factor)
	{
		m[0][0] = factor;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[3][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = factor;
		m[2][1] = 0.0f;
		m[3][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = factor;
		m[3][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set scaling matrix
		@note

		@param	v enlargement vtor

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setScalingMatrix(const Vector3 &v)
	{
		m[0][0] = v.x;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[3][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = v.y;
		m[2][1] = 0.0f;
		m[3][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = v.z;
		m[3][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Set scaling matrix
		@note

		@param	fx enlargement factor of x direction
		@param	fy enlargement factor of y direction
		@param	fz enlargement factor of z direction

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::setScalingMatrix(const float fx, const float fy, const float fz)
	{
		m[0][0] = fx;
		m[1][0] = 0.0f;
		m[2][0] = 0.0f;
		m[3][0] = 0.0f;
		m[0][1] = 0.0f;
		m[1][1] = fy;
		m[2][1] = 0.0f;
		m[3][1] = 0.0f;
		m[0][2] = 0.0f;
		m[1][2] = 0.0f;
		m[2][2] = fz;
		m[3][2] = 0.0f;
		m[0][3] = 0.0f;
		m[1][3] = 0.0f;
		m[2][3] = 0.0f;
		m[3][3] = 1.0f;
	}

	/****************************************/
	/*!
		@brief	Copy constructor
		@note

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline Matrix44::Matrix44(const Matrix44 &m)
	{
		memcpy(serial, m.serial, sizeof(float) * 16);
	}

	/****************************************/
	/*!
		@brief	Constructor
		@note

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline Matrix44::Matrix44(
		const float f00, const float f01, const float f02, const float f03,
		const float f10, const float f11, const float f12, const float f13,
		const float f20, const float f21, const float f22, const float f23,
		const float f30, const float f31, const float f32, const float f33)
	{
		set(f00, f01, f02, f03, f10, f11, f12, f13, f20, f21, f22, f23, f30, f31, f32, f33);
	}

	/****************************************/
	/*!
		@brief	Set parameter
		@note

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline void Matrix44::set(
		const float f00, const float f01, const float f02, const float f03,
		const float f10, const float f11, const float f12, const float f13,
		const float f20, const float f21, const float f22, const float f23,
		const float f30, const float f31, const float f32, const float f33)
	{
		m[0][0] = f00;
		m[1][0] = f01;
		m[2][0] = f02;
		m[3][0] = f03;
		m[0][1] = f10;
		m[1][1] = f11;
		m[2][1] = f12;
		m[3][1] = f13;
		m[0][2] = f20;
		m[1][2] = f21;
		m[2][2] = f22;
		m[3][2] = f23;
		m[0][3] = f30;
		m[1][3] = f31;
		m[2][3] = f32;
		m[3][3] = f33;
	}

	/****************************************/
	/*!
		@brief	Unary operator (-)
		@note

		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	inline Matrix44 Matrix44::operator-() const
	{
		return Matrix44(
			-m[0][0], -m[1][0], -m[2][0], -m[3][0],
			-m[0][1], -m[1][1], -m[2][1], -m[3][1],
			-m[0][2], -m[1][2], -m[2][2], -m[3][2],
			-m[0][3], -m[1][3], -m[2][3], -m[3][3]);
	}

}; // namespace S3D

#endif // S3D_MATH_MATRIX_INL_H
