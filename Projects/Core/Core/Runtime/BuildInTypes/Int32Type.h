
#ifndef Core_Runtime_BuildInTypes_Int32Type_h
#define Core_Runtime_BuildInTypes_Int32Type_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class Int32Type : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	explicit Int32Type( int32_t value = 0 );
	explicit Int32Type( const AtomicValue& value );
	explicit Int32Type( const std::string& name, const AtomicValue& value );
	explicit Int32Type( const Object& object );

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	void operator_assign( const Object* other );
	bool operator_bool() const;
	void operator_bitand( const Object* other );
	void operator_bitor( const Object* other );
	void operator_divide( const Object* other );
	bool operator_equal( const Object* other );
	bool operator_greater( const Object* other );
	bool operator_greater_equal( const Object* other );
	bool operator_less( const Object* other );
	bool operator_less_equal( const Object* other );
	void operator_modulo( const Object* other );
	void operator_multiply( const Object* other );
	void operator_plus( const Object* other );
	void operator_subtract( const Object* other );
	void operator_unary_decrement();
	void operator_unary_increment();
	void operator_unary_minus();
	void operator_unary_not();
};


}
}


#endif
