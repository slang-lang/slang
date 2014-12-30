
#ifndef ObjectiveScript_Parameter_h
#define ObjectiveScript_Parameter_h


// Library includes
#include <list>
#include <string>

// Project includes
#include <Core/Variable.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Parameter
{
public:
	class AccessMode
	{
	public:
		enum E {
			ByReference,
			ByValue
		};
	};

public:
	Parameter(const std::string& name, const std::string& type, const std::string& value, AccessMode::E access = AccessMode::ByValue)
	: mAccessMode(access),
	  mName(name),
	  mType(type),
	  mValue(value)
	{ }

	AccessMode::E access() const {
		return mAccessMode;
	}

	const std::string& name() const {
		return mName;
	}

	const std::string& type() const {
		return mType;
	}

	const std::string& value() const {
		return mValue;
	}

protected:

private:
	AccessMode::E mAccessMode;
	std::string mName;
	std::string mType;
	std::string mValue;
};


typedef std::list<Parameter> ParameterList;


}


#endif

