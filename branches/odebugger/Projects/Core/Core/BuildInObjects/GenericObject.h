
#ifndef Core_Runtime_BuildInObjects_GenericObject_h
#define Core_Runtime_BuildInObjects_GenericObject_h


// Library includes
#include <string>

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class GenericObject : public Object
{
public:
	static std::string DEFAULTVALUE;
	static std::string TYPENAME;

public:
	GenericObject();
	GenericObject(const std::string& name, const std::string& filename, const std::string& type, AtomicValue value);
	GenericObject(const Object& object);

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;
};


}
}


#endif
