
#ifndef ObjectiveScript_Symbol_h
#define ObjectiveScript_Symbol_h


// Library includes
#include <map>
#include <string>

// Project includes

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Symbol
{
public:
	class IType
	{
	public:
		virtual const std::string& getName() const = 0;
	};

public:
	Symbol(const std::string& name, IType *type)
	: mName(name),
	  mType(type)
	{ }
	virtual ~Symbol() { }

public:
	bool operator < (const Symbol& other) const {
		return getName() < other.getName();
	}
	bool operator < (const Symbol* other) const {
		return getName() < other->getName();
	}

	const std::string& getName() const {
		return mName;
	}
	IType* getType() const {
		return mType;
	}

protected:

private:
	std::string mName;
	IType *mType;
};

typedef std::less<std::string> StringLess; 

typedef std::map<std::string, Symbol*> Symbols;


class BuildInTypeSymbol : public Symbol,
						  public Symbol::IType
{
public:
	BuildInTypeSymbol(const std::string& name, IType *type)
	: Symbol(name, type)
	{ }
	virtual ~BuildInTypeSymbol() { }
};

class ClassSymbol : public Symbol,
					public Symbol::IType
{
public:
	ClassSymbol(const std::string& name, IType *type)
	: Symbol(name, type)
	{ }
	virtual ~ClassSymbol() { }
};

class MemberSymbol : public Symbol,
					 public Symbol::IType
{
public:
	MemberSymbol(const std::string& name, IType *type)
	: Symbol(name, type)
	{ }
	virtual ~MemberSymbol() { }
};

class MethodSymbol : public Symbol,
					 public Symbol::IType
{
public:
	MethodSymbol(const std::string& name, IType *type)
	: Symbol(name, type)
	{ }
	virtual ~MethodSymbol() { }
};


}


#endif
