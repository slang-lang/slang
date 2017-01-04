
#ifndef Core_Runtime_Namespace_h
#define Core_Runtime_Namespace_h


// Library includes
#include <string>

// Project includes
#include <Core/Scope.h>
#include <Core/Symbol.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {
namespace Runtime {


class Namespace : public MethodScope,
				  public NamespaceSymbol
{
public:
	Namespace(const std::string& name, IScope* parent);
	~Namespace();

public:	// Symbol::IType implementation
	const std::string& Filename() const { return mFilename; }
	const std::string& QualifiedTypename() const { return mQualifiedTypename; }
	const std::string& Typename() const { return mTypename; }

	void setQualifiedTypename(const std::string& type) { mQualifiedTypename = type; }

public:
	std::string ToString(unsigned int indent = 0) const;

private:
	std::string mFilename;
	std::string mQualifiedTypename;
	std::string mTypename;
};


}
}


#endif
