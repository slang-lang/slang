
// Header
#include "Evaluator.h"

// Library includes

// Project includes
#include "Valueizer.h"

// Namespace declarations


namespace Utils {


vector2f Evaluator::toVector2f(Valueizer *t)
{
	Value val = t->getTokenAsValue();

	vector2f vec;
	vec.x = val.toFloat();
	if ( t->hasNext() ) {
		val = Value(t->getToken());
		vec.y = val.toFloat();

		return vec;
	}

	return vector2f();
}

vector3f Evaluator::toVector3f(Valueizer *t)
{
	Value val = t->getTokenAsValue();

	vector3f vec;
	vec.x = val.toFloat();
	if ( t->hasNext() ) {
		val = Value(t->getToken());
		vec.y = val.toFloat();

		if ( t->hasNext() ) {
			val = Value(t->getToken());
			vec.z = val.toFloat();

			return vec;
		}
	}

	return vector3f();
}

vector4f Evaluator::toVector4f(Valueizer *t)
{
	Value val = t->getTokenAsValue();

	vector4f vec;
	vec.x = val.toFloat();
	if ( t->hasNext() ) {
		val = Value(t->getToken());
		vec.y = val.toFloat();

		if ( t->hasNext() ) {
			val = Value(t->getToken());
			vec.z = val.toFloat();

			if ( t->hasNext() ) {
				val = Value(t->getToken());
				vec.w = val.toFloat();

				return vec;
			}
		}
	}

	return vector4f();
}


}
