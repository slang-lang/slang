
// Header
#include "AtomicValue.h"

// Library includes
#include <cassert>

// Project includes
#include <Tools/Strings.h>

#include <utility>

// Namespace declarations


namespace Slang {
namespace Runtime {


AtomicValue::AtomicValue()
: mType(Type::INT)
{
    mValue.bool_ = false;
    mValue.double_ = 0.0;
    mValue.float_ = 0.f;
    mValue.int_ = 0;
    mValue.reference_ = 0;
}

AtomicValue::AtomicValue(bool val)
: mType(Type::BOOL)
{
    mValue.double_ = 0.0;
    mValue.float_ = 0.f;
    mValue.int_ = 0;
    mValue.reference_ = 0;

    mValue.bool_ = val;
}

AtomicValue::AtomicValue(double val)
: mType(Type::DOUBLE)
{
    mValue.bool_ = false;
    mValue.float_ = 0.f;
    mValue.int_ = 0;
    mValue.reference_ = 0;

    mValue.double_ = val;
}

AtomicValue::AtomicValue(float val)
: mType(Type::FLOAT)
{
    mValue.bool_ = false;
    mValue.double_ = 0.0;
    mValue.int_ = 0;
    mValue.reference_ = 0;

    mValue.float_ = val;
}

AtomicValue::AtomicValue(int16_t val)
: mType(Type::INT)
{
    mValue.bool_ = false;
    mValue.double_ = 0.0;
    mValue.float_ = 0.f;
    mValue.reference_ = 0;

    mValue.int_ = val;
}

AtomicValue::AtomicValue(int32_t val)
: mType(Type::INT)
{
    mValue.bool_ = false;
    mValue.double_ = 0.0;
    mValue.float_ = 0.f;
    mValue.reference_ = 0;

    mValue.int_ = val;
}

AtomicValue::AtomicValue(int64_t val)
: mType(Type::INT)
{
    mValue.bool_ = false;
    mValue.double_ = 0.0;
    mValue.float_ = 0.f;
    mValue.reference_ = 0;

    mValue.int_ = val;
}

AtomicValue::AtomicValue(MemoryId val)
: mType(Type::REFERENCE)
{
    mValue.bool_ = false;
    mValue.double_ = 0.0;
    mValue.float_ = 0.f;
    mValue.int_ = 0;

    mValue.reference_ = val;
}

AtomicValue::AtomicValue(std::string val)
: mStringValue(std::move(val)),
  mType(Type::STRING)
{
    mValue.bool_ = false;
    mValue.double_ = 0.0;
    mValue.float_ = 0.f;
    mValue.int_ = 0;
    mValue.reference_ = 0;
}

AtomicValue& AtomicValue::operator=(bool val)
{
    mStringValue = "";

    mType = Type::BOOL;
    mValue.bool_ = val;

    return *this;
}

AtomicValue& AtomicValue::operator=(double val)
{
    mStringValue = "";

    mType = Type::DOUBLE;
    mValue.double_ = val;

    return *this;
}

AtomicValue& AtomicValue::operator=(float val)
{
    mStringValue = "";

    mType = Type::FLOAT;
    mValue.float_ = val;

    return *this;
}

AtomicValue& AtomicValue::operator=(int16_t val)
{
    mStringValue = "";

    mType = Type::INT;
    mValue.int_ = val;

    return *this;
}

AtomicValue& AtomicValue::operator=(int32_t val)
{
    mStringValue = "";

    mType = Type::INT;
    mValue.int_ = val;

    return *this;
}

AtomicValue& AtomicValue::operator=(int64_t val)
{
    mStringValue = "";

    mType = Type::INT;
    mValue.int_ = val;

    return *this;
}

AtomicValue& AtomicValue::operator=(MemoryId val)
{
    mStringValue = "";

    mType = Type::REFERENCE;
    mValue.reference_ = val;

    return *this;
    }

AtomicValue& AtomicValue::operator=(const std::string& val)
{
    mValue.double_ = 0.0;

    mType = Type::STRING;
    mStringValue = val;

    return *this;
}

bool AtomicValue::toBool() const
{
    switch ( mType ) {
        case Type::BOOL:        return mValue.bool_;
        case Type::DOUBLE:      return mValue.double_ != 0.0;
        case Type::FLOAT:       return mValue.float_ != 0.f;
        case Type::INT:         return mValue.int_ != 0;
        case Type::REFERENCE:   return mValue.reference_ != 0;
        case Type::STRING:      return Utils::Tools::stringToBool( mStringValue );
        case Type::UNKNOWN:     break;
    }

    assert(!"invalid data type");
    return false;
}

double AtomicValue::toDouble() const
{
    switch ( mType ) {
        case Type::BOOL:        return static_cast<double>( mValue.bool_ );
        case Type::DOUBLE:      return mValue.double_;
        case Type::FLOAT:       return static_cast<double>( mValue.float_ );
        case Type::INT:         return static_cast<double>( mValue.int_ );
        case Type::REFERENCE:   return static_cast<double>( mValue.reference_ != 0 );
        case Type::STRING:      return Utils::Tools::stringToDouble( mStringValue );
        case Type::UNKNOWN:     break;
    }

    assert(!"invalid data type");
    return 0.0;
}

float AtomicValue::toFloat() const
{
    switch ( mType ) {
        case Type::BOOL:        return static_cast<float>( mValue.bool_ );
        case Type::DOUBLE:      return static_cast<float>( mValue.double_ );
        case Type::FLOAT:       return mValue.float_;
        case Type::INT:         return static_cast<float>( mValue.int_ );
        case Type::REFERENCE:   return static_cast<float>( mValue.reference_ != 0 );
        case Type::STRING:      return Utils::Tools::stringToFloat( mStringValue );
        default:                break;
    }

    assert(!"invalid data type");
    return 0.f;
}

int64_t AtomicValue::toInt() const
{
   switch ( mType ) {
      case Type::BOOL:        return static_cast<int64_t>( mValue.bool_ );
      case Type::DOUBLE:      return static_cast<int64_t>( mValue.double_ );
      case Type::FLOAT:       return static_cast<int64_t>( mValue.float_ );
      case Type::INT:         return mValue.int_;
      case Type::REFERENCE:   return static_cast<int64_t>( mValue.reference_ != 0 );
      case Type::STRING:      return Utils::Tools::stringToInt( mStringValue );
      case Type::UNKNOWN:     break;
   }

   assert(!"invalid data type");
   return 0;
}

MemoryId AtomicValue::toReference() const
{
    switch ( mType ) {
        case Type::REFERENCE:   return mValue.reference_;

        case Type::BOOL:
        case Type::DOUBLE:
        case Type::FLOAT:
        case Type::INT:
        case Type::STRING:      return static_cast<MemoryId>( -1 );	// invalidly typecast
        case Type::UNKNOWN:     break;
    }

    assert(!"invalid data type");
    return 0;
}

std::string AtomicValue::toStdString() const
{
    switch ( mType ) {
        case Type::BOOL:        return Utils::Tools::toString( mValue.bool_ );
        case Type::DOUBLE:      return Utils::Tools::toString( mValue.double_ );
        case Type::FLOAT:       return Utils::Tools::toString( mValue.float_ );
        case Type::INT:         return Utils::Tools::toString( mValue.int_ );
        case Type::REFERENCE:   return Utils::Tools::toString( mValue.reference_ );
        case Type::STRING:      return mStringValue;
        case Type::UNKNOWN:     break;
    }

    assert(!"invalid data type");
    return "";
}

AtomicValue::Type::E AtomicValue::type() const
{
    return mType;
}


}
}
