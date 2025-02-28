/******************************************************************/
/*!
	@file	MathemaricsTypes.h
	@brief	Classes for mathematics
	@note
	@todo
	@bug

	@author	Naoto Nakamura
	@date	Mar. 10, 2020
*/
/******************************************************************/

#ifndef S3D_MATH_MATHEMATICSTYPES_H
#define S3D_MATH_MATHEMATICSTYPES_H

#include "S3D/Common.h"
#include "S3D/Foundation/CPU.h"

namespace S3D
{
	//////////////////////////////////////////////////////
	//				forward declarations				//
	//////////////////////////////////////////////////////
	// implemented
	class Point2;
	class Pointf2;
	class Size2;
	class Sizef2;
	class Rect4;
	class Rectf4;
	class Vector2;
	class Vector3;
	class Vector4;
	class Matrix33;
	class Matrix44;
	class Quaternion4;
	class Cube;
	class Cuboid;

	//////////////////////////////////////////////////////
	//				class declarations					//
	//////////////////////////////////////////////////////
	/****************************************/
	/*!
		@class	Point2
		@brief	2D position(integer)
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Point2
	{
	public:
		// constructor
		Point2() {}
		Point2(const int ix, const int iy) : x(ix), y(iy) {}

		operator Pointf2();

		// property
		void set(const int ix, const int iy)
		{
			x = ix;
			y = iy;
		}

		// unary operators
		Point2 operator+() const { return *this; }
		Point2 operator-() const { return Point2(-x, -y); }

		// binary operators
		Point2 operator+(const Point2 &p) const { return Point2(x + p.x, y + p.y); }
		Point2 operator-(const Point2 &p) const { return Point2(x - p.x, y - p.y); }

		// compound assignment operators
		Point2 &operator+=(const Point2 &p)
		{
			*this = *this + p;
			return *this;
		}
		Point2 &operator-=(const Point2 &p)
		{
			*this = *this - p;
			return *this;
		}

		// comparison operators
		bool operator==(const Point2 &p) const { return x == p.x && y == p.y; }
		bool operator!=(const Point2 &p) const { return x != p.x || y != p.y; }

		// tools
		void setZero()
		{
			x = 0;
			y = 0;
		}

	public:
		int x; //!< x position
		int y; //!< y position
	};

	/****************************************/
	/*!
		@class	Pointf2
		@brief	2D position(float)
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Pointf2
	{
	public:
		// constructor
		Pointf2() {}
		Pointf2(const float ix, const float iy) : x(ix), y(iy) {}

		operator Point2();

		// property
		void set(const float ix, const float iy)
		{
			x = ix;
			y = iy;
		}

		// unary operators
		Pointf2 operator+() const { return *this; }
		Pointf2 operator-() const { return Pointf2(-x, -y); }

		// binary operators
		Pointf2 operator+(const Pointf2 &p) const { return Pointf2(x + p.x, y + p.y); }
		Pointf2 operator-(const Pointf2 &p) const { return Pointf2(x - p.x, y - p.y); }

		// compound assignment operators
		Pointf2 &operator+=(const Pointf2 &p)
		{
			*this = *this + p;
			return *this;
		}
		Pointf2 &operator-=(const Pointf2 &p)
		{
			*this = *this - p;
			return *this;
		}

		// comparison operators
		bool operator==(const Pointf2 &p) const { return x == p.x && y == p.y; }
		bool operator!=(const Pointf2 &p) const { return x != p.x || y != p.y; }

		// tools
		void setZero()
		{
			x = 0.0f;
			y = 0.0f;
		}

	public:
		float x; //!< x position
		float y; //!< y position
	};

	inline Point2::operator Pointf2() { return Pointf2((float)x, (float)y); }
	inline Pointf2::operator Point2() { return Point2((int)x, (int)y); }

	/****************************************/
	/*!
		@class	Size2
		@brief	2D Size(integer)
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Size2
	{
	public:
		// constructor
		Size2() {}
		Size2(const int iwidth, const int iheight) : width(iwidth), height(iheight) {}

		operator Sizef2();

		// property
		void set(const int iwidth, const int iheight)
		{
			width = iwidth;
			height = iheight;
		}

		// unary operators
		Size2 operator+() const { return *this; }
		Size2 operator-() const { return Size2(-width, -height); }

		// binary operators
		Size2 operator+(const Size2 &size) const { return Size2(width + size.width, height + size.height); }
		Size2 operator-(const Size2 &size) const { return Size2(width - size.width, height - size.height); }

		// compound assignment operators
		Size2 &operator+=(const Size2 &size)
		{
			*this = *this + size;
			return *this;
		}
		Size2 &operator-=(const Size2 &size)
		{
			*this = *this - size;
			return *this;
		}

		// comparison operators
		bool operator==(const Size2 &size) const { return width == size.width && height == size.height; }
		bool operator!=(const Size2 &size) const { return width != size.width || height != size.height; }

		// tools
		void setZero()
		{
			width = 0;
			height = 0;
		}

	public:
		int width;	//!< horizontal size
		int height; //!< vertical size
	};

	/****************************************/
	/*!
		@class	Sizef2
		@brief	2D Size(float)
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Sizef2
	{
	public:
		// constructor
		Sizef2() {}
		Sizef2(const float iwidth, const float iheight) : width(iwidth), height(iheight) {}

		operator Size2();

		// property
		void set(const float iwidth, const float iheight)
		{
			width = iwidth;
			height = iheight;
		}

		// unary operators
		Sizef2 operator+() const { return *this; }
		Sizef2 operator-() const { return Sizef2(-width, -height); }

		// binary operators
		Sizef2 operator+(const Sizef2 &size) const { return Sizef2(width + size.width, height + size.height); }
		Sizef2 operator-(const Sizef2 &size) const { return Sizef2(width - size.width, height - size.height); }

		// compound assignment operators
		Sizef2 &operator+=(const Sizef2 &size)
		{
			*this = *this + size;
			return *this;
		}
		Sizef2 &operator-=(const Sizef2 &size)
		{
			*this = *this - size;
			return *this;
		}

		// comparison operators
		bool operator==(const Sizef2 &size) const { return width == size.width && height == size.height; }
		bool operator!=(const Sizef2 &size) const { return width != size.width || height != size.height; }

		// tools
		void setZero()
		{
			width = 0.0f;
			height = 0.0f;
		}

	public:
		float width;  //!< horizontal size
		float height; //!< vertical size
	};

	inline Size2::operator Sizef2() { return Sizef2((float)width, (float)height); }
	inline Sizef2::operator Size2() { return Size2((int)width, (int)height); }

	/****************************************/
	/*!
		@class	Rect4
		@brief	2D Rectangle(integer)
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Rect4
	{
	public:
		// constructor
		Rect4() {}
		Rect4(const int ix, const int iy, const int iwidth, const int iheight) : x(ix), y(iy), width(iwidth), height(iheight) {}

		operator Rectf4();

		// property
		void set(const int ix, const int iy, const int iwidth, const int iheight)
		{
			x = ix;
			y = iy;
			width = iwidth;
			height = iheight;
		}

		void setOrigin(const Point2 &p)
		{
			x = p.x;
			y = p.y;
		}
		void setSize(const Size2 &s)
		{
			width = s.width;
			height = s.height;
		}

		// tools
		void setZero()
		{
			x = 0;
			y = 0;
			width = 0;
			height = 0;
		}

		bool pointInRect(const Point2 &p) const { return (p.x >= x && p.x <= x + width && p.y >= y && p.y <= y + height); }

	public:
		int x;		//!< position (horizonal)
		int y;		//!< position (vertical)
		int width;	//!< size (horizonal)
		int height; //!< size (vertical)
	};

	/****************************************/
	/*!
		@class	Rectf4
		@brief	2D Rectangle(float)
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Rectf4
	{
	public:
		// constructor
		Rectf4() {}
		Rectf4(const float fx, const float fy, const float fwidth, const float fheight) : x(fx), y(fy), width(fwidth), height(fheight) {}

		operator Rect4();

		// property
		void set(const float fx, const float fy, const float fwidth, const float fheight)
		{
			x = fx;
			y = fy;
			width = fwidth;
			height = fheight;
		}

		void setOrigin(const Pointf2 &p)
		{
			x = p.x;
			y = p.y;
		}
		void setSize(const Sizef2 &s)
		{
			width = s.width;
			height = s.height;
		}

		// tools
		void setZero()
		{
			x = 0.0f;
			y = 0.0f;
			width = 0.0f;
			height = 0.0f;
		}

		bool pointInRect(const Pointf2 &p) const { return (p.x >= x && p.x <= x + width && p.y >= y && p.y <= y + height); }

	public:
		float x;	  //!< left edge position (horizonal)
		float y;	  //!< rignt edge position (horizonal)
		float width;  //!< top edge position (vertical)
		float height; //!< bottom edge position (vertical)
	};

	inline Rect4::operator Rectf4() { return Rectf4((float)x, (float)y, (float)width, (float)height); }
	inline Rectf4::operator Rect4() { return Rect4((int)x, (int)y, (int)width, (int)height); }

	/****************************************/
	/*!
		@class	Vector2
		@brief	2D Vector
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Vector2
	{
	public:
		// constructor
		Vector2() {}
		Vector2(const float fx, const float fy) : x(fx), y(fy) {}

		// property
		void set(const float fx, const float fy)
		{
			x = fx;
			y = fy;
		}

		// unary operators
		Vector2 operator+() const { return *this; }
		Vector2 operator-() const { return Vector2(-x, -y); }

		// binary operators
		Vector2 operator+(const Vector2 &v) const;
		Vector2 operator-(const Vector2 &v) const;
		Vector2 operator*(const Vector2 &v) const;
		Vector2 operator*(const float f) const;
		Vector2 operator/(const Vector2 &v) const;
		Vector2 operator/(const float f) const;

		// compound assignment operators
		Vector2 &operator+=(const Vector2 &v)
		{
			*this = *this + v;
			return *this;
		}
		Vector2 &operator-=(const Vector2 &v)
		{
			*this = *this - v;
			return *this;
		}
		Vector2 &operator*=(const Vector2 &v)
		{
			*this = *this * v;
			return *this;
		}
		Vector2 &operator*=(const float f)
		{
			*this = *this * f;
			return *this;
		}
		Vector2 &operator/=(const Vector2 &v)
		{
			*this = *this / v;
			return *this;
		}
		Vector2 &operator/=(const float f)
		{
			*this = *this / f;
			return *this;
		}

		// comparison operators
		bool operator==(const Vector2 &v) const { return x == v.x && y == v.y; }
		bool operator!=(const Vector2 &v) const { return x != v.x || y != v.y; }

		// operations
		inline void add(Vector2 &vOut, const Vector2 &v) const;
		inline void subtract(Vector2 &vOut, const Vector2 &v) const;
		inline void multiply(Vector2 &vOut, const Vector2 &v) const;
		inline void multiply(Vector2 &vOut, const float f) const;
		inline void divide(Vector2 &vOut, const Vector2 &v) const;
		inline void divide(Vector2 &vOut, const float f) const;

		// tools
		void setZero()
		{
			x = 0.0f;
			y = 0.0f;
		}

		float length() const { return ::sqrt(x * x + y * y); }
		float innerProduct(const Vector2 &v) const { return x * v.x + y * v.y; }
		void normalize() { *this / length(); }

	public:
		union
		{
			struct
			{
				float x; //!< x position
				float y; //!< y position
			};
			float data[2];
		};
	};

	/****************************************/
	/*!
		@class	Vector3
		@brief	3D Vector
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Vector3
	{
	public:
		// constructor
		Vector3() { data[3] = 1.0f; }
		Vector3(const float fx, const float fy, const float fz) : x(fx), y(fy), z(fz) { data[3] = 1.0f; }

		// property
		void set(const float fx, const float fy, const float fz)
		{
			x = fx;
			y = fy;
			z = fz;
		}

		// unary operators
		Vector3 operator+() const { return *this; }
		Vector3 operator-() const { return Vector3(-x, -y, -z); }

		// binary operators
		Vector3 operator+(const Vector3 &v) const;
		Vector3 operator-(const Vector3 &v) const;
		Vector3 operator*(const Vector3 &v) const;
		Vector3 operator*(const float f) const;
		Vector3 operator/(const Vector3 &v) const;
		Vector3 operator/(const float f) const;

		// compound assignment operators
		inline Vector3 &operator+=(const Vector3 &v)
		{
			*this = *this + v;
			return *this;
		}
		inline Vector3 &operator-=(const Vector3 &v)
		{
			*this = *this - v;
			return *this;
		}
		inline Vector3 &operator*=(const Vector3 &v)
		{
			*this = *this * v;
			return *this;
		}
		inline Vector3 &operator*=(const float f)
		{
			*this = *this * f;
			return *this;
		}
		inline Vector3 &operator/=(const Vector3 &v)
		{
			*this = *this / v;
			return *this;
		}
		inline Vector3 &operator/=(const float f)
		{
			*this = *this / f;
			return *this;
		}

		// comparison operators
		bool operator==(const Vector3 &v) const { return x == v.x && y == v.y && z == v.z; }
		bool operator!=(const Vector3 &v) const { return x != v.x || y != v.y || z != v.z; }

		// operations
		inline void add(Vector3 &vOut, const Vector3 &v) const;
		inline void subtract(Vector3 &vOut, const Vector3 &v) const;
		inline void multiply(Vector3 &vOut, const Vector3 &v) const;
		inline void multiply(Vector3 &vOut, const float f) const;
		inline void divide(Vector3 &vOut, const Vector3 &v) const;
		inline void divide(Vector3 &vOut, const float f) const;

		// tools
		void setZero()
		{
			data[0] = 0.0f;
			data[1] = 0.0f;
			data[2] = 0.0f;
			data[3] = 1.0f;
		}

		float length() const { return ::sqrt(x * x + y * y + z * z); }
		float innerProduct(const Vector3 &v) const { return x * v.x + y * v.y + z * v.z; }
		void outerProduct(Vector3 &vOut, const Vector3 &v) const
		{
			vOut.x = y * v.z - z * v.y;
			vOut.y = z * v.x - x * v.z;
			vOut.z = x * v.y - y * v.x;
		}

		void normalize() { *this /= length(); }

	public:
		union
		{
			struct
			{
				float x; //!< x position
				float y; //!< y position
				float z; //!< z position
			};
			float data[4];
			SIMD128 quad;
		};
	};

	/****************************************/
	/*!
		@class	Vector4
		@brief	3D Vector with w parameter
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Vector4
	{
	public:
		// constructor
		Vector4() {}
		Vector4(const float fx, const float fy, const float fz, const float fw) : x(fx), y(fy), z(fz), w(fw) {}

		// property
		void set(const float fx, const float fy, const float fz, const float fw)
		{
			x = fx;
			y = fy;
			z = fz;
			w = fw;
		}

		// unary operators
		Vector4 operator+() const { return *this; }
		Vector4 operator-() const { return Vector4(-x, -y, -z, -w); }

		// binary operators
		Vector4 operator+(const Vector4 &v) const;
		Vector4 operator-(const Vector4 &v) const;
		Vector4 operator*(const Vector4 &v) const;
		Vector4 operator*(const float f) const;
		Vector4 operator/(const Vector4 &v) const;
		Vector4 operator/(const float f) const;

		// compound assignment operators
		Vector4 &operator+=(const Vector4 &v)
		{
			*this = *this + v;
			return *this;
		}
		Vector4 &operator-=(const Vector4 &v)
		{
			*this = *this - v;
			return *this;
		}
		Vector4 &operator*=(const Vector4 &v)
		{
			*this = *this * v;
			return *this;
		}
		Vector4 &operator*=(const float f)
		{
			*this = *this * f;
			return *this;
		}
		Vector4 &operator/=(const Vector4 &v)
		{
			*this = *this / v;
			return *this;
		}
		Vector4 &operator/=(const float f)
		{
			*this = *this / f;
			return *this;
		}

		// comparison operators
		bool operator==(const Vector4 &v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
		bool operator!=(const Vector4 &v) const { return x != v.x || y != v.y || z != v.z || w != v.w; }

		// operations
		inline void add(Vector4 &vOut, const Vector4 &v) const;
		inline void subtract(Vector4 &vOut, const Vector4 &v) const;
		inline void multiply(Vector4 &vOut, const Vector4 &v) const;
		inline void multiply(Vector4 &vOut, const float f) const;
		inline void divide(Vector4 &vOut, const Vector4 &v) const;
		inline void divide(Vector4 &vOut, const float f) const;

		// tools
		void setZero()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

	public:
		union
		{
			struct
			{
				float x; //!< x position
				float y; //!< y position
				float z; //!< z position
				float w; //!< w parameter
			};
			float data[4];
			SIMD128 quad;
		};
	};

	/****************************************/
	/*!
		@class	Matrix33
		@brief	Matrix (3x3)
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Matrix33
	{
	public:
		// constractor
		Matrix33() {}

		Matrix33(const Matrix33 &mat);

		Matrix33(
			const float f00, const float f01, const float f02,
			const float f10, const float f11, const float f12,
			const float f20, const float f21, const float f22);

		// property
		void set(
			const float f00, const float f01, const float f02,
			const float f10, const float f11, const float f12,
			const float f20, const float f21, const float f22);

		// unary operators
		Matrix33 operator+() const { return *this; }
		Matrix33 operator-() const;

		// binary operators
		Matrix33 operator+(const Matrix33 &mat) const;
		Matrix33 operator-(const Matrix33 &mat) const;
		Matrix33 operator*(const Matrix33 &mat) const;
		Vector2 operator*(const Vector2 &v) const;
		Vector3 operator*(const Vector3 &v) const;
		Matrix33 operator*(const float f) const;
		Matrix33 operator/(const float f) const;

		// compound assignment operators
		Matrix33 &operator+=(const Matrix33 &mat)
		{
			*this = *this + mat;
			return *this;
		}
		Matrix33 &operator-=(const Matrix33 &mat)
		{
			*this = *this - mat;
			return *this;
		}
		Matrix33 &operator*=(const Matrix33 &mat)
		{
			*this = *this * mat;
			return *this;
		}
		Matrix33 &operator*=(const float f)
		{
			*this = *this * f;
			return *this;
		}
		Matrix33 &operator/=(const float f)
		{
			*this = *this / f;
			return *this;
		}

		// binary operation
		void add(Matrix33 &mOut, const Matrix33 &mat) const;
		void subtract(Matrix33 &mOut, const Matrix33 &mat) const;
		void multiply(Matrix33 &mOut, const Matrix33 &mat) const;
		void multiply(Vector2 &vOut, const Vector2 &v) const;
		void multiply(Vector3 &vOut, const Vector3 &v) const;
		void multiply(Matrix33 &mOut, const float f) const;
		void divide(Matrix33 &mOut, const float f) const;

		// tools
		void transpose();
		bool inverse();

		inline void setUnitMatrix();

		void setTransrationMatrix(const Vector2 &v);
		void setTransrationMatrix(const float fx, const float fy);

		void setRotationMarix(const float radian);

		void setScalingMatrix(const float factor);
		void setScalingMatrix(const Vector2 &v);
		void setScalingMatrix(const float fx, const float fy);

	public:
		union
		{
			float m[3][3];	  //!< m[col][row] Note that the order
			float serial[9]; //!< matrix buffer
			SIMD128 row[3];
		};
	};

	/****************************************/
	/*!
		@class	Matrix44
		@brief	Matrix (4x4)
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Matrix44
	{
	public:
		// constractor
		Matrix44() {}

		Matrix44(const Matrix44 &mat);

		Matrix44(
			const float f00, const float f01, const float f02, const float f03,
			const float f10, const float f11, const float f12, const float f13,
			const float f20, const float f21, const float f22, const float f23,
			const float f30, const float f31, const float f32, const float f33);

		// property
		void set(
			const float f00, const float f01, const float f02, const float f03,
			const float f10, const float f11, const float f12, const float f13,
			const float f20, const float f21, const float f22, const float f23,
			const float f30, const float f31, const float f32, const float f33);

		// unary operators
		Matrix44 operator+() const { return *this; }
		Matrix44 operator-() const;

		// binary operators
		Matrix44 operator+(const Matrix44 &mat) const;
		Matrix44 operator-(const Matrix44 &mat) const;
		Matrix44 operator*(const Matrix44 &mat) const;
		Vector3 operator*(const Vector3 &v) const;
		Vector4 operator*(const Vector4 &v) const;
		Matrix44 operator*(const float f) const;
		Matrix44 operator/(const float f) const;

		// compound assignment operators
		Matrix44 &operator+=(const Matrix44 &mat)
		{
			*this = *this + mat;
			return *this;
		}
		Matrix44 &operator-=(const Matrix44 &mat)
		{
			*this = *this - mat;
			return *this;
		}
		Matrix44 &operator*=(const Matrix44 &mat)
		{
			*this = *this * mat;
			return *this;
		}
		Matrix44 &operator*=(const float f)
		{
			*this = *this * f;
			return *this;
		}
		Matrix44 &operator/=(const float f)
		{
			*this = *this / f;
			return *this;
		}

		// binary operation
		void add(Matrix44 &mOut, const Matrix44 &mat) const;
		void subtract(Matrix44 &mOut, const Matrix44 &mat) const;
		void multiply(Matrix44 &mOut, const Matrix44 &mat) const;
		void multiply(Vector3 &vOut, const Vector3 &v) const;
		void multiply(Vector4 &vOut, const Vector4 &v) const;
		void multiply(Matrix44 &mOut, const float f) const;
		void divide(Matrix44 &mOut, const float f) const;

		// tools
		void transpose();
		bool inverse();

		inline void setUnitMatrix();

		void setTransrationMatrix(const Vector3 &v);
		void setTransrationMatrix(const float fx, const float fy, const float fz);

		void setRotationMarix(const Vector3 &v, float radian);
		void setXRotationMatrix(const float radian);
		void setYRotationMatrix(const float radian);
		void setZRotationMatrix(const float radian);

		void setScalingMatrix(const float factor);
		void setScalingMatrix(const Vector3 &v);
		void setScalingMatrix(const float fx, const float fy, const float fz);

	public:
		union
		{
			float m[4][4];	  //!< m[col][row] Note that the order!!
			float serial[16]; //!< matrix buffer is row based array
			SIMD128 row[4];
		};
	};

	/****************************************/
	/*!
		@class	Quaternion4
		@brief	Quaternion4
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Quaternion4
	{
	public:
		// constructor
		Quaternion4(){};
		Quaternion4(const float fx, const float fy, const float fz, const float fw) : x(fx), y(fy), z(fz), w(fw){};

		// property
		void set(const float fx, const float fy, const float fz, const float fw)
		{
			x = fx;
			y = fy;
			z = fz;
			w = fw;
		}

		// unary operators
		Quaternion4 operator+() const { return *this; }
		Quaternion4 operator-() const { return Quaternion4(-x, -y, -z, -w); }

		// binary operators
		Quaternion4 operator+(const Quaternion4 &q) const;
		Quaternion4 operator-(const Quaternion4 &q) const;
		Quaternion4 operator*(const Quaternion4 &q) const;
		Quaternion4 operator*(const float f) const;
		Quaternion4 operator/(const float f) const;

		// compound assignment operators
		Quaternion4 &operator+=(const Quaternion4 &q)
		{
			*this = *this + q;
			return *this;
		}
		Quaternion4 &operator-=(const Quaternion4 &q)
		{
			*this = *this - q;
			return *this;
		}
		Quaternion4 &operator*=(const Quaternion4 &q)
		{
			*this = *this * q;
			return *this;
		}
		Quaternion4 &operator*=(float f)
		{
			*this = *this * f;
			return *this;
		}
		Quaternion4 &operator/=(float f)
		{
			*this = *this / f;
			return *this;
		}

		// comparison operators
		bool operator==(const Quaternion4 &q) const { return (x == q.x) && (y == q.y) && (z == q.z) && (w == q.w); }
		bool operator!=(const Quaternion4 &q) const { return (x != q.x) || (y != q.y) || (z != q.z) || (w != q.w); }

		// binary operaton
		void add(Quaternion4 &qOut, const Quaternion4 &q) const;
		void subtract(Quaternion4 &qOut, const Quaternion4 &q) const;
		void multiply(Quaternion4 &qOut, const Quaternion4 &q) const;
		void multiply(Quaternion4 &qOut, const float f) const;
		void divide(Quaternion4 &qOut, const float f) const;

		// tools
		void setUnitQuaternion()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 1.0f;
		}
		float getNorm() const { return x * x + y * y + z * z + w * w; }
		float getAbsoluteValue() const { return ::sqrt(x * x + y * y + z * z + w * w); }

		void normalize() const { *this / getAbsoluteValue(); }
		void conjugate()
		{
			x = -x;
			y = -y;
			z = -z;
		}
		void inverse();

		float innerProduct(const Quaternion4 &q) const { return (x * q.x + y * q.y + z * q.z + w * q.w); }

		void toMatrix44(Matrix44 &m) const;
		void convert(const Matrix44 &m);
		void convert(const Vector3 &v, const float radian);

		void toAxisAngle(Vector3 &v, float &radian) const;

		void convertVector(Vector3 &vOut, const Vector3 &v) const;

	public:
		union
		{
			struct
			{
				// q = w + xi + yj + zk
				float x; //!< imaginary part(i)
				float y; //!< imaginary part(j)
				float z; //!< imaginary part(k)
				float w; //!< real part
			};
			SIMD128 data;
		};
	};

	/****************************************/
	/*!
		@class	Color4
		@brief	Color parameter
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Color3
	{
	public:
		// constructor
		Color3() {}
		Color3(unsigned int code) 
		{
			r = (float)((code >> 16) & 0xff) / 255.0f;
			g = (float)((code >> 8) & 0xff) / 255.0f;
			b = (float)(code & 0xff) / 255.0f;
		}
		Color3(const float fr, const float fg, const float fb) : r(fr), g(fg), b(fb) {}

		// property
		void set(const float fr, const float fg, const float fb)
		{
			r = fr;
			g = fg;
			b = fb;
		}

		// comparison operators
		bool operator==(const Color3 &c) const { return r == c.r && g == c.g && b == c.b; }
		bool operator!=(const Color3 &c) const { return r != c.r || g != c.g || b != c.b; }

		static const Color3 white;
		static const Color3 black;
		static const Color3 gray;
		static const Color3 red;
		static const Color3 green;
		static const Color3 blue;

	public:
		union
		{
			struct
			{
				float r; //!< red
				float g; //!< green
				float b; //!< blue
			};
			float data[3];
		};
	};

	/****************************************/
	/*!
		@class	Color4
		@brief	Color parameter
		@note
		@author	Naoto Nakamura
		@date	Mar. 10, 2009
	*/
	/****************************************/
	class Color4
	{
	public:
		// constructor
		Color4() : a(1.0f) {}
		Color4(unsigned int code) : a(1.0f)
		{
			r = (float)((code >> 16) & 0xff) / 255.0f;
			g = (float)((code >> 8) & 0xff) / 255.0f;
			b = (float)(code & 0xff) / 255.0f;
		}
		Color4(const float fr, const float fg, const float fb, const float fa = 1.0f) : r(fr), g(fg), b(fb), a(fa) {}

		// property
		void set(const float fr, const float fg, const float fb)
		{
			r = fr;
			g = fg;
			b = fb;
		}

		void set(const float fr, const float fg, const float fb, const float fa)
		{
			r = fr;
			g = fg;
			b = fb;
			a = fa;
		}

		void setAlpha(const float fa)
		{
			a = fa;
		}

		// comparison operators
		bool operator==(const Color4 &c) const { return r == c.r && g == c.g && b == c.b && a == c.a; }
		bool operator!=(const Color4 &c) const { return r != c.r || g != c.g || b != c.b || a != c.a; }

		static const Color4 white;
		static const Color4 black;
		static const Color4 gray;
		static const Color4 red;
		static const Color4 green;
		static const Color4 blue;

	public:
		union
		{
			struct
			{
				float r; //!< red
				float g; //!< green
				float b; //!< blue
				float a; //!< alpha
			};
			float data[4];
		};
	};

}; // namespace S3D

#include "S3D/Graphics/Math/Vector-inl.h"
#include "S3D/Graphics/Math/Matrix-inl.h"
#include "S3D/Graphics/Math/Quaternion-inl.h"

#endif // S3D_MATH_MATHEMATICSTYPES_H
