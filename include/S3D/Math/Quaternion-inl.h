/******************************************************************/
/*!
	@file	Matrix-inl.h
	@brief	Inline definition for matrix
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 10, 2020
*/
/******************************************************************/

#ifndef S3D_MATH_QUATERNION_INL_H
#define S3D_MATH_QUATERNION_INL_H

#include "S3D/Common.h"

namespace S3D
{

	//////////////////////////////////////////////////////////
	//						Quaternion4						//
	//////////////////////////////////////////////////////////
	inline void addQuaternion4Quaternion4(Quaternion4 &qOut, const Quaternion4 &q1, const Quaternion4 &q2)
	{
		qOut.x = q1.x + q2.x;
		qOut.y = q1.y + q2.y;
		qOut.z = q1.z + q2.z;
		qOut.w = q1.w + q2.w;
	}

	inline void subtractQuaternion4Quaternion4(Quaternion4 &qOut, const Quaternion4 &q1, const Quaternion4 &q2)
	{
		qOut.x = q1.x - q2.x;
		qOut.y = q1.y - q2.y;
		qOut.z = q1.z - q2.z;
		qOut.w = q1.w - q2.w;
	}

	inline void multiplyQuaternion4Quaternion4(Quaternion4 &qOut, const Quaternion4 &q1, const Quaternion4 &q2)
	{
		float x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
		float y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
		float z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
		float w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
		qOut.set(x, y, z, w);
	}

	inline void multiplyQuaternion4Float(Quaternion4 &qOut, const Quaternion4 &q, const float f)
	{
		qOut.x = q.x * f;
		qOut.y = q.y * f;
		qOut.z = q.z * f;
		qOut.w = q.w * f;
	}

	inline void divideQuaternion4Float(Quaternion4 &qOut, const Quaternion4 &q, const float f)
	{
		qOut.x = q.x / f;
		qOut.y = q.y / f;
		qOut.z = q.z / f;
		qOut.w = q.w / f;
	}

	inline Quaternion4 Quaternion4::operator+(const Quaternion4 &q) const
	{
		Quaternion4 qOut;
		addQuaternion4Quaternion4(qOut, *this, q);
		return qOut;
	}

	inline Quaternion4 Quaternion4::operator-(const Quaternion4 &q) const
	{
		Quaternion4 qOut;
		subtractQuaternion4Quaternion4(qOut, *this, q);
		return qOut;
	}

	inline Quaternion4 Quaternion4::operator*(const Quaternion4 &q) const
	{
		Quaternion4 qOut;
		multiplyQuaternion4Quaternion4(qOut, *this, q);
		return qOut;
	}

	inline Quaternion4 Quaternion4::operator*(const float f) const
	{
		Quaternion4 qOut;
		multiplyQuaternion4Float(qOut, *this, f);
		return qOut;
	}

	inline Quaternion4 Quaternion4::operator/(const float f) const
	{
		Quaternion4 qOut;
		divideQuaternion4Float(qOut, *this, f);
		return qOut;
	}

	inline void Quaternion4::add(Quaternion4 &qOut, const Quaternion4 &q) const
	{
		addQuaternion4Quaternion4(qOut, *this, q);
	}

	inline void Quaternion4::subtract(Quaternion4 &qOut, const Quaternion4 &q) const
	{
		subtractQuaternion4Quaternion4(qOut, *this, q);
	}

	inline void Quaternion4::multiply(Quaternion4 &qOut, const Quaternion4 &q) const
	{
		multiplyQuaternion4Quaternion4(qOut, *this, q);
	}

	inline void Quaternion4::multiply(Quaternion4 &qOut, const float f) const
	{
		multiplyQuaternion4Float(qOut, *this, f);
	}

	inline void Quaternion4::divide(Quaternion4 &qOut, const float f) const
	{
		divideQuaternion4Float(qOut, *this, f);
	}

	inline void convertQuaternion4ToMatrix44(Matrix44 &m, const Quaternion4 &q)
	{
		m.m[0][0] = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		m.m[1][0] = 2.0f * (q.x * q.y - q.w * q.z);
		m.m[2][0] = 2.0f * (q.x * q.z + q.w * q.y);
		m.m[3][0] = 0.0f;

		m.m[0][1] = 2.0f * (q.x * q.y + q.w * q.z);
		m.m[1][1] = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
		m.m[2][1] = 2.0f * (q.y * q.z - q.w * q.x);
		m.m[3][1] = 0.0f;

		m.m[0][2] = 2.0f * (q.x * q.z - q.w * q.y);
		m.m[1][2] = 2.0f * (q.y * q.z + q.w * q.x);
		m.m[2][2] = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
		m.m[3][2] = 0.0f;

		m.m[0][3] = 0.0f;
		m.m[1][3] = 0.0f;
		m.m[2][3] = 0.0f;
		m.m[3][3] = 1.0f;
	}

	inline void convertMatrix44ToQuaternion4(Quaternion4 &q, const Matrix44 &m)
	{
		float s = 0.0f;
		float trace = m.m[0][0] + m.m[1][1] + m.m[2][2] + 1.0f;

		if (trace >= 1.0f)
		{
			s = 0.5f / ::sqrt(trace);
			q.w = 0.25f / s;
			q.x = (m.m[1][2] - m.m[2][1]) * s;
			q.y = (m.m[0][2] - m.m[2][0]) * s;
			q.z = (m.m[0][1] - m.m[1][0]) * s;
		}
		else
		{
			float max = m.m[1][1] > m.m[2][2] ? m.m[1][1] : m.m[2][2];

			if (max < m.m[0][0])
			{
				s = sqrtf(m.m[0][0] - (m.m[1][1] + m.m[2][2]) + 1.0f);
				q.x = s * 0.5f;
				s = 0.5f / s;
				q.y = (m.m[0][1] + m.m[1][0]) * s;
				q.z = (m.m[2][0] + m.m[0][2]) * s;
				q.w = (m.m[1][2] - m.m[2][1]) * s;
			}
			else if (max == m.m[1][1])
			{
				s = sqrtf(m.m[1][1] - (m.m[2][2] + m.m[0][0]) + 1.0f);
				q.y = s * 0.5f;
				s = 0.5f / s;
				q.x = (m.m[0][1] + m.m[1][0]) * s;
				q.z = (m.m[1][2] - m.m[2][1]) * s;
				q.w = (m.m[2][0] + m.m[0][2]) * s;
			}
			else
			{
				s = sqrtf(m.m[2][2] - (m.m[0][0] + m.m[0][0]) + 1.0f);
				q.z = s * 0.5f;
				s = 0.5f / s;
				q.x = (m.m[2][0] + m.m[0][2]) * s;
				q.y = (m.m[1][2] - m.m[2][1]) * s;
				q.w = (m.m[0][1] + m.m[1][0]) * s;
			}
		}
	}

	inline void convertAxisAngleToQuaternion4(Quaternion4 &q, const Vector3 &v, const float radian)
	{
		float s = sin(radian * 0.5f);
		float c = cos(radian * 0.5f);
		q.x = s * v.x;
		q.y = s * v.y;
		q.z = s * v.z;
		q.w = c;
	}

	inline void convertQuaternion4ToAxisAngle(Vector3 &v, float &radian, const Quaternion4 &q)
	{
		radian = acos(q.w) * 2.0f;
		float s = sin(radian * 0.5f);
		if (s == 0.0f)
		{
			v.setZero();
		}
		else
		{
			v = Vector3(q.x, q.y, q.z) / s;
		}
	}

	inline void convertVector3WithQuaternion4(Vector3 &vOut, const Quaternion4 &q, const Vector3 &v)
	{
		const float rx = v.x * q.w + v.y * -q.z + v.z * q.y;
		const float ry = v.x * q.z + v.y * q.w + v.z * -q.x;
		const float rz = v.x * -q.y + v.y * q.x + v.z * q.w;
		const float rw = v.x * q.x + v.y * q.y + v.z * q.z;

		vOut.x = q.x * rw + q.y * rz + q.z * -ry + q.w * rx;
		vOut.y = q.x * -rz + q.y * rw + q.z * rx + q.w * ry;
		vOut.z = q.x * ry + q.y * -rx + q.z * rw + q.w * rz;
	}

	inline void Quaternion4::inverse()
	{
		float norm = this->getNorm();
		if (norm == 0)
			return;
		norm = norm * norm;
		x = -x / norm;
		y = -y / norm;
		z = -z / norm;
		w /= norm;
	}

	inline void Quaternion4::toMatrix44(Matrix44 &m) const
	{
		convertQuaternion4ToMatrix44(m, *this);
	}

	inline void Quaternion4::convert(const Matrix44 &m)
	{
		convertMatrix44ToQuaternion4(*this, m);
	}

	inline void Quaternion4::toAxisAngle(Vector3 &v, float &radian) const
	{
		convertQuaternion4ToAxisAngle(v, radian, *this);
	}

	inline void Quaternion4::convert(const Vector3 &v, const float radian)
	{
		convertAxisAngleToQuaternion4(*this, v, radian);
	}

	inline void Quaternion4::convertVector(Vector3 &vOut, const Vector3 &v) const
	{
		convertVector3WithQuaternion4(vOut, *this, v);
	}

}; // namespace S3D

#endif // S3D_MATH_QUATERNION_INL_H
