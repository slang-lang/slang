
#ifndef ObjectiveScript_Core_Symbol_h
#define ObjectiveScript_Core_Symbol_h


// Defines
#include <Core/Defines.h>

// Library includes
#ifdef USE_ORDERED_COLLECTION
#	include <map>
#	include <set>
#else
#	include <unordered_map>
#	include <unordered_set>
#endif
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>
#include <Core/Common/Visibility.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Symbol
{
public:
	class IType
	{
	public:
		enum E {
			BluePrintEnumSymbol,
			BluePrintObjectSymbol,
			MethodSymbol,
			NamespaceSymbol,
			ObjectSymbol
		};

		virtual ~IType() { }

		virtual const std::string& QualifiedTypename() const = 0;
	};

public:
	Symbol(const std::string& name, IType::E type, Visibility::E visibility = Visibility::Public);
	virtual ~Symbol();

public:
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

#ifdef USE_ORDERED_COLLECTION
	typedef std::map<std::string, Symbol*> Symbols;
#else
	typedef std::unordered_map<std::string, Symbol*> Symbols;
#endif


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
	virtual ~BlueprintSymbol() { }
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
	virtual ~MethodSymbol() { }
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
	virtual ~NamespaceSymbol() { }
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
	virtual ~ObjectSymbol() { }
};


}


#endif