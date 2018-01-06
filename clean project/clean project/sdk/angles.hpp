#pragma once

#ifdef _MSC_VER
#pragma once
#endif
#include <math.h>
#include <Windows.h>
#include <sstream>
#include <intrin.h>
#define CHECK_VALID( _v ) 0
#define Assert( _exp ) ((void)0)
#define FastSqrt(x)			(*sqrtf)(x)
#define M_PI		3.14159265358979323846f
#define M_RADPI		57.295779513082f
#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#define square( x ) ( x * x )
#define SQUARE( a ) a*a
#define rad(a) a*(M_PI/180)
#define deg(a) a*(180/M_PI)
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif


namespace sdk
{
	inline float sqrt2(float sqr)
	{
		float root = 0;

		__asm
		{
			sqrtss xmm0, sqr
			movss root, xmm0
		}

		return root;
	}

	void inline SinCos(float radians, float sine, float cosine)
	{
		sine = sin(radians);
		cosine = cos(radians);
	}

	struct vertex_t
	{
	public:

		float	x;
		float	y;

	private:

		float	tex_x = 0.f;
		float	tex_y = 0.f;
	};

	struct vec2_t
	{
	public:
		float x, y;

		vec2_t() {}
		vec2_t(float x_, float y_) { x = x_; y = y_; }
	};


	class vec3_t
	{
	public:
		typedef float vec_t;
		vec_t x, y, z;
		vec3_t(const float* clr)
		{
			x = clr[0];
			y = clr[1];
			z = clr[2];
		}

		vec3_t(float X, float Y)
		{
			x = X;
			y = Y;
			z = 0;
		}

		vec3_t(void);
		vec3_t(float X, float Y, float Z);
		void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
		float operator[](int i) const;
		float& operator[](int i);
		inline void Zero();
		bool operator==(const vec3_t& v) const;
		bool operator!=(const vec3_t& v) const;
		inline bool operator!() { return !x && !y && !z; }
		__forceinline vec3_t&	operator+=(const vec3_t &v);
		__forceinline vec3_t&	operator-=(const vec3_t &v);
		__forceinline vec3_t&	operator*=(const vec3_t &v);
		__forceinline vec3_t&	operator*=(float s);
		__forceinline vec3_t&	operator/=(const vec3_t &v);
		__forceinline vec3_t&	operator/=(float s);
		__forceinline vec3_t&	operator+=(float fl);
		__forceinline vec3_t&	operator-=(float fl);
		inline vec3_t NormalizeVec();
		inline float	Length() const;
		__forceinline float LengthSqr(void) const
		{
			CHECK_VALID(*this);
			return (x*x + y*y + z*z);
		}
		bool IsZero(float tolerance = 0.01f) const
		{
			return (x > -tolerance && x < tolerance &&
				y > -tolerance && y < tolerance &&
				z > -tolerance && z < tolerance);
		}
		float	NormalizeInPlace();
		__forceinline float	DistToSqr(const vec3_t &vOther) const;
		float	Dot(const vec3_t& vOther) const;
		float	Dots(const float* fOther) const;
		float	Length2D(void) const;
		float	Length2DSqr(void) const;
		inline void Rotate2D(const float& f);
		vec3_t& operator=(const vec3_t &vOther);
		vec3_t	operator-(void) const;
		vec3_t	operator+(const vec3_t& v) const;
		vec3_t	operator-(const vec3_t& v) const;
		vec3_t	operator*(const vec3_t& v) const;
		vec3_t	operator/(const vec3_t& v) const;
		vec3_t	operator*(float fl) const;
		vec3_t	operator/(float fl) const;
		// Base address...
		float* Base();
		float const* Base() const;
		inline vec3_t Cross(vec3_t a) { return vec3_t(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x); }
		inline vec3_t Angle(vec3_t* up = 0)
		{
			if (!x && !y)
				return vec3_t(0, 0, 0);

			float roll = 0;

			if (up)
			{
				vec3_t left = (*up).Cross(*this);

				roll = deg(atan2f(left.z, (left.y * x) - (left.x * y)));
			}

			return vec3_t(deg(atan2f(-z, sqrt2(x*x + y*y))), deg(atan2f(y, x)), roll);
		}
		inline bool IsValid() const
		{
			return (x == x && y == y && z == z);
		}
		vec3_t Direction()
		{
			return vec3_t(cos(y * M_PI / 180.0f) * cos(x * M_PI / 180.0f), sin(y * M_PI / 180.0f) * cos(x * M_PI / 180.0f), sin(-x * M_PI / 180.0f)).NormalizeVec();
		}

		inline vec3_t Forward()
		{
			float sp, sy, cp, cy;

			SinCos(rad(x), sp, cp);
			SinCos(rad(y), sy, cy);

			return vec3_t(cp*cy, cp*sy, -sp);
		}
		inline vec3_t Right()
		{
			float sp, sy, sr, cp, cy, cr;

			SinCos(rad(x), sp, cp);
			SinCos(rad(y), sy, cy);
			SinCos(rad(z), sr, cr);

			return vec3_t(1 * sr*sp*cy + -1 * cr*-sy, -1 * sr*sp*sy + -1 * cr*cy, -1 * sr*cr);
		}
		inline vec3_t Up()
		{
			float sp, sy, sr, cp, cy, cr;

			SinCos(rad(x), sp, cp);
			SinCos(rad(y), sy, cy);
			SinCos(rad(z), sr, cr);

			return vec3_t(cr*sp*cy + -sr*-sy, cr*sp*sy + -sr*cy, cr*cp);
		}

		vec3_t Normalized() const {
			vec3_t res = *this;
			vec_t l = res.Length();
			if (l != 0.0f) {
				res /= l;
			}
			else {
				res.x = res.y = res.z = 0.0f;
			}
		}
	};

	//===============================================
	inline void vec3_t::Init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
		CHECK_VALID(*this);
	}
	//===============================================
	inline vec3_t::vec3_t(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
		CHECK_VALID(*this);
	}
	//===============================================
	inline vec3_t::vec3_t(void) { }
	//===============================================
	inline void vec3_t::Zero()
	{
		x = y = z = 0.0f;
	}
	inline vec3_t operator*(float fl, const vec3_t& v)
	{
		return v * fl;
	}
	//===============================================
	inline void vec3_tClear(vec3_t& a)
	{
		a.x = a.y = a.z = 0.0f;
	}
	inline void vec3_t::Rotate2D(const float &f)
	{
		float _x, _y;

		float s, c;

		SinCos(DEG2RAD(f), s, c);

		_x = x;
		_y = y;

		x = (_x * c) - (_y * s);
		y = (_x * s) + (_y * c);
	}

	FORCEINLINE float DotProduct(const vec3_t& a, const vec3_t& b)
	{
		return (a.x * b.x + a.y * b.y + a.z * b.z);
	}
	//===============================================
	inline vec3_t& vec3_t::operator=(const vec3_t &vOther)
	{
		CHECK_VALID(vOther);
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}
	//===============================================
	inline float& vec3_t::operator[](int i)
	{
		Assert((i >= 0) && (i < 3));
		return ((float*)this)[i];
	}
	//===============================================
	inline float vec3_t::operator[](int i) const
	{
		Assert((i >= 0) && (i < 3));
		return ((float*)this)[i];
	}
	//===============================================
	inline bool vec3_t::operator==(const vec3_t& src) const
	{
		CHECK_VALID(src);
		CHECK_VALID(*this);
		return (src.x == x) && (src.y == y) && (src.z == z);
	}
	//===============================================
	inline bool vec3_t::operator!=(const vec3_t& src) const
	{
		CHECK_VALID(src);
		CHECK_VALID(*this);
		return (src.x != x) || (src.y != y) || (src.z != z);
	}
	//===============================================
	__forceinline void vec3_tCopy(const vec3_t& src, vec3_t& dst)
	{
		CHECK_VALID(src);
		dst.x = src.x;
		dst.y = src.y;
		dst.z = src.z;
	}
	//===============================================
	__forceinline  vec3_t& vec3_t::operator+=(const vec3_t& v)
	{
		CHECK_VALID(*this);
		CHECK_VALID(v);
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	//===============================================
	__forceinline  vec3_t& vec3_t::operator-=(const vec3_t& v)
	{
		CHECK_VALID(*this);
		CHECK_VALID(v);
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	//===============================================
	__forceinline  vec3_t& vec3_t::operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		z *= fl;
		CHECK_VALID(*this);
		return *this;
	}
	//===============================================
	__forceinline  vec3_t& vec3_t::operator*=(const vec3_t& v)
	{
		CHECK_VALID(v);
		x *= v.x;
		y *= v.y;
		z *= v.z;
		CHECK_VALID(*this);
		return *this;
	}
	//===============================================
	__forceinline vec3_t&	vec3_t::operator+=(float fl)
	{
		x += fl;
		y += fl;
		z += fl;
		CHECK_VALID(*this);
		return *this;
	}
	//===============================================
	__forceinline vec3_t&	vec3_t::operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		z -= fl;
		CHECK_VALID(*this);
		return *this;
	}
	//===============================================
	__forceinline  vec3_t& vec3_t::operator/=(float fl)
	{
		Assert(fl != 0.0f);
		float oofl = 1.0f / fl;
		x *= oofl;
		y *= oofl;
		z *= oofl;
		CHECK_VALID(*this);
		return *this;
	}
	//===============================================
	__forceinline  vec3_t& vec3_t::operator/=(const vec3_t& v)
	{
		CHECK_VALID(v);
		Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
		x /= v.x;
		y /= v.y;
		z /= v.z;
		CHECK_VALID(*this);
		return *this;
	}
	//===============================================
	inline float vec3_t::Length(void) const
	{
		CHECK_VALID(*this);

		float root = 0.0f;

		float sqsr = x*x + y*y + z*z;

		__asm
		{
			sqrtss xmm0, sqsr
			movss root, xmm0
		}

		return root;
	}
	//===============================================
	inline float vec3_t::Length2D(void) const
	{
		CHECK_VALID(*this);

		float root = 0.0f;

		float sqst = x*x + y*y;

		__asm
		{
			sqrtss xmm0, sqst
			movss root, xmm0
		}

		return root;
	}
	//===============================================
	inline float vec3_t::Length2DSqr(void) const
	{
		return (x*x + y*y);
	}
	//===============================================
	inline vec3_t CrossProduct(const vec3_t& a, const vec3_t& b)
	{
		return vec3_t(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
	}

	inline void CrossProduct2(const vec3_t& a, const vec3_t& b, vec3_t& result)
	{
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
	}



	//===============================================
	float vec3_t::DistToSqr(const vec3_t &vOther) const
	{
		vec3_t delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}
	inline vec3_t vec3_t::NormalizeVec()
	{
		vec3_t& vecIn = *this;
		for (int axis = 0; axis < 3; ++axis)
		{
			while (vecIn[axis] > 180.f)
				vecIn[axis] -= 360.f;

			while (vecIn[axis] < -180.f)
				vecIn[axis] += 360.f;

		}

		vecIn[2] = 0.f;
		return vecIn;
	}
	//===============================================
	inline float vec3_t::NormalizeInPlace()
	{
		vec3_t& v = *this;

		float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;

		return iradius;

	}
	//===============================================
	inline float vec3_tNormalize(vec3_t& v)
	{
		Assert(v.IsValid());
		float l = v.Length();
		if (l != 0.0f)
		{
			v /= l;
		}
		else
		{
			// FIXME: 
			// Just copying the existing implemenation; shouldn't res.z == 0?
			v.x = v.y = 0.0f; v.z = 1.0f;
		}
		return l;
	}
	//===============================================
	FORCEINLINE float vec3_tNormalize(float * v)
	{
		return vec3_tNormalize(*(reinterpret_cast< vec3_t * >(v)));
	}
	//===============================================
	inline vec3_t vec3_t::operator+(const vec3_t& v) const
	{
		vec3_t res;
		res.x = x + v.x;
		res.y = y + v.y;
		res.z = z + v.z;
		return res;
	}

	//===============================================
	inline vec3_t vec3_t::operator-(const vec3_t& v) const
	{
		vec3_t res;
		res.x = x - v.x;
		res.y = y - v.y;
		res.z = z - v.z;
		return res;
	}
	//===============================================
	inline vec3_t vec3_t::operator*(float fl) const
	{
		vec3_t res;
		res.x = x * fl;
		res.y = y * fl;
		res.z = z * fl;
		return res;
	}
	//===============================================
	inline vec3_t vec3_t::operator*(const vec3_t& v) const
	{
		vec3_t res;
		res.x = x * v.x;
		res.y = y * v.y;
		res.z = z * v.z;
		return res;
	}
	//===============================================
	inline vec3_t vec3_t::operator/(float fl) const
	{
		vec3_t res;
		res.x = x / fl;
		res.y = y / fl;
		res.z = z / fl;
		return res;
	}
	//===============================================
	inline vec3_t vec3_t::operator/(const vec3_t& v) const
	{
		vec3_t res;
		res.x = x / v.x;
		res.y = y / v.y;
		res.z = z / v.z;
		return res;
	}
	inline float vec3_t::Dot(const vec3_t& vOther) const
	{
		const vec3_t& a = *this;

		return(a.x*vOther.x + a.y*vOther.y + a.z*vOther.z);
	}
	inline float vec3_t::Dots(const float* fOther) const
	{
		const vec3_t& a = *this;

		return(a.x*fOther[0] + a.y*fOther[1] + a.z*fOther[2]);
	}
	inline float vector_length(const vec3_t& v)
	{
		CHECK_VALID(v);
		return (float)FastSqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	}
	inline void vector_multiply(const vec3_t& src, float fl, vec3_t& res)
	{
		Assert(IsFinite(fl));
		res.x = src.x * fl;
		res.y = src.y * fl;
		res.z = src.z * fl;
	}
	inline void vector_ma_inline(const float* start, float scale, const float* direction, float* dest)
	{
		dest[0] = start[0] + direction[0] * scale;
		dest[1] = start[1] + direction[1] * scale;
		dest[2] = start[2] + direction[2] * scale;
	}

	inline void vector_ma_inline(const vec3_t& start, float scale, const vec3_t& direction, vec3_t& dest)
	{
		dest.x = start.x + direction.x*scale;
		dest.y = start.y + direction.y*scale;
		dest.z = start.z + direction.z*scale;
	}

	inline void vector_ma(const vec3_t& start, float scale, const vec3_t& direction, vec3_t& dest)
	{
		vector_ma_inline(start, scale, direction, dest);
	}

	inline void vector_ma(const float * start, float scale, const float *direction, float *dest)
	{
		vector_ma_inline(start, scale, direction, dest);
	}

	inline void vector_add(const vec3_t& a, const vec3_t& b, vec3_t& c)
	{
		CHECK_VALID(a);
		CHECK_VALID(b);
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
	}

	inline void vector_subtract(const vec3_t& a, const vec3_t& b, vec3_t& c)
	{
		CHECK_VALID(a);
		CHECK_VALID(b);
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
	}

	inline float* vec3_t::Base()
	{
		return (float*)this;
	}
	inline float const* vec3_t::Base() const
	{
		return (float const*)this;
	}

	typedef vec3_t angle_t;


	class __declspec(align(16)) vec3_tAligned : public vec3_t
	{
	public:
		inline vec3_tAligned(void) {};
		inline vec3_tAligned(float X, float Y, float Z)
		{
			Init(X, Y, Z);
		}
	public:
		explicit vec3_tAligned(const vec3_t &vOther)
		{
			Init(vOther.x, vOther.y, vOther.z);
		}

		vec3_tAligned& operator=(const vec3_t &vOther)
		{
			Init(vOther.x, vOther.y, vOther.z);
			return *this;
		}

		float w;	// this space is used anyway
	};

	typedef vec3_t angle_t;

	typedef float vec_t;
	inline void vector_lerp(const vec3_t& src1, const vec3_t& src2, vec_t t, vec3_t& dest)
	{
		CHECK_VALID(src1);
		CHECK_VALID(src2);
		dest.x = src1.x + (src2.x - src1.x) * t;
		dest.y = src1.y + (src2.y - src1.y) * t;
		dest.z = src1.z + (src2.z - src1.z) * t;
	}

	inline vec3_t vector_lerp(const vec3_t& src1, const vec3_t& src2, vec_t t)
	{
		vec3_t result;
		vector_lerp(src1, src2, t, result);
		return result;
	}


	struct cplane_t {
		vec3_t	normal;
		float	dist;
		byte	type;			// for fast side tests
		byte	signbits;		// signx + (signy<<1) + (signz<<1)
		byte	pad[2];

	};

	class matrix3x4_t
	{
	public:
		matrix3x4_t() {}
		matrix3x4_t(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23)
		{
			m_flMatVal[0][0] = m00; m_flMatVal[0][1] = m01; m_flMatVal[0][2] = m02; m_flMatVal[0][3] = m03;
			m_flMatVal[1][0] = m10; m_flMatVal[1][1] = m11; m_flMatVal[1][2] = m12; m_flMatVal[1][3] = m13;
			m_flMatVal[2][0] = m20; m_flMatVal[2][1] = m21; m_flMatVal[2][2] = m22; m_flMatVal[2][3] = m23;
		}
		//-----------------------------------------------------------------------------
		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		//-----------------------------------------------------------------------------
		void Init(const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis, const vec3_t &vecOrigin)
		{
			m_flMatVal[0][0] = xAxis.x; m_flMatVal[0][1] = yAxis.x; m_flMatVal[0][2] = zAxis.x; m_flMatVal[0][3] = vecOrigin.x;
			m_flMatVal[1][0] = xAxis.y; m_flMatVal[1][1] = yAxis.y; m_flMatVal[1][2] = zAxis.y; m_flMatVal[1][3] = vecOrigin.y;
			m_flMatVal[2][0] = xAxis.z; m_flMatVal[2][1] = yAxis.z; m_flMatVal[2][2] = zAxis.z; m_flMatVal[2][3] = vecOrigin.z;
		}

		//-----------------------------------------------------------------------------
		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		//-----------------------------------------------------------------------------
		matrix3x4_t(const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis, const vec3_t &vecOrigin)
		{
			Init(xAxis, yAxis, zAxis, vecOrigin);
		}

		inline void SetOrigin(vec3_t const & p)
		{
			m_flMatVal[0][3] = p.x;
			m_flMatVal[1][3] = p.y;
			m_flMatVal[2][3] = p.z;
		}

		inline void Invalidate(void)
		{
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 4; j++) {
					m_flMatVal[i][j] = std::numeric_limits<float>::infinity();;
				}
			}
		}

		vec3_t& at(int i) const { return *(vec3_t*)&m_flMatVal[i]; }

		float *operator[](int i) { return m_flMatVal[i]; }
		const float *operator[](int i) const { return m_flMatVal[i]; }
		float *Base() { return &m_flMatVal[0][0]; }
		const float *Base() const { return &m_flMatVal[0][0]; }

		float m_flMatVal[3][4];
	};
	class matrix3x4a_t :public matrix3x4_t
	{
	public:
		/*
		matrix3x4a_t() { if (((size_t)Base()) % 16 != 0) { Error( "matrix3x4a_t missaligned" ); } }
		*/
		matrix3x4a_t& operator=(const matrix3x4_t& src) { memcpy(Base(), src.Base(), sizeof(float) * 3 * 4); return *this; };
	};

	class VMatrix {
	public:

		VMatrix();
		VMatrix(
			vec_t m00, vec_t m01, vec_t m02, vec_t m03,
			vec_t m10, vec_t m11, vec_t m12, vec_t m13,
			vec_t m20, vec_t m21, vec_t m22, vec_t m23,
			vec_t m30, vec_t m31, vec_t m32, vec_t m33
		);

		// Creates a matrix where the X axis = forward
		// the Y axis = left, and the Z axis = up
		VMatrix(const vec3_t& forward, const vec3_t& left, const vec3_t& up);

		// Construct from a 3x4 matrix
		VMatrix(const matrix3x4_t& matrix3x4);

		// Set the values in the matrix.
		void		Init(
			vec_t m00, vec_t m01, vec_t m02, vec_t m03,
			vec_t m10, vec_t m11, vec_t m12, vec_t m13,
			vec_t m20, vec_t m21, vec_t m22, vec_t m23,
			vec_t m30, vec_t m31, vec_t m32, vec_t m33
		);


		// Initialize from a 3x4
		void		Init(const matrix3x4_t& matrix3x4);

		// array access
		inline float* operator[](int i) {
			return m[i];
		}

		inline const float* operator[](int i) const {
			return m[i];
		}

		// Get a pointer to m[0][0]
		inline float *Base() {
			return &m[0][0];
		}

		inline const float *Base() const {
			return &m[0][0];
		}

		void		SetLeft(const vec3_t &vLeft);
		void		SetUp(const vec3_t &vUp);
		void		SetForward(const vec3_t &vForward);

		void		GetBasisvec3_ts(vec3_t &vForward, vec3_t &vLeft, vec3_t &vUp) const;
		void		SetBasisvec3_ts(const vec3_t &vForward, const vec3_t &vLeft, const vec3_t &vUp);

		// Get/set the translation.
		vec3_t &	GetTranslation(vec3_t &vTrans) const;
		void		SetTranslation(const vec3_t &vTrans);

		void		PreTranslate(const vec3_t &vTrans);
		void		PostTranslate(const vec3_t &vTrans);

		matrix3x4_t& As3x4();
		const matrix3x4_t& As3x4() const;
		void		CopyFrom3x4(const matrix3x4_t &m3x4);
		void		Set3x4(matrix3x4_t& matrix3x4) const;

		bool		operator==(const VMatrix& src) const;
		bool		operator!=(const VMatrix& src) const { return !(*this == src); }

		// Access the basis vec3_ts.
		vec3_t		GetLeft() const;
		vec3_t		GetUp() const;
		vec3_t		GetForward() const;
		vec3_t		GetTranslation() const;


		// Matrix->vec3_t operations.
	public:
		// Multiply by a 3D vec3_t (same as operator*).
		void		V3Mul(const vec3_t &vIn, vec3_t &vOut) const;

		// Multiply by a 4D vec3_t.
		//void		V4Mul( const vec3_t4D &vIn, vec3_t4D &vOut ) const;

		// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
		vec3_t		ApplyRotation(const vec3_t &vVec) const;

		// Multiply by a vec3_t (divides by w, assumes input w is 1).
		vec3_t		operator*(const vec3_t &vVec) const;

		// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
		vec3_t		VMul3x3(const vec3_t &vVec) const;

		// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
		vec3_t		VMul3x3Transpose(const vec3_t &vVec) const;

		// Multiply by the upper 3 rows.
		vec3_t		VMul4x3(const vec3_t &vVec) const;

		// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
		vec3_t		VMul4x3Transpose(const vec3_t &vVec) const;


		// Matrix->plane operations.
		//public:
		// Transform the plane. The matrix can only contain translation and rotation.
		//void		TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

		// Just calls TransformPlane and returns the result.
		//VPlane		operator*(const VPlane &thePlane) const;

		// Matrix->matrix operations.
	public:

		VMatrix&	operator=(const VMatrix &mOther);

		// Multiply two matrices (out = this * vm).
		void		MatrixMul(const VMatrix &vm, VMatrix &out) const;

		// Add two matrices.
		const VMatrix& operator+=(const VMatrix &other);

		// Just calls MatrixMul and returns the result.	
		VMatrix		operator*(const VMatrix &mOther) const;

		// Add/Subtract two matrices.
		VMatrix		operator+(const VMatrix &other) const;
		VMatrix		operator-(const VMatrix &other) const;

		// Negation.
		VMatrix		operator-() const;

		// Return inverse matrix. Be careful because the results are undefined 
		// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
		VMatrix		operator~() const;

		// Matrix operations.
	public:
		// Set to identity.
		void		Identity();

		bool		IsIdentity() const;

		// Setup a matrix for origin and angles.
		void		SetupMatrixOrgAngles(const vec3_t &origin, const angle_t &vAngles);

		// General inverse. This may fail so check the return!
		bool		InverseGeneral(VMatrix &vInverse) const;

		// Does a fast inverse, assuming the matrix only contains translation and rotation.
		void		InverseTR(VMatrix &mRet) const;

		// Usually used for debug checks. Returns true if the upper 3x3 contains
		// unit vec3_ts and they are all orthogonal.
		bool		IsRotationMatrix() const;

		// This calls the other InverseTR and returns the result.
		VMatrix		InverseTR() const;

		// Get the scale of the matrix's basis vec3_ts.
		vec3_t		GetScale() const;

		// (Fast) multiply by a scaling matrix setup from vScale.
		VMatrix		Scale(const vec3_t &vScale);

		// Normalize the basis vec3_ts.
		VMatrix		NormalizeBasisvec3_ts() const;

		// Transpose.
		VMatrix		Transpose() const;

		// Transpose upper-left 3x3.
		VMatrix		Transpose3x3() const;

	public:
		// The matrix.
		vec_t		m[4][4];
	};


	inline VMatrix::VMatrix() {
	}

	inline VMatrix::VMatrix(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33) {
		Init(
			m00, m01, m02, m03,
			m10, m11, m12, m13,
			m20, m21, m22, m23,
			m30, m31, m32, m33
		);
	}


	inline VMatrix::VMatrix(const matrix3x4_t& matrix3x4) {
		Init(matrix3x4);
	}


	//-----------------------------------------------------------------------------
	// Creates a matrix where the X axis = forward
	// the Y axis = left, and the Z axis = up
	//-----------------------------------------------------------------------------
	inline VMatrix::VMatrix(const vec3_t& xAxis, const vec3_t& yAxis, const vec3_t& zAxis) {
		Init(
			xAxis.x, yAxis.x, zAxis.x, 0.0f,
			xAxis.y, yAxis.y, zAxis.y, 0.0f,
			xAxis.z, yAxis.z, zAxis.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);
	}


	inline void VMatrix::Init(
		vec_t m00, vec_t m01, vec_t m02, vec_t m03,
		vec_t m10, vec_t m11, vec_t m12, vec_t m13,
		vec_t m20, vec_t m21, vec_t m22, vec_t m23,
		vec_t m30, vec_t m31, vec_t m32, vec_t m33
	) {
		m[0][0] = m00;
		m[0][1] = m01;
		m[0][2] = m02;
		m[0][3] = m03;

		m[1][0] = m10;
		m[1][1] = m11;
		m[1][2] = m12;
		m[1][3] = m13;

		m[2][0] = m20;
		m[2][1] = m21;
		m[2][2] = m22;
		m[2][3] = m23;

		m[3][0] = m30;
		m[3][1] = m31;
		m[3][2] = m32;
		m[3][3] = m33;
	}


	//-----------------------------------------------------------------------------
	// Initialize from a 3x4
	//-----------------------------------------------------------------------------
	inline void VMatrix::Init(const matrix3x4_t& matrix3x4) {
		memcpy(m, matrix3x4.Base(), sizeof(matrix3x4_t));

		m[3][0] = 0.0f;
		m[3][1] = 0.0f;
		m[3][2] = 0.0f;
		m[3][3] = 1.0f;
	}

	//-----------------------------------------------------------------------------
	// vec3_t3DMultiplyPosition treats src2 as if it's a point (adds the translation)
	//-----------------------------------------------------------------------------
	// NJS: src2 is passed in as a full vec3_t rather than a reference to prevent the need
	// for 2 branches and a potential copy in the body.  (ie, handling the case when the src2
	// reference is the same as the dst reference ).
	inline void vec3_t3DMultiplyPosition(const VMatrix& src1, const vec3_t& src2, vec3_t& dst) {
		dst[0] = src1[0][0] * src2.x + src1[0][1] * src2.y + src1[0][2] * src2.z + src1[0][3];
		dst[1] = src1[1][0] * src2.x + src1[1][1] * src2.y + src1[1][2] * src2.z + src1[1][3];
		dst[2] = src1[2][0] * src2.x + src1[2][1] * src2.y + src1[2][2] * src2.z + src1[2][3];
	}

	//-----------------------------------------------------------------------------
	// Methods related to the basis vec3_ts of the matrix
	//-----------------------------------------------------------------------------

	inline vec3_t VMatrix::GetForward() const {
		return vec3_t(m[0][0], m[1][0], m[2][0]);
	}

	inline vec3_t VMatrix::GetLeft() const {
		return vec3_t(m[0][1], m[1][1], m[2][1]);
	}

	inline vec3_t VMatrix::GetUp() const {
		return vec3_t(m[0][2], m[1][2], m[2][2]);
	}

	inline void VMatrix::SetForward(const vec3_t &vForward) {
		m[0][0] = vForward.x;
		m[1][0] = vForward.y;
		m[2][0] = vForward.z;
	}

	inline void VMatrix::SetLeft(const vec3_t &vLeft) {
		m[0][1] = vLeft.x;
		m[1][1] = vLeft.y;
		m[2][1] = vLeft.z;
	}

	inline void VMatrix::SetUp(const vec3_t &vUp) {
		m[0][2] = vUp.x;
		m[1][2] = vUp.y;
		m[2][2] = vUp.z;
	}

	inline void VMatrix::GetBasisvec3_ts(vec3_t &vForward, vec3_t &vLeft, vec3_t &vUp) const {
		vForward.Init(m[0][0], m[1][0], m[2][0]);
		vLeft.Init(m[0][1], m[1][1], m[2][1]);
		vUp.Init(m[0][2], m[1][2], m[2][2]);
	}

	inline void VMatrix::SetBasisvec3_ts(const vec3_t &vForward, const vec3_t &vLeft, const vec3_t &vUp) {
		SetForward(vForward);
		SetLeft(vLeft);
		SetUp(vUp);
	}


	//-----------------------------------------------------------------------------
	// Methods related to the translation component of the matrix
	//-----------------------------------------------------------------------------

	inline vec3_t VMatrix::GetTranslation() const {
		return vec3_t(m[0][3], m[1][3], m[2][3]);
	}

	inline vec3_t& VMatrix::GetTranslation(vec3_t &vTrans) const {
		vTrans.x = m[0][3];
		vTrans.y = m[1][3];
		vTrans.z = m[2][3];
		return vTrans;
	}

	inline void VMatrix::SetTranslation(const vec3_t &vTrans) {
		m[0][3] = vTrans.x;
		m[1][3] = vTrans.y;
		m[2][3] = vTrans.z;
	}


	//-----------------------------------------------------------------------------
	// appply translation to this matrix in the input space
	//-----------------------------------------------------------------------------
	inline void VMatrix::PreTranslate(const vec3_t &vTrans) {
		vec3_t tmp;
		vec3_t3DMultiplyPosition(*this, vTrans, tmp);
		m[0][3] = tmp.x;
		m[1][3] = tmp.y;
		m[2][3] = tmp.z;
	}


	//-----------------------------------------------------------------------------
	// appply translation to this matrix in the output space
	//-----------------------------------------------------------------------------
	inline void VMatrix::PostTranslate(const vec3_t &vTrans) {
		m[0][3] += vTrans.x;
		m[1][3] += vTrans.y;
		m[2][3] += vTrans.z;
	}

	inline const matrix3x4_t& VMatrix::As3x4() const {
		return *((const matrix3x4_t*)this);
	}

	inline matrix3x4_t& VMatrix::As3x4() {
		return *((matrix3x4_t*)this);
	}

	inline void VMatrix::CopyFrom3x4(const matrix3x4_t &m3x4) {
		memcpy(m, m3x4.Base(), sizeof(matrix3x4_t));
		m[3][0] = m[3][1] = m[3][2] = 0;
		m[3][3] = 1;
	}

	inline void	VMatrix::Set3x4(matrix3x4_t& matrix3x4) const {
		memcpy(matrix3x4.Base(), m, sizeof(matrix3x4_t));
	}


	//-----------------------------------------------------------------------------
	// Matrix math operations
	//-----------------------------------------------------------------------------
	inline const VMatrix& VMatrix::operator+=(const VMatrix &other) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] += other.m[i][j];
			}
		}

		return *this;
	}

	inline VMatrix&	VMatrix::operator=(const VMatrix &mOther) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = mOther.m[i][j];
			}
		}

		return *this;
	}

	inline VMatrix VMatrix::operator+(const VMatrix &other) const {
		VMatrix ret;
		for (int i = 0; i < 16; i++) {
			((float*)ret.m)[i] = ((float*)m)[i] + ((float*)other.m)[i];
		}
		return ret;
	}

	inline VMatrix VMatrix::operator-(const VMatrix &other) const {
		VMatrix ret;

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret.m[i][j] = m[i][j] - other.m[i][j];
			}
		}

		return ret;
	}

	inline VMatrix VMatrix::operator-() const {
		VMatrix ret;
		for (int i = 0; i < 16; i++) {
			((float*)ret.m)[i] = -((float*)m)[i];
		}
		return ret;
	}

	//-----------------------------------------------------------------------------
	// vec3_t transformation
	//-----------------------------------------------------------------------------


	inline vec3_t VMatrix::operator*(const vec3_t &vVec) const {
		vec3_t vRet;
		vRet.x = m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z + m[0][3];
		vRet.y = m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z + m[1][3];
		vRet.z = m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z + m[2][3];

		return vRet;
	}

	inline vec3_t VMatrix::VMul4x3(const vec3_t &vVec) const {
		vec3_t vResult;
		vec3_t3DMultiplyPosition(*this, vVec, vResult);
		return vResult;
	}


	inline vec3_t VMatrix::VMul4x3Transpose(const vec3_t &vVec) const {
		vec3_t tmp = vVec;
		tmp.x -= m[0][3];
		tmp.y -= m[1][3];
		tmp.z -= m[2][3];

		return vec3_t(
			m[0][0] * tmp.x + m[1][0] * tmp.y + m[2][0] * tmp.z,
			m[0][1] * tmp.x + m[1][1] * tmp.y + m[2][1] * tmp.z,
			m[0][2] * tmp.x + m[1][2] * tmp.y + m[2][2] * tmp.z
		);
	}

	inline vec3_t VMatrix::VMul3x3(const vec3_t &vVec) const {
		return vec3_t(
			m[0][0] * vVec.x + m[0][1] * vVec.y + m[0][2] * vVec.z,
			m[1][0] * vVec.x + m[1][1] * vVec.y + m[1][2] * vVec.z,
			m[2][0] * vVec.x + m[2][1] * vVec.y + m[2][2] * vVec.z
		);
	}

	inline vec3_t VMatrix::VMul3x3Transpose(const vec3_t &vVec) const {
		return vec3_t(
			m[0][0] * vVec.x + m[1][0] * vVec.y + m[2][0] * vVec.z,
			m[0][1] * vVec.x + m[1][1] * vVec.y + m[2][1] * vVec.z,
			m[0][2] * vVec.x + m[1][2] * vVec.y + m[2][2] * vVec.z
		);
	}


	inline void VMatrix::V3Mul(const vec3_t &vIn, vec3_t &vOut) const {
		vec_t rw;

		rw = 1.0f / (m[3][0] * vIn.x + m[3][1] * vIn.y + m[3][2] * vIn.z + m[3][3]);
		vOut.x = (m[0][0] * vIn.x + m[0][1] * vIn.y + m[0][2] * vIn.z + m[0][3]) * rw;
		vOut.y = (m[1][0] * vIn.x + m[1][1] * vIn.y + m[1][2] * vIn.z + m[1][3]) * rw;
		vOut.z = (m[2][0] * vIn.x + m[2][1] * vIn.y + m[2][2] * vIn.z + m[2][3]) * rw;
	}

	//-----------------------------------------------------------------------------
	// Other random stuff
	//-----------------------------------------------------------------------------
	inline void VMatrix::Identity() {
		m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
		m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
		m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
		m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	}


	inline bool VMatrix::IsIdentity() const {
		return
			m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 0.0f && m[0][3] == 0.0f &&
			m[1][0] == 0.0f && m[1][1] == 1.0f && m[1][2] == 0.0f && m[1][3] == 0.0f &&
			m[2][0] == 0.0f && m[2][1] == 0.0f && m[2][2] == 1.0f && m[2][3] == 0.0f &&
			m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == 0.0f && m[3][3] == 1.0f;
	}

	inline vec3_t VMatrix::ApplyRotation(const vec3_t &vVec) const {
		return VMul3x3(vVec);
	}

	inline VMatrix VMatrix::operator~() const {
		VMatrix mRet;
		InverseGeneral(mRet);
		return mRet;
	}

	struct mstudiobbox_t
	{
		int					bone;
		int					group;				// intersection group
		vec3_t				bbmin;				// bounding box
		vec3_t				bbmax;
		int					szhitboxnameindex;	// offset to the name of the hitbox.
		int        m_iPad01[3];
		float        m_flRadius;
		int        m_iPad02[4];

		const char* pszHitboxName()
		{
			if (szhitboxnameindex == 0)
				return "";

			return ((char*)this) + szhitboxnameindex;
		}

		mstudiobbox_t() {}

	private:
		mstudiobbox_t(const mstudiobbox_t& vOther);
	};
	class quaternion
	{
	public:
		float x, y, z, w;
		float operator[](int i) const { if (i == 1) return x; if (i == 2) return y; if (y == 3) return z; return w; };
		float& operator[](int i) { if (i == 1) return x; if (i == 2) return y; if (y == 3) return z; return w; };
	};

	class radian_euler
	{
	public:
		float x, y, z;
	};
	struct mstudiobone_t
	{
		int					sznameindex;
		inline char * const pszName(void) const { return ((char *)this) + sznameindex; }
		int		 			parent;		// parent bone
		int					bonecontroller[6];	// bone controller index, -1 == none

												// default values
		vec3_t				pos;
		quaternion			quat;
		radian_euler			rot;
		// compression scale
		vec3_t				posscale;
		vec3_t				rotscale;

		matrix3x4_t			poseToBone;
		quaternion			qAlignment;
		int					flags;
		int					proctype;
		int					procindex;		// procedural rule
		mutable int			physicsbone;	// index into physically simulated bone
		inline void *pProcedure() const { if (procindex == 0) return NULL; else return  (void *)(((byte *)this) + procindex); };
		int					surfacepropidx;	// index into string tablefor property name
		inline char * const pszSurfaceProp(void) const { return ((char *)this) + surfacepropidx; }
		inline int			GetSurfaceProp(void) const { return surfacepropLookup; }

		int					contents;		// See BSPFlags.h for the contents flags
		int					surfacepropLookup;	// this index must be cached by the loader, not saved in the file
		int					unused[7];		// remove as appropriate

		mstudiobone_t() {}
	private:
		// No copy constructors allowed
		mstudiobone_t(const mstudiobone_t& vOther);
	};

	struct mstudiohitboxset_t
	{
		int					sznameindex;
		inline char * const	pszName(void) const { return ((char *)this) + sznameindex; }
		int					numhitboxes;
		int					hitboxindex;
		inline mstudiobbox_t *pHitbox(int i) const { return (mstudiobbox_t *)(((byte *)this) + hitboxindex) + i; };
	};

	class mstudioanimdesc_t {
	};
	class mstudioseqdesc_t {
	};

	class studiohdr_t
	{
	public:
		__int32 id;                     //0x0000 
		__int32 version;                //0x0004 
		long    checksum;               //0x0008 
		char    szName[64];             //0x000C 
		__int32 length;                 //0x004C 
		vec3_t  vecEyePos;              //0x0050 
		vec3_t  vecIllumPos;            //0x005C 
		vec3_t  vecHullMin;             //0x0068 
		vec3_t  vecHullMax;             //0x0074 
		vec3_t  vecBBMin;               //0x0080 
		vec3_t  vecBBMax;               //0x008C 
		__int32 flags;                  //0x0098 
		__int32 numbones;               //0x009C 
		__int32 boneindex;              //0x00A0 
		__int32 numbonecontrollers;     //0x00A4 
		__int32 bonecontrollerindex;    //0x00A8 
		__int32 numhitboxsets;          //0x00AC 
		__int32 hitboxsetindex;         //0x00B0 
		__int32 numlocalanim;           //0x00B4 
		__int32 localanimindex;         //0x00B8 
		__int32 numlocalseq;            //0x00BC 
		__int32 localseqindex;          //0x00C0 
		__int32 activitylistversion;    //0x00C4 
		__int32 eventsindexed;          //0x00C8 
		__int32 numtextures;            //0x00CC 
		__int32 textureindex;           //0x00D0

		mstudiohitboxset_t* GetHitboxSet(int i)
		{
			if (i > numhitboxsets) return nullptr;
			return (mstudiohitboxset_t*)((uint8_t*)this + hitboxsetindex) + i;
		}
		mstudiobone_t* GetBone(int i)
		{
			if (i > numbones) return nullptr;
			return (mstudiobone_t*)((uint8_t*)this + boneindex) + i;
		}

	};//Size=0x00D4
}