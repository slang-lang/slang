
#ifndef Core_Runtime_BuildInTypes_VoidType_h
#define Core_Runtime_BuildInTypes_VoidType_h


// Library includes
#include <string>

// Project includes
#include <Core/Runtime/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class VoidType : public Object
{
public:
	static std::string TYPENAME;

public:
	VoidType();
	explicit VoidType( const std::string& name );
	explicit VoidType( const Object& other );

public:	// Operators
	bool operator_bool() const;

public: // Value
	bool isValid() const;
};


}
}


#endif
