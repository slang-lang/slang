
#ifndef Core_Runtime_AtomicValue_h
#define Core_Runtime_AtomicValue_h


// Library includes
#include <cassert>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class AtomicValue
{
public:
	class Type {
	public:
		enum E {
			UNKOWN,
			BOOL,
			DOUBLE,
			FLOAT,
			INT,
			OBJECT,
			STRING
		};
	};

public:	// Construction
	AtomicValue();
	AtomicValue(bool val);
	AtomicValue(double val);
	AtomicValue(float val);
	AtomicValue(int val);
	AtomicValue(const char* val);
	AtomicValue(const std::string& val);
	explicit AtomicValue(unsigned int val);

	~AtomicValue();

public:	// Assignment
	void operator=(bool val);
	void operator=(double val);
	void operator=(float val);
	void operator=(int val);
	void operator=(const char* val);
	void operator=(const std::string& val);
	void operator=(unsigned int val);

public:	// Conversion
	bool toBool() const;
	double toDouble() const;
	float toFloat() const;
	int toInt() const;
	unsigned int toObject() const;
	std::string toStdString() const;

	Type::E type() const;

private:
	union ValueHolder {
		bool bool_;
		double double_;
		float float_;
		int int_;
		unsigned int object_;
		//const char* string_;
	};

private:
	std::string mStringValue;
	Type::E mType;
	ValueHolder mValue;
};


}
}


#endif
