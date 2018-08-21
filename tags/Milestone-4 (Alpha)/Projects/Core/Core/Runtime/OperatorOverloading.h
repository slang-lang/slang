
#ifndef ObjectiveScript_Core_Runtime_OperatorOverloading_h
#define ObjectiveScript_Core_Runtime_OperatorOverloading_h


// Library includes
#include <string>

// Project includes
#include <Core/Common/Position.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Symbol;

namespace Runtime {

// Forward declarations
class Object;

void operator_binary_assign(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_binary_bitand(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_binary_bitcomplement(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_binary_bitor(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_binary_divide(Object *base, Object *other, const Common::Position& position = Common::Position());
bool operator_binary_equal(Object *base, Object *other, const Common::Position& position = Common::Position());
bool operator_binary_greater(Object *base, Object *other, const Common::Position& position = Common::Position());
bool operator_binary_greater_equal(Object *base, Object *other, const Common::Position& position = Common::Position());
bool operator_binary_less(Object *base, Object *other, const Common::Position& position = Common::Position());
bool operator_binary_less_equal(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_binary_modulo(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_binary_multiply(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_binary_plus(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_binary_subtract(Object *base, Object *other, const Common::Position& position = Common::Position());
void operator_unary_decrement(Object *base, const Common::Position& position = Common::Position());
void operator_unary_increment(Object *base, const Common::Position& position = Common::Position());
void operator_unary_minus(Object *base, const Common::Position& position = Common::Position());
void operator_unary_plus(Object *base, const Common::Position& position = Common::Position());
void operator_unary_not(Object *base, const Common::Position& position = Common::Position());
void operator_unary_validate(Object *base, const Common::Position& position = Common::Position());


}
}


#endif
