
#ifndef ObjectiveScript_Core_Symbol_h
#define ObjectiveScript_Core_Symbol_h


// Library includes
#include <map>
#include <string>
//#include <unordered_map>

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
			UnknownSymbol,
			BluePrintEnumSymbol,
			BluePrintObjectSymbol,
			MethodSymbol,
			NamespaceSymbol,
			ObjectSymbol
		};

		virtual ~IType() { }

		virtual const std::string& QualifiedTypename() const = 0;
		virtual const std::string& Typename() const = 0;
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

typedef std::map<std::string, Symbol*> Symbols;
//typedef std::unordered_map<std::string, Symbol*> Symbols;


class BluePrintSymbol : public Symbol,
						public Symbol::IType,
						public ObjectAttributes
{
public:
	explicit BluePrintSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::BluePrintObjectSymbol)
	{ }
	virtual ~BluePrintSymbol() { }
};

class MethodSymbol : public Symbol,
					 public Symbol::IType,
					 public MethodAttributes
{
public:
	explicit MethodSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::MethodSymbol)
	{ }
	virtual ~MethodSymbol() { }
};

class NamespaceSymbol : public Symbol,
						public Symbol::IType,
						public NamespaceAttributes
{
public:
	explicit NamespaceSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::NamespaceSymbol)
	{ }
	virtual ~NamespaceSymbol() { }
};

class ObjectSymbol : public Symbol,
					 public Symbol::IType,
					 public ObjectAttributes
{
public:
	explicit ObjectSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::ObjectSymbol)
	{ }
	virtual ~ObjectSymbol() { }
};


}


#endif
