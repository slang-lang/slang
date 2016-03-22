
#ifndef ObjectiveScript_Core_Runtime_OperatorOverloading_h
#define ObjectiveScript_Core_Runtime_OperatorOverloading_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {

// Forward declarations
class Object;


void operator_assign(Object *base, Object *other);
void operator_bitand(Object *base, Object *other);
void operator_bitcomplement(Object *base, Object *other);
void operator_bitor(Object *base, Object *other);
void operator_divide(Object *base, Object *other);
bool operator_equal(Object *base, Object *other);
bool operator_greater(Object *base, Object *other);
bool operator_greater_equal(Object *base, Object *other);
bool operator_less(Object *base, Object *other);
bool operator_less_equal(Object *base, Object *other);
void operator_modulo(Object *base, Object *other);
void operator_multiply(Object *base, Object *other);
void operator_plus(Object *base, Object *other);
void operator_subtract(Object *base, Object *other);
void operator_unary_decrement(Object *base);
void operator_unary_increment(Object *base);
void operator_unary_minus(Object *base);
void operator_unary_not(Object *base);


}
}


#endif
