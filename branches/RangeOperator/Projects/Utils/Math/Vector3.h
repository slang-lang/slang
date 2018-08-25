
#ifndef _Math_Vector3_h_
#define _Math_Vector3_h_


// Library includes
#include <ostream>

// Project includes

// Forward declarations

// Namespace declarations


template <class T>
class vector3
{
public:
	vector3()
	: x(static_cast<T>(0)),
	  y(static_cast<T>(0)),
	  z(static_cast<T>(0))
	{ }
	vector3(T _x, T _y, T _z)
	: x(_x),
	  y(_y),
	  z(_z)
	{ }
	virtual ~vector3() { }

public:
	T x;
	T y;
	T z;
};


class vector3f// : public vector3<float>
{
public:
	vector3f();
    vector3f(float _x, float _y, float _z);

public:
	vector3f cross(const vector3f& other) const;
	float length();
    void normalize();

public:
    // Operators...
    vector3f operator + (const vector3f& other);
    vector3f operator - (const vector3f& other);
    vector3f operator * (const vector3f& other);
	vector3f operator / (const vector3f& other);

    vector3f operator * (const float scalar);
    friend vector3f operator * (const float scalar, const vector3f& other);

	vector3f operator / (const float scalar);
    friend vector3f operator / (const float scalar, const vector3f& other);
    
	vector3f& operator = (const vector3f& other);
    vector3f& operator += (const vector3f& other);
    vector3f& operator -= (const vector3f& other);

    vector3f& operator *= (const float scalar);
    vector3f& operator /= (const float scalar);

	vector3f operator + (void) const;
	vector3f operator - (void) const;

	bool operator == (const vector3f& other);
	bool operator != (const vector3f& other);

public:
	// Static utility methods
    static float distance(const vector3f& v1, const vector3f& v2);
    static float dotProduct(const vector3f& v1,  const vector3f& v2);
    static vector3f crossProduct(const vector3f& v1, const vector3f& v2);

public:
	float x;
	float y;
	float z;
};


class vector3i : public vector3<int>
{
public:
	vector3i()
	: vector3<int>(0, 0, 0)
	{ }
	vector3i(int _x, int _y, int _z)
	: vector3<int>(_x, _y, _z)
	{ }
};


class vector3l : public vector3<long>
{
public:
	vector3l()
	: vector3<long>(0, 0, 0)
	{ }
	vector3l(long _x, long _y, long _z)
	: vector3<long>(_x, _y, _z)
	{ }
};


inline std::ostream &operator<<(std::ostream &s, const vector3f &v)
{
    s << "(" << v.x << "/" << v.y << "/" << v.z << ")";
    return s;
}


#endif
