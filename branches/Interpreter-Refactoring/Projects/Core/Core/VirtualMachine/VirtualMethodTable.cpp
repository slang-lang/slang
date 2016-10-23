
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
		}

		mMethods.erase(parentIt->first);
	}
}

void VirtualMethodTable::addMethod(const std::string& currentObject, Runtime::Method* method, const std::string& parentObject)
{
	MethodTable::iterator ownerIt = mMethods.find(currentObject);
	if ( ownerIt == mMethods.end() ) {
		mMethods.insert(std::make_pair(currentObject, MethodCollection()));

		ownerIt = mMethods.find(currentObject);
	}

	ownerIt->second.push_back(MethodAndParent(method, parentObject));
}

Runtime::Method* VirtualMethodTable::lookup(const std::string& parent, const std::string& name, const ParameterList& params) const
{
	MethodTable::const_iterator ownerIt = mMethods.find(parent);
	if ( ownerIt != mMethods.end() ) {
		MethodCollection owner = ownerIt->second;

		for ( MethodCollection::const_iterator methodIt = owner.begin(); methodIt != owner.end(); ++methodIt ) {
			MethodAndParent mp = (*methodIt);

			if ( mp.mMethod->getName() == name && mp.mMethod->isSignatureValid(params) ) {
				Runtime::Method* tmp = lookup(mp.mParent, name, params);
				if ( tmp && tmp->isFinal() ) {
					return tmp;
				}

				return mp.mMethod;
			}
		}
	}

	return 0;
}


}
