
#ifndef ObjectiveScript_Core_Runtime_OperatorOverloading_h
#define ObjectiveScript_Core_Runtime_OperatorOverloading_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Symbol;

namespace Runtime {

// Forward declarations
class Object;

void operator_binary_assign(Object *base, Object *other);
void operator_binary_bitand(Object *base, Object *other);
void operator_binary_bitcomplement(Object *base, Object *other);
void operator_binary_bitor(Object *base, Object *other);
void operator_binary_divide(Object *base, Object *other);
bool operator_binary_equal(Object *base, Object *other);
bool operator_binary_greater(Object *base, Object *other);
bool operator_binary_greater_equal(Object *base, Object *other);
bool operator_binary_less(Object *base, Object *other);
bool operator_binary_less_equal(Object *base, Object *other);
bool operator_binary_is(Object* base, Symbol* other);
void operator_binary_modulo(Object *base, Object *other);
void operator_binary_multiply(Object *base, Object *other);
void operator_binary_plus(Object *base, Object *other);
void operator_binary_subtract(Object *base, Object *other);
void operator_trinary_array(Object *base, Object *index, Object* other);
void operator_unary_infix_decrement(Object *base);
void operator_unary_infix_increment(Object *base);
void operator_unary_minus(Object *base);
void operator_unary_not(Object *base);
void operator_unary_postfix_decrement(Object *base);
void operator_unary_postfix_increment(Object *base);
void operator_unary_validate(Object *base);


}
}


#endif
