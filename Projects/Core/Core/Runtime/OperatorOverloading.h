
#ifndef Slang_Core_Core_Runtime_OperatorOverloading_h
#define Slang_Core_Core_Runtime_OperatorOverloading_h


// Library includes
#include <string>

// Project includes
#include <Core/Common/Position.h>

// Forward declarations

// Namespace declarations


namespace Slang {

// Forward declarations
class Symbol;

namespace Runtime {

// Forward declarations
class Object;

void operator_binary_assign( Object* lvalue, Object* rvalue );
void operator_binary_bitand( Object* lvalue, Object* rvalue );
void operator_binary_bitcomplement( Object* lvalue, Object* rvalue );
void operator_binary_bitor( Object* lvalue, Object* rvalue );
void operator_binary_divide( Object* lvalue, Object* rvalue );
bool operator_binary_equal( Object* lvalue, Object* rvalue );
bool operator_binary_greater( Object* lvalue, Object* rvalue );
bool operator_binary_greater_equal( Object* lvalue, Object* rvalue );
bool operator_binary_less( Object* lvalue, Object* rvalue );
bool operator_binary_less_equal( Object* lvalue, Object* rvalue );
void operator_binary_modulo( Object* lvalue, Object* rvalue );
void operator_binary_multiply( Object* lvalue, Object* rvalue );
void operator_binary_plus( Object* lvalue, Object* rvalue );
void operator_binary_subtract( Object* lvalue, Object* rvalue );
void operator_unary_decrement( Object* lvalue );
void operator_unary_increment( Object* lvalue );
void operator_unary_minus( Object* lvalue );
void operator_unary_plus( Object* lvalue );
void operator_unary_not( Object* base );
void operator_unary_validate( Object* base );


}
}


#endif
