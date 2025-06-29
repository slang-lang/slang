
#ifndef Slang_Core_Core_Common_Namespace_h
#define Slang_Core_Core_Common_Namespace_h


// Library includes
#include <string>

// Project includes
#include <Core/Scope.h>
#include <Core/Symbol.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Common {


class Namespace : public MethodScope,
				  public NamespaceSymbol
{
public:
	Namespace(const std::string& name, IScope* parent);
	~Namespace();

public: // MethodScope overrides
	void defineMethod(const std::string& name, Method* method);

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
