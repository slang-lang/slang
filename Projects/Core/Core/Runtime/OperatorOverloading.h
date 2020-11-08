
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

void operator_binary_assign(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_binary_bitand(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_binary_bitcomplement(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_binary_bitor(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_binary_divide(Object* left, Object* right, const Common::Position& position = Common::Position());
bool operator_binary_equal(Object* left, Object* right, const Common::Position& position = Common::Position());
bool operator_binary_greater(Object* left, Object* right, const Common::Position& position = Common::Position());
bool operator_binary_greater_equal(Object* left, Object* right, const Common::Position& position = Common::Position());
bool operator_binary_less(Object* left, Object* right, const Common::Position& position = Common::Position());
bool operator_binary_less_equal(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_binary_modulo(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_binary_multiply(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_binary_plus(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_binary_subtract(Object* left, Object* right, const Common::Position& position = Common::Position());
void operator_unary_decrement(Object* base, const Common::Position& position = Common::Position());
void operator_unary_increment(Object* base, const Common::Position& position = Common::Position());
void operator_unary_minus(Object* base, const Common::Position& position = Common::Position());
void operator_unary_plus(Object* base, const Common::Position& position = Common::Position());
void operator_unary_not(Object* base, const Common::Position& position = Common::Position());
void operator_unary_validate(Object* base, const Common::Position& position = Common::Position());


}
}


#endif
