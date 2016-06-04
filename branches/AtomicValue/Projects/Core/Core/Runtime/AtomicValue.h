
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


struct AtomicValue
{
	enum {
		UNKOWN,
		BOOL,
		DOUBLE,
		FLOAT,
		INT,
		STRING
	} type;

	union ValueHolder {
		bool bool_;
		double double_;
		float float_;
		int int_;
		const char* string_;
	} value;

	AtomicValue();
	AtomicValue(bool val);
	AtomicValue(double val);
	AtomicValue(float val);
	AtomicValue(int val);
	AtomicValue(const char* val);

	void operator=(bool v);
	void operator=(double v);
	void operator=(float v);
	void operator=(int v);
	void operator=(const char* v);

	bool toBool() const;
	double toDouble() const;
	float toFloat() const;
	int toInt() const;
	const char* toString() const;
	std::string toStdString() const;
};


}
}


#endif
