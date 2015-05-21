
#ifndef ObjectiveScript_Parameter_h
#define ObjectiveScript_Parameter_h


// Library includes
#include <list>
#include <string>

// Project includes

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
	Parameter(const std::string& name, const std::string& type, const std::string& value, bool isConst = false, AccessMode::E access = AccessMode::ByValue, Object* reference = 0);

public:
	AccessMode::E access() const;
	bool isConst() const;
	const std::string& name() const;
	Object* reference() const;
	const std::string& type() const;
	const std::string& value() const;

protected:

private:
	AccessMode::E mAccessMode;
	bool mIsConst;
	std::string mName;
	Object* mReference;
	std::string mType;
	std::string mValue;
};


typedef std::list<Parameter> ParameterList;


}


#endif

