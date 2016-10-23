
// Header
#include "VirtualMethodTable.h"

// Library includes

// Project includes
#include <Core/Method.h>
#include <Common/Exceptions.h>

// Namespace declarations


namespace ObjectiveScript {


VirtualMethodTable::VirtualMethodTable()
{
}

VirtualMethodTable::~VirtualMethodTable()
{
	MethodTable tmpParents;
	for ( MethodTable::iterator parentIt = tmpParents.begin(); parentIt != tmpParents.end(); ++parentIt ) {
		MethodCollection tmpMethods = parentIt->second;

		for ( MethodCollection::iterator methodIt = tmpMethods.begin(); methodIt != tmpMethods.end(); ++methodIt ) {
			parentIt->second.erase(methodIt);

			delete (*methodIt);
		}

		mMethods.erase(parentIt->first);
	}
}

void VirtualMethodTable::addMethod(const std::string& parent, Runtime::Method* method)
{
	MethodTable::iterator parentIt = mMethods.find(parent);
	if ( parentIt == mMethods.end() ) {
		mMethods.insert(std::make_pair(parent, MethodCollection()));

		parentIt = mMethods.find(parent);
	}

	parentIt->second.insert(method);
}

Runtime::Method* VirtualMethodTable::lookup(const std::string& parent, const std::string& name, const ParameterList& params) const
{
	MethodTable::const_iterator parentIt = mMethods.find(parent);
	if ( parentIt != mMethods.end() ) {
		for ( MethodCollection::const_iterator methodIt = parentIt->second.begin(); methodIt != parentIt->second.end(); ++methodIt ) {
			Runtime::Method *method = (*methodIt);

			if ( method->getName() == name && method->isSignatureValid(params) ) {
				return method;
			}
		}
	}

	return 0;
}


}
