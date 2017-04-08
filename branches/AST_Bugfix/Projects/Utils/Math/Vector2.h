
#ifndef _Math_Vector2_h_
#define _Math_Vector2_h_


// Library includes
#include <ostream>

// Project includes

// Forward declarations

// Namespace declarations


template <class T>
class vector2
{
public:
	vector2()
	: x(static_cast<T>(0)),
	  y(static_cast<T>(0))
	{ }
	vector2(T _x, T _y)
	: x(_x),
	  y(_y)
	{ }

	T x;
	T y;
};


class vector2f : public vector2<float>
{
public:
	vector2f()
	{ }
	vector2f(float _x, float _y)
	: vector2<float>(_x, _y)
	{ }
};

class vector2i : public vector2<int>
{
public:
	vector2i()
	{ }
	vector2i(int _x, int _y)
	: vector2<int>(_x, _y)
	{ }
};

class vector2l : public vector2<long>
{
public:
	vector2l()
	{ }
	vector2l(long _x, long _y)
	: vector2<long>(_x, _y)
	{ }
};


inline std::ostream &operator<<(std::ostream &s, const vector2f &v)
{
    s << "(" << v.x << "/" << v.y << ")";
    return s;
}


#endif
