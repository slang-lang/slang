
#ifndef ObjectiveScript_Extensions_System_Math_Srand_h
#define ObjectiveScript_Extensions_System_Math_Srand_h


// Library includes
#include <math.h>

// Project includes
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/VoidObject.h>
#include <Core/Extensions/ExtensionMethod.h>
#include <Core/Tools.h>
#include <Tools/Strings.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace System {
namespace Math {


class Srand: public ExtensionMethod
{
public:
	Srand()
	: ExtensionMethod(0, "srand", Designtime::VoidObject::TYPENAME)
	{
		ParameterList params;
		params.push_back(Parameter("value", Designtime::IntegerObject::TYPENAME, VALUE_NONE));

		setSignature(params);
	}

public:
	Runtime::ControlFlow::E execute(const ParameterList& params, Runtime::Object* /*result*/, const Token& token)
	{
		ParameterList list = mergeParameters(params);

		try {
			ParameterList::const_iterator it = list.begin();

			int param_value = (it++)->value().toInt();

			srand(param_value);
		}
		catch ( std::exception& e ) {
			Runtime::Object *data = Repository::GetInstance().createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
			*data = Runtime::StringObject(std::string(e.what()));

			mExceptionData = Runtime::ExceptionData(data, token.position());
			return Runtime::ControlFlow::Throw;
		}

		return Runtime::ControlFlow::Normal;
	}
};


}
}
}
}


#endif
