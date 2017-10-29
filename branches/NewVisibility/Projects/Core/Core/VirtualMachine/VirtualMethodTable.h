
#ifndef ObjectiveScript_Core_VirtualMachine_VirtualMethodTable_h
#define ObjectiveScript_Core_VirtualMachine_VirtualMethodTable_h


// Defines
#include <Core/Defines.h>

// Library includes
#include <list>
#ifdef USE_ORDERED_COLLECTION
#	include <map>
#else
#	include<unordered_map>
#endif

// Project includes
#include <Core/Parameter.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Common {
	class Method;
}

class VirtualMethodTable
{
public:
	VirtualMethodTable();
	~VirtualMethodTable();

public:
	void addMethod(const std::string& currentObject, Common::Method* method, const std::string& parentObject);

	Common::Method* lookup(const std::string& parent, const std::string& name, const ParameterList& params) const;

private:
	class MethodAndParent
	{
	public:
		MethodAndParent(Common::Method* method, const std::string& parent)
		: mMethod(method),
		  mParent(parent)
		{ }

		Common::Method* mMethod;
		std::string mParent;
	};

	typedef std::list<MethodAndParent> MethodCollection;
#ifdef USE_ORDERED_COLLECTION
	typedef std::map<std::string /*parent*/, MethodCollection> MethodTable;
#else
	typedef std::unordered_map<std::string /*parent*/, MethodCollection> MethodTable;
#endif

private:
	MethodTable mMethods;
};



}


#endif
