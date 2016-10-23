
#ifndef ObjectiveScript_Core_VirtualMachine_VirtualMethodTable_h
#define ObjectiveScript_Core_VirtualMachine_VirtualMethodTable_h


// Library includes
#include <map>
#include <set>

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
	void addMethod(const std::string& parent, Runtime::Method* method);

	Runtime::Method* lookup(const std::string& parent, const std::string& name, const ParameterList& params) const;

private:
	typedef std::set<Runtime::Method*> MethodCollection;
	typedef std::map<std::string /*parent*/, MethodCollection> MethodTable;

private:
	MethodTable mMethods;
};



}


#endif
