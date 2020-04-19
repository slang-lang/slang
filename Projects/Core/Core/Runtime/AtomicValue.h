
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
	class Type {
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
	AtomicValue(bool val);
	AtomicValue(double val);
	AtomicValue(float val);
	AtomicValue(int val);
	explicit AtomicValue(MemoryId val);
	AtomicValue(const std::string& val);

	~AtomicValue();

public:	// Assignment
	void operator=(bool val);
	void operator=(double val);
	void operator=(float val);
	void operator=(int val);
	void operator=(MemoryId val);
	void operator=(const std::string& val);

public:	// Conversion
	bool toBool() const;
	double toDouble() const;
	float toFloat() const;
	int toInt() const;
	MemoryId toReference() const;
	std::string toStdString() const;

	Type::E type() const;

private:
	union ValueHolder {
		bool bool_;
		double double_;
		float float_;
		int int_;
		MemoryId reference_;
	};

private:
	std::string mStringValue;
	Type::E mType;
	ValueHolder mValue;
};


}
}


#endif
