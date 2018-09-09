
// Header
#include "Vector3.h"

// Library includes
#include <cmath>

// Project includes

// Namespace declarations


vector3f::vector3f()
//: vector3<float>(0.f, 0.f, 0.f)
: x(0.f),
  y(0.f),
  z(0.f)
{
}

vector3f::vector3f(float _x, float _y, float _z)
//: vector3<float>(_x, _y, _z)
: x(_x),
  y(_y),
  z(_z)
{
}

vector3f vector3f::cross(const vector3f& other) const
{
	vector3f c;

    c.x = y * other.z - z * other.y;
    c.y = z * other.x - x * other.z;
    c.z = x * other.y - y * other.x;

	return c;
}

float vector3f::length( void )
{
    return (float)sqrt( x * x + y * y + z * z );
}

void vector3f::normalize()
{
	float l = length();

	x = x / l;
	y = y / l;
	z = z / l;
}

//
// Operators...
//

vector3f vector3f::operator + ( const vector3f& other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x + other.x;
    vResult.y = y + other.y;
    vResult.z = z + other.z;

    return vResult;
}

vector3f vector3f::operator + ( void ) const
{
    return *this;
}

vector3f vector3f::operator - ( const vector3f& other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x - other.x;
    vResult.y = y - other.y;
    vResult.z = z - other.z;

    return vResult;
}

vector3f vector3f::operator - ( void ) const
{
    vector3f vResult(-x, -y, -z);

    return vResult;
}

vector3f vector3f::operator * ( const vector3f& other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x * other.x;
    vResult.y = y * other.y;
    vResult.z = z * other.z;

    return vResult;
}

vector3f vector3f::operator * ( const float scalar )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x * scalar;
    vResult.y = y * scalar;
    vResult.z = z * scalar;

    return vResult;
}

vector3f operator * ( const float scalar, const vector3f& other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = other.x * scalar;
    vResult.y = other.y * scalar;
    vResult.z = other.z * scalar;

    return vResult;
}

vector3f vector3f::operator / ( const vector3f& other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x / other.x;
    vResult.y = y / other.y;
    vResult.z = z / other.z;

    return vResult;
}

vector3f vector3f::operator / ( const float scalar )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = x / scalar;
    vResult.y = y / scalar;
    vResult.z = z / scalar;

    return vResult;
}

vector3f operator / ( const float scalar, const vector3f& other )
{
    vector3f vResult(0.0f, 0.0f, 0.0f);

    vResult.x = other.x / scalar;
    vResult.y = other.y / scalar;
    vResult.z = other.z / scalar;

    return vResult;
}

vector3f& vector3f::operator = ( const vector3f& other )
{
	x = other.x;
	y = other.y;
	z = other.z;

    return *this;
}

vector3f& vector3f::operator += ( const vector3f& other )
{
    x += other.x;
    y += other.y;
    z += other.z;

    return *this;
}

vector3f& vector3f::operator -= ( const vector3f& other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

vector3f& vector3f::operator *= ( const float scalar )
{
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

vector3f& vector3f::operator /= ( const float scalar )
{
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
}

bool vector3f::operator == (const vector3f& other)
{
	return (this->x == other.x) && (this->y == other.y) && (this->z == other.z);
}

bool vector3f::operator != (const vector3f& other)
{
	return (this->x != other.x) || (this->y != other.y) || (this->z != other.z);
}

//
// Static utility methods...
//

float vector3f::distance( const vector3f& v1,  const vector3f& v2  )
{
	float dx = v1.x - v2.x;
	float dy = v1.y - v2.y;
	float dz = v1.z - v2.z;

	return (float)sqrt( dx * dx + dy * dy + dz * dz );
}

float vector3f::dotProduct( const vector3f& v1,  const vector3f& v2 )
{
	return( v1.x * v2.x + v1.y * v2.y + v1.z * v2.z  );
}

vector3f vector3f::crossProduct( const vector3f& v1,  const vector3f& v2 )
{
	vector3f vCrossProduct;

    vCrossProduct.x = v1.y * v2.z - v1.z * v2.y;
    vCrossProduct.y = v1.z * v2.x - v1.x * v2.z;
    vCrossProduct.z = v1.x * v2.y - v1.y * v2.x;

	return vCrossProduct;
}
