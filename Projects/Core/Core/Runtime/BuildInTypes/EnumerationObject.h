
#ifndef Core_Runtime_BuildInTypes_EnumerationObject_h
#define Core_Runtime_BuildInTypes_EnumerationObject_h


// Library includes

// Project includes
#include <Core/Object.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class EnumerationObject : public Object
{
public:
	static AtomicValue DEFAULTVALUE;
	static std::string TYPENAME;

public:
	explicit EnumerationObject( const std::string& name, const std::string& type, const AtomicValue& value );

public:	// Symbol::IType implementation
	const std::string& getTypeName() const;

public:	// Operators
	void operator_assign( const Object* other );
	bool operator_bool() const;
	bool operator_equal( const Object* other );
	bool operator_greater( const Object* other );
	bool operator_greater_equal( const Object* other );
	bool operator_less( const Object* other );
	bool operator_less_equal( const Object* other );

public: // Values
	bool isValid() const;
};


}
}


#endif
