
#ifndef Core_Runtime_AtomicValue_h
#define Core_Runtime_AtomicValue_h


// Library includes
#include <cassert>
#include <string>

// Project includes
//#include <Core/Tools.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class AtomicValue
{
public:
	enum {
		UNKOWN,
		BOOL,
		DOUBLE,
		FLOAT,
		INT,
		STRING
	} type;

public:	// Construction
	AtomicValue();
	AtomicValue(bool val);
	AtomicValue(double val);
	AtomicValue(float val);
	AtomicValue(int val);
	//AtomicValue(const char* val);
	AtomicValue(const std::string& val);

	~AtomicValue();

public:	// Assignment
	void operator=(bool val);
	void operator=(double val);
	void operator=(float val);
	void operator=(int val);
	//void operator=(const char* val);
	void operator=(const std::string& val);

public:	// Conversion
	bool toBool() const;
	double toDouble() const;
	float toFloat() const;
	int toInt() const;
	//const char* toString() const;
	std::string toStdString() const;

private:
	union ValueHolder {
		bool bool_;
		double double_;
		float float_;
		int int_;
		//const char* string_;
	};

private:
	std::string mStringValue;
	ValueHolder mValue;
};


}
}


#endif
