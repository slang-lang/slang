
#ifndef _Math_Normals_h_
#define _Math_Normals_h_


// Library includes

// Project includes
#include "Vector3.h"

// Forward declarations

// Namespace declarations


class Vertex
{
public:
	vector3f	mNormal;
	vector3f	mVertex;
};

class Face
{
public:
	vector3f	v[3];
	vector3f	vNormal;
};


void getNormal(vector3f v[3], vector3f *normal);
vector3f normalize(vector3f vector);


#endif
