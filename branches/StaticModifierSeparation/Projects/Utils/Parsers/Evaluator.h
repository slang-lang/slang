
#ifndef Utils_Parsers_Evaluator_h
#define Utils_Parsers_Evaluator_h


// Library includes

// Project includes
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// Forward declarations

// Namespace declarations


namespace Utils {

// Forward declarations
class Valueizer;

class Evaluator
{
public:
	static vector2f toVector2f(Valueizer *t);
	static vector3f toVector3f(Valueizer *t);
	static vector4f toVector4f(Valueizer *t);

protected:

private:

};


}


#endif
