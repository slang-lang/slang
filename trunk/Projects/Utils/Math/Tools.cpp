
// Header
#include "Tools.h"

// Library includes
#include <cmath>

// Project includes
#include "Vector3.h"

// Namespace declarations


const float fPi = 3.14159265f;
//const double dPi = 3.1415926535897932384626433832795;
const double dPI = 2 * std::acos(0.0);


/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns a perpendicular vector from 2 given vectors by taking the cross product.
/////
/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

vector3f cross(const vector3f& v1, const vector3f& v2)
{
	vector3f r;	

	// Calculate the cross product with the non communitive equation
	r.x = ((v1.y * v2.z) - (v1.z * v2.y));
	r.y = ((v1.z * v2.x) - (v1.x * v2.z));
	r.z = ((v1.x * v2.y) - (v1.y * v2.x));

	// Return the cross product
	return r;										 
}

float distance(const vector3f& v1, const vector3f& v2)
{
	return fastSquareRoot(power(v1.x + v2.x) + power(v1.y + v2.y) + power(v1.z + v2.z));
}

float fastsqrtf(const float x)
{
	union
	{
		int i;
		float x;
	} u;

	u.x = x;
	u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

	// Two Babylonian Steps (simplified from:)
	// u.x = 0.5f * (u.x + x/u.x);
	// u.x = 0.5f * (u.x + x/u.x);
	u.x =         u.x + x / u.x;
	u.x = 0.25f * u.x + x / u.x;

	return u.x;
}

float fastSquareRoot(float x)
{
#ifdef _MSC_VER
	__asm {
		fld x;
		fsqrt;
		fstp x;
	}
#elif __APPLE__
#if TARGET_IPHONE_SIMULATOR
    // iOS Simulator
#elif TARGET_OS_IPHONE
    // iOS device
#elif TARGET_OS_MAC
    // Other kinds of Mac OS
	__asm__ ("fsqrt" : "+t" (x));
#else
    // Unsupported platform
#endif
#elif __linux
	asm("fld x; fsqrt; fstp x;");
#endif

	return x;
}

/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the magnitude of a vector
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*

float magnitude(const vector3f& vNormal)
{
	// Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2) : Where V is the vector
	return fastSquareRoot( (vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z) );
}

float power(float p)
{
	return p * p;
}
