
#ifndef Core_Runtime_BuildInTypes_UserType_h
#define Core_Runtime_BuildInTypes_UserType_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class UserType : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	UserType();
	explicit UserType( const std::string& name, const std::string& filename, const std::string& type, bool isReference = false );
	explicit UserType( const Object& object) ;
};


}
}


#endif
