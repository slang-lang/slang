
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
			BuildInTypeSymbol,
			MemberSymbol,
			MethodSymbol,
			ObjectSymbol
		} E;

        virtual ~IType() { }

		virtual const std::string& getTypeName() const = 0;
	};

public:
	Symbol(const std::string& name, IType::E type)
	: mName(name),
	  mType(type)
	{ }
	virtual ~Symbol() { }

public:
	bool operator< (const Symbol& other) const {
		return getName() < other.getName();
	}
	bool operator< (const Symbol* other) const {
		return getName() < other->getName();
	}

public:
	const std::string& getName() const {
		return mName;
	}
	IType::E getType() const {
		return mType;
	}

protected:

private:
	std::string mName;
	IType::E mType;
};

typedef std::less<std::string> StringLess;

typedef std::map<std::string, Symbol*> Symbols;


class BuildInTypeSymbol : public Symbol,
						  public Symbol::IType,
						  public ObjectAttributes
{
public:
    BuildInTypeSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::BuildInTypeSymbol)
	{ }
	virtual ~BuildInTypeSymbol() { }
};

class MemberSymbol : public Symbol,
					 public Symbol::IType,
					 public ObjectAttributes
{
public:
	MemberSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::MemberSymbol)
	{ }
	virtual ~MemberSymbol() { }
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

class ObjectSymbol : public Symbol,
					 public Symbol::IType
					 //public ObjectAttributes
{
public:
	ObjectSymbol(const std::string& name)
	: Symbol(name, Symbol::IType::ObjectSymbol)
	{ }
	virtual ~ObjectSymbol() { }
};


}


#endif
