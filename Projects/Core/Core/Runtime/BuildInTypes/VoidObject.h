
#ifndef Core_Runtime_BuildInTypes_VoidObject_h
#define Core_Runtime_BuildInTypes_VoidObject_h


// Library includes
#include <string>

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class VoidObject : public Object
{
public:
	static std::string TYPENAME;

public:
	VoidObject();
	explicit VoidObject(const std::string& name);
	explicit VoidObject(const Object& other);

public:	// Operators
	bool operator_bool() const;

public: // Value
	bool isValid() const;
};


}
}


#endif
