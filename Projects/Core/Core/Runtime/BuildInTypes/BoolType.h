
#ifndef Core_Runtime_BuildInTypes_BoolType_h
#define Core_Runtime_BuildInTypes_BoolType_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class BoolType : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	explicit BoolType( bool value = false );
	explicit BoolType( const AtomicValue& value );
	explicit BoolType( const std::string& name, const AtomicValue& value );
	explicit BoolType( const Object& other );

public:	// Operators
	void operator_assign( const Object* rvalue );
	bool operator_bool() const;
	bool operator_equal( const Object* rvalue );
	void operator_unary_not();
};


}
}


#endif
