
#ifndef Slang_Core_Core_Symbol_h
#define Slang_Core_Core_Symbol_h


// Defines
#include <Core/Defines.h>

// Library includes
#include <map>
#include <set>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Common/Visibility.h>

// Forward declarations

// Namespace declarations


namespace Slang {


class Symbol
{
public:
	class IType
	{
	public:
		enum E {
			BluePrintObjectSymbol,
			MethodSymbol,
			NamespaceSymbol,
			ObjectSymbol
		};

		virtual ~IType() = default;

		virtual const std::string& QualifiedTypename() const = 0;
	};

public:
	Symbol(const std::string& name, IType::E type, Visibility::E visibility = Visibility::Public);
	virtual ~Symbol() = default;

public:
	bool operator==(const std::string& name) const;
	bool operator< (const Symbol& other) const;
	bool operator< (const Symbol* other) const;

	const std::string& getName() const;
	IType::E getSymbolType() const;

	Visibility::E getVisibility() const;
	void setVisibility(Visibility::E visibility);

public:
	virtual std::string ToString(unsigned int indent = 0) const = 0;

protected:
	std::string mName;
	IType::E mType;
	Visibility::E mVisibility;
};

typedef std::map<std::string, Symbol*> Symbols;


class BlueprintSymbol : public Symbol,
						public Symbol::IType,
						public ObjectAttributes
{
public:
	explicit BlueprintSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::BluePrintObjectSymbol)
	{
		mVisibility = Visibility::Private;
	}
};

class MethodSymbol : public Symbol,
					 public Symbol::IType,
					 public MethodAttributes
{
public:
	explicit MethodSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::MethodSymbol)
	{
		mVisibility = Visibility::Private;
	}
};

class NamespaceSymbol : public Symbol,
						public Symbol::IType,
						public NamespaceAttributes
{
public:
	explicit NamespaceSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::NamespaceSymbol)
	{
		mVisibility = Visibility::Private;
	}
};

class ObjectSymbol : public Symbol,
					 public Symbol::IType,
					 public ObjectAttributes
{
public:
	explicit ObjectSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::ObjectSymbol)
	{
		mVisibility = Visibility::Private;
	}
};


}


#endif
