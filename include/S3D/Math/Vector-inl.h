/******************************************************************/
/*!
	@file	Vector-inl.h
	@brief	Inline definition for vtor
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 10, 2020
*/
/******************************************************************/

#ifndef S3D_MATH_VECTOR_INL_H
#define S3D_MATH_VECTOR_INL_H

#include "S3D/Common.h"

namespace S3D
{

	//////////////////////////////////////////////////////////
	//						Vector2							//
	//////////////////////////////////////////////////////////
	inline void addVector2Vector2(Vector2 &vOut, const Vector2 &v1, const Vector2 &v2)
	{
		vOut.x = v1.x + v2.x;
		vOut.y = v1.y + v2.y;
	}

	inline void subtractVector2Vector2(Vector2 &vOut, const Vector2 &v1, const Vector2 &v2)
	{
		vOut.x = v1.x - v2.x;
		vOut.y = v1.y - v2.y;
	}

	inline void multiplyVector2Vector2(Vector2 &vOut, const Vector2 &v1, const Vector2 &v2)
	{
		vOut.x = v1.x * v2.x;
		vOut.y = v1.y * v2.y;
	}

	inline void multiplyVector2Float(Vector2 &vOut, const Vector2 &v, const float f)
	{
		vOut.x = v.x * f;
		vOut.y = v.y * f;
	}

	inline void divideVector2Vector2(Vector2 &vOut, const Vector2 &v1, const Vector2 &v2)
	{
		vOut.x = v1.x / v2.x;
		vOut.y = v1.y / v2.y;
	}

	inline void divideVector2Float(Vector2 &vOut, const Vector2 &v, const float f)
	{
		vOut.x = v.x / f;
		vOut.y = v.y / f;
	}

	inline void Vector2::add(Vector2 &vOut, const Vector2 &v) const
	{
		addVector2Vector2(vOut, *this, v);
	}

	inline void Vector2::subtract(Vector2 &vOut, const Vector2 &v) const
	{
		subtractVector2Vector2(vOut, *this, v);
	}

	inline void Vector2::multiply(Vector2 &vOut, const Vector2 &v) const
	{
		multiplyVector2Vector2(vOut, *this, v);
	}

	inline void Vector2::multiply(Vector2 &vOut, const float f) const
	{
		multiplyVector2Float(vOut, *this, f);
	}

	inline void Vector2::divide(Vector2 &vOut, const Vector2 &v) const
	{
		divideVector2Vector2(vOut, *this, v);
	}

	inline void Vector2::divide(Vector2 &vOut, const float f) const
	{
		divideVector2Float(vOut, *this, f);
	}

	inline Vector2 Vector2::operator+(const Vector2 &v) const
	{
		Vector2 retVec;
		addVector2Vector2(retVec, *this, v);
		return retVec;
	}

	inline Vector2 Vector2::operator-(const Vector2 &v) const
	{
		Vector2 retVec;
		subtractVector2Vector2(retVec, *this, v);
		return retVec;
	}

	inline Vector2 Vector2::operator*(const Vector2 &v) const
	{
		Vector2 retVec;
		multiplyVector2Vector2(retVec, *this, v);
		return retVec;
	}

	inline Vector2 Vector2::operator*(const float f) const
	{
		Vector2 retVec;
		multiplyVector2Float(retVec, *this, f);
		return retVec;
	}

	inline Vector2 Vector2::operator/(const Vector2 &v) const
	{
		Vector2 retVec;
		divideVector2Vector2(retVec, *this, v);
		return retVec;
	}

	inline Vector2 Vector2::operator/(const float f) const
	{
		Vector2 retVec;
		divideVector2Float(retVec, *this, f);
		return retVec;
	}

	//////////////////////////////////////////////////////////
	//						Vector3							//
	//////////////////////////////////////////////////////////
	inline void addVector3Vector3(Vector3 &vOut, const Vector3 &v1, const Vector3 &v2)
	{
		vOut.x = v1.x + v2.x;
		vOut.y = v1.y + v2.y;
		vOut.z = v1.z + v2.z;
	}

	inline void subtractVector3Vector3(Vector3 &vOut, const Vector3 &v1, const Vector3 &v2)
	{
		vOut.x = v1.x - v2.x;
		vOut.y = v1.y - v2.y;
		vOut.z = v1.z - v2.z;
	}

	inline void multiplyVector3Vector3(Vector3 &vOut, const Vector3 &v1, const Vector3 &v2)
	{
		vOut.x = v1.x * v2.x;
		vOut.y = v1.y * v2.y;
		vOut.z = v1.z * v2.z;
	}

	inline void multiplyVector3Float(Vector3 &vOut, const Vector3 &v, const float f)
	{
		vOut.x = v.x * f;
		vOut.y = v.y * f;
		vOut.z = v.z * f;
	}

	inline void divideVector3Vector3(Vector3 &vOut, const Vector3 &v1, const Vector3 &v2)
	{
		vOut.x = v1.x / v2.x;
		vOut.y = v1.y / v2.y;
		vOut.z = v1.z / v2.z;
	}

	inline void divideVector3Float(Vector3 &vOut, const Vector3 &v, const float f)
	{
		vOut.x = v.x / f;
		vOut.y = v.y / f;
		vOut.z = v.z / f;
	}

	inline void Vector3::add(Vector3 &vOut, const Vector3 &v) const
	{
		addVector3Vector3(vOut, *this, v);
	}

	inline void Vector3::subtract(Vector3 &vOut, const Vector3 &v) const
	{
		subtractVector3Vector3(vOut, *this, v);
	}

	inline void Vector3::multiply(Vector3 &vOut, const Vector3 &v) const
	{
		multiplyVector3Vector3(vOut, *this, v);
	}

	inline void Vector3::multiply(Vector3 &vOut, const float f) const
	{
		multiplyVector3Float(vOut, *this, f);
	}

	inline void Vector3::divide(Vector3 &vOut, const Vector3 &v) const
	{
		divideVector3Vector3(vOut, *this, v);
	}

	inline void Vector3::divide(Vector3 &vOut, const float f) const
	{
		divideVector3Float(vOut, *this, f);
	}

	inline Vector3 Vector3::operator+(const Vector3 &v) const
	{
		Vector3 retVec;
		addVector3Vector3(retVec, *this, v);
		return retVec;
	}

	inline Vector3 Vector3::operator-(const Vector3 &v) const
	{
		Vector3 retVec;
		subtractVector3Vector3(retVec, *this, v);
		return retVec;
	}

	inline Vector3 Vector3::operator*(const Vector3 &v) const
	{
		Vector3 retVec;
		multiplyVector3Vector3(retVec, *this, v);
		return retVec;
	}

	inline Vector3 Vector3::operator*(const float f) const
	{
		Vector3 retVec;
		multiplyVector3Float(retVec, *this, f);
		return retVec;
	}

	inline Vector3 Vector3::operator/(const Vector3 &v) const
	{
		Vector3 retVec;
		divideVector3Vector3(retVec, *this, v);
		return retVec;
	}

	inline Vector3 Vector3::operator/(const float f) const
	{
		Vector3 retVec;
		divideVector3Float(retVec, *this, f);
		return retVec;
	}

	//////////////////////////////////////////////////////////
	//						Vector4							//
	//////////////////////////////////////////////////////////
	inline void addVector4Vector4(Vector4 &vOut, const Vector4 &v1, const Vector4 &v2)
	{
		vOut.x = v1.x + v2.x;
		vOut.y = v1.y + v2.y;
		vOut.z = v1.z + v2.z;
		vOut.w = v1.w + v2.w;
	}

	inline void subtractVector4Vector4(Vector4 &vOut, const Vector4 &v1, const Vector4 &v2)
	{
		vOut.x = v1.x - v2.x;
		vOut.y = v1.y - v2.y;
		vOut.z = v1.z - v2.z;
		vOut.w = v1.w - v2.w;
	}

	inline void multiplyVector4Vector4(Vector4 &vOut, const Vector4 &v1, const Vector4 &v2)
	{
		vOut.x = v1.x * v2.x;
		vOut.y = v1.y * v2.y;
		vOut.z = v1.z * v2.z;
		vOut.w = v1.w * v2.w;
	}

	inline void multiplyVector4Float(Vector4 &vOut, const Vector4 &v, const float f)
	{
		vOut.x = v.x * f;
		vOut.y = v.y * f;
		vOut.z = v.z * f;
		vOut.w = v.w * f;
	}

	inline void divideVector4Vector4(Vector4 &vOut, const Vector4 &v1, const Vector4 &v2)
	{
		vOut.x = v1.x / v2.x;
		vOut.y = v1.y / v2.y;
		vOut.z = v1.z / v2.z;
		vOut.w = v1.w / v2.w;
	}

	inline void divideVector4Float(Vector4 &vOut, const Vector4 &v, const float f)
	{
		vOut.x = v.x / f;
		vOut.y = v.y / f;
		vOut.z = v.z / f;
		vOut.w = v.w / f;
	}

	inline void Vector4::add(Vector4 &vOut, const Vector4 &v) const
	{
		addVector4Vector4(vOut, *this, v);
	}

	inline void Vector4::subtract(Vector4 &vOut, const Vector4 &v) const
	{
		subtractVector4Vector4(vOut, *this, v);
	}

	inline void Vector4::multiply(Vector4 &vOut, const Vector4 &v) const
	{
		multiplyVector4Vector4(vOut, *this, v);
	}

	inline void Vector4::multiply(Vector4 &vOut, const float f) const
	{
		multiplyVector4Float(vOut, *this, f);
	}

	inline void Vector4::divide(Vector4 &vOut, const Vector4 &v) const
	{
		divideVector4Vector4(vOut, *this, v);
	}

	inline void Vector4::divide(Vector4 &vOut, const float f) const
	{
		divideVector4Float(vOut, *this, f);
	}

	inline Vector4 Vector4::operator+(const Vector4 &v) const
	{
		Vector4 retVec;
		addVector4Vector4(retVec, *this, v);
		return retVec;
	}

	inline Vector4 Vector4::operator-(const Vector4 &v) const
	{
		Vector4 retVec;
		subtractVector4Vector4(retVec, *this, v);
		return retVec;
	}

	inline Vector4 Vector4::operator*(const Vector4 &v) const
	{
		Vector4 retVec;
		multiplyVector4Vector4(retVec, *this, v);
		return retVec;
	}

	inline Vector4 Vector4::operator*(const float f) const
	{
		Vector4 retVec;
		multiplyVector4Float(retVec, *this, f);
		return retVec;
	}

	inline Vector4 Vector4::operator/(const Vector4 &v) const
	{
		Vector4 retVec;
		divideVector4Vector4(retVec, *this, v);
		return retVec;
	}

	inline Vector4 Vector4::operator/(const float f) const
	{
		Vector4 retVec;
		divideVector4Float(retVec, *this, f);
		return retVec;
	}

}; // namespace S3D

#endif // S3D_MATH_VECTOR_INL_H
