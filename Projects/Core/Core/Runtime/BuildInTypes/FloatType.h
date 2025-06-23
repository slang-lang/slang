
#ifndef Core_Runtime_BuildInTypes_FloatType_h
#define Core_Runtime_BuildInTypes_FloatType_h


// Library includes

// Project includes
#include <Core/Runtime/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class FloatType : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
    explicit FloatType( float value = 0.0f );
	explicit FloatType( const AtomicValue& value );
	explicit FloatType( const std::string& name, const AtomicValue& value );
	explicit FloatType( const Object& object );

public:	// Operators
	void operator_assign( const Object* other );
	bool operator_bool() const;
	void operator_divide( const Object* other );
	bool operator_equal( const Object* other );
	bool operator_greater( const Object* other );
	bool operator_greater_equal( const Object* other );
	bool operator_less( const Object* other );
	bool operator_less_equal( const Object* other );
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
