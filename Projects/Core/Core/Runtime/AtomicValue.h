
#ifndef Core_Runtime_AtomicValue_h
#define Core_Runtime_AtomicValue_h


// Library includes
#include <cassert>
#include <string>

// Project includes
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Runtime {


class AtomicValue
{
public:
	class Type
	{
	public:
		enum E {
			UNKNOWN,
			BOOL,
			DOUBLE,
			FLOAT,
			INT,
			REFERENCE,
			STRING
		};
	};

public:	// Construction
	AtomicValue();
	AtomicValue( bool val );
	AtomicValue( double val );
	AtomicValue( float val );
	AtomicValue( int16_t val );
	AtomicValue( int32_t val );
	AtomicValue( int64_t val );
	explicit AtomicValue( MemoryId val );
	AtomicValue( std::string val );

	~AtomicValue() = default;

public:	// Assignment
	AtomicValue& operator=( bool val );
	AtomicValue& operator=( double val );
	AtomicValue& operator=( float val );
	AtomicValue& operator=( int16_t val );
	AtomicValue& operator=( int32_t val );
	AtomicValue& operator=( int64_t val );
	AtomicValue& operator=( MemoryId val );
	AtomicValue& operator=( const std::string& val );

public:	// Conversion
	bool toBool() const;
	double toDouble() const;
	float toFloat() const;
	int64_t toInt() const;
	MemoryId toReference() const;
	std::string toStdString() const;

	Type::E type() const;

private:
	union ValueHolder {
		bool bool_;
		double double_;
		float float_;
		int64_t int_;
		MemoryId reference_;
	};

private:
	std::string mStringValue;
	Type::E mType;
	ValueHolder mValue{};
};


}
}


#endif
