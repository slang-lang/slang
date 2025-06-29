
#ifndef Core_Runtime_BuildInTypes_String_h
#define Core_Runtime_BuildInTypes_String_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class StringType : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	explicit StringType( const std::string& value = "" );
	explicit StringType( const AtomicValue& value );
	explicit StringType( const std::string& name, const AtomicValue& value );
	explicit StringType( const Object& other );

public:	// Operators
	void operator_assign( const Object* other );
	bool operator_bool() const;
	bool operator_equal( const Object* other );
	bool operator_greater( const Object* other );
	bool operator_greater_equal( const Object* other );
	bool operator_less( const Object* other );
	bool operator_less_equal( const Object* other );
	void operator_plus( const Object* other );
	void operator_shift_left( const Object* other );
};


}
}


#endif
