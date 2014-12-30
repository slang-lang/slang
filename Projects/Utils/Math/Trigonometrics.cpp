
// Header
#include "Trigonometrics.h"

// Library includes

// Project includes
#include "Tools.h"

// Namespace declarations


namespace Math {


float degreeToRad(float degree)
{
	return degree * PI / 180.f;
}


float radToDegree(float rad)
{
	return rad * 180.f / PI;
}


}
