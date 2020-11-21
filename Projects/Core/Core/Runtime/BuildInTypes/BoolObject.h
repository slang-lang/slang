
#ifndef Core_Runtime_BuildInTypes_BoolObject_h
#define Core_Runtime_BuildInTypes_BoolObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class BoolObject : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
    explicit BoolObject( bool value = false );
	explicit BoolObject( const AtomicValue& value );
	explicit BoolObject( const std::string& name, const AtomicValue& value );
	explicit BoolObject( const Object& other );

public:	// Operators
	void operator_assign( const Object* rvalue );
	bool operator_bool() const;
	bool operator_equal( const Object* rvalue );
	void operator_unary_not();
};


}
}


#endif
