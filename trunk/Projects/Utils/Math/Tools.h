
#ifndef _Math_Tools_h_
#define _Math_Tools_h_


// Library includes
#include <math.h>

// Project includes

// Forward declarations
class vector3f;

// Namespace declarations


#define SQR(a)  (a * a)

#define PI 3.14159265f


extern const float fPi;
extern const double dPi;


extern vector3f cross(const vector3f& v1, const vector3f& v2);
extern float distance(const vector3f& v1, const vector3f& v2);
extern inline float fastsqrtf(const float x);
extern inline float fastSquareRoot(float x);
extern float magnitude(const vector3f& vNormal);
extern float power(float p);


#endif
