
#ifndef _Math_Vector4_h_
#define _Math_Vector4_h_


// Library includes
#include <ostream>

// Project includes

// Forward declarations

// Namespace declarations


template <class T>
class vector4
{
public:
	vector4()
	: x(static_cast<T>(0)),
	  y(static_cast<T>(0)),
	  z(static_cast<T>(0)),
	  w(static_cast<T>(0))
	{ }
	vector4(T _x, T _y, T _z, T _w)
	: x(_x),
	  y(_y),
	  z(_z),
	  w(_w)
	{ }
	virtual ~vector4() { }

public:
	T x;
	T y;
	T z;
	T w;
};


class vector4f : public vector4<float>
{
public:
	vector4f()
	: vector4<float>(0.f, 0.f, 0.f, 0.f)
	{ }
	vector4f(float _x, float _y, float _z, float _w)
	: vector4<float>(_x, _y, _z, _w)
	{ }
};


class vector4i : public vector4<int>
{
public:
	vector4i()
	: vector4<int>(0, 0, 0, 0)
	{ }
	vector4i(int _x, int _y, int _z, int _w)
	: vector4<int>(_x, _y, _z, _w)
	{ }
};


class vector4l : public vector4<long>
{
public:
	vector4l()
	: vector4<long>(0, 0, 0, 0)
	{ }
	vector4l(long _x, long _y, long _z, long _w)
	: vector4<long>(_x, _y, _z, _w)
	{ }
};


inline std::ostream &operator<<(std::ostream &s, const vector4f &v)
{
    s << "(" << v.x << "/" << v.y << "/" << v.z << "/" << v.w << ")";
    return s;
}


#endif
