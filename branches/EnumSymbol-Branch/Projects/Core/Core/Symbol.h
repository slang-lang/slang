
#ifndef ObjectiveScript_Symbol_h
#define ObjectiveScript_Symbol_h


// Library includes
#include <map>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Symbol
{
public:
	class IType
	{
	public:
		typedef enum {
			UnknownSymbol,
			BluePrintSymbol,
			EnumSymbol,
			MethodSymbol,
			NamespaceSymbol,
			ObjectSymbol
		} E;

        virtual ~IType() { }

		virtual const std::string& QualifiedTypename() const = 0;
		virtual const std::string& Typename() const = 0;
	};

public:
	Symbol(const std::string& name, IType::E type);
	virtual ~Symbol();

public:
	bool operator< (const Symbol& other) const;
	bool operator< (const Symbol* other) const;

public:
	const std::string& getName() const;
	IType::E getSymbolType() const;

	virtual std::string ToString() const = 0;

protected:
	std::string mName;
	IType::E mType;
};

typedef std::less<std::string> StringLess;

typedef std::map<std::string, Symbol*> Symbols;


class BluePrintSymbol : public Symbol,
						public Symbol::IType,
						public ObjectAttributes
{
public:
	BluePrintSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::BluePrintSymbol)
	{ }
	virtual ~BluePrintSymbol() { }
};

class EnumSymbol : public Symbol,
				   public Symbol::IType,
				   public GenericAttributes
{
public:
	EnumSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::EnumSymbol)
	{ }
	virtual ~EnumSymbol() { }
};

class MethodSymbol : public Symbol,
					 public Symbol::IType,
					 public MethodAttributes
{
public:
	MethodSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::MethodSymbol)
	{ }
	virtual ~MethodSymbol() { }
};

class NamespaceSymbol : public Symbol,
						public Symbol::IType,
						public NamespaceAttributes
{
public:
	NamespaceSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::NamespaceSymbol)
	{ }
	virtual ~NamespaceSymbol() { }
};

class ObjectSymbol : public Symbol,
					 public Symbol::IType,
					 public ObjectAttributes
{
public:
	ObjectSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::ObjectSymbol)
	{ }
	virtual ~ObjectSymbol() { }
};


}


#endif
