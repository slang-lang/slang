
#ifndef ObjectiveScript_Parameter_h
#define ObjectiveScript_Parameter_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Reference.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
class Object;

class Parameter
{
public:
	class AccessMode
	{
	public:
		enum E {
			Unspecified,
			ByReference,
			ByValue
		};
	};

public:
	Parameter();
	Parameter(const std::string& name, const std::string& type, const std::string& value, bool hasDefaultValue = false, bool isConst = false, AccessMode::E access = AccessMode::ByValue, Reference reference = Reference());

public:
	AccessMode::E access() const;
	bool hasDefaultValue() const;
	bool isConst() const;
	const std::string& name() const;
	const Reference& reference() const;
	const std::string& type() const;
	const std::string& value() const;

protected:

private:
	AccessMode::E mAccessMode;
	bool mHasDefaultValue;
	bool mIsConst;
	std::string mName;
	Reference mReference;
	std::string mType;
	std::string mValue;
};


typedef std::list<Parameter> ParameterList;


}


#endif

