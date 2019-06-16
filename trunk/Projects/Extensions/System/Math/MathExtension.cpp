
// Header
#include "MathExtension.h"

// Library includes

// Project includes
#include "Abs.h"
#include "Ceil.h"
#include "Floor.h"
#include "Rand.h"
#include "Round.h"
#include "Sqrt.h"
#include "Srand.h"
#include "Trunc.h"

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Math {


SystemMathExtension::SystemMathExtension()
: AExtension("Math")
{
}

SystemMathExtension::~SystemMathExtension()
{
}

void SystemMathExtension::initialize(ObjectiveScript::IScope* /*scope*/)
{
	// nothing to do here
}

void SystemMathExtension::provideMethods(ExtensionMethods &methods)
{
	methods.push_back(new AbsDouble());
	methods.push_back(new AbsFloat());
	methods.push_back(new AbsInt());
	methods.push_back(new CeilDouble());
	methods.push_back(new CeilFloat());
	methods.push_back(new FloorDouble());
	methods.push_back(new FloorFloat());
	methods.push_back(new Rand());
	methods.push_back(new RoundDouble());
	methods.push_back(new RoundFloat());
	methods.push_back(new SqrtDouble());
	methods.push_back(new SqrtFloat());
	methods.push_back(new Srand());
	methods.push_back(new TruncDouble());
	methods.push_back(new TruncFloat());

}


}
}
}
}
