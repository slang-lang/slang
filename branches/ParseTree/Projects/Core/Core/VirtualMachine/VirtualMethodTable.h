
#ifndef ObjectiveScript_Core_VirtualMachine_VirtualMethodTable_h
#define ObjectiveScript_Core_VirtualMachine_VirtualMethodTable_h


// Library includes
#include <list>
#include <map>
//#include <unordered_map>

// Project includes
#include <Core/Parameter.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {

// Forward declarations
namespace Runtime {
	class Method;
}

class VirtualMethodTable
{
public:
	VirtualMethodTable();
	~VirtualMethodTable();

public:
	void addMethod(const std::string& currentObject, Runtime::Method* method, const std::string& parentObject);

	Runtime::Method* lookup(const std::string& parent, const std::string& name, const ParameterList& params) const;

private:
	class MethodAndParent
	{
	public:
		MethodAndParent(Runtime::Method* method, const std::string& parent)
		: mMethod(method),
		  mParent(parent)
		{ }

		Runtime::Method* mMethod;
		std::string mParent;
	};

	typedef std::list<MethodAndParent> MethodCollection;
	typedef std::map<std::string /*parent*/, MethodCollection> MethodTable;
	//typedef std::unordered_map<std::string /*parent*/, MethodCollection> MethodTable;

private:
	MethodTable mMethods;
};



}


#endif
