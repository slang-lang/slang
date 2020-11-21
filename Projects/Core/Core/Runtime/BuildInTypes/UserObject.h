
#ifndef Core_Runtime_BuildInTypes_UserObject_h
#define Core_Runtime_BuildInTypes_UserObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class UserObject : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	UserObject();
	explicit UserObject( const std::string& name, const std::string& filename, const std::string& type, bool isReference = false );
	explicit UserObject( const Object& object) ;
};


}
}


#endif
