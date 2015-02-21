
#ifndef ObjectiveScript_Variable_h
#define ObjectiveScript_Variable_h


// Library includes
#include <cassert>
#include <list>
#include <string>

// Project includes
#include <Core/Attributes/Attributes.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class Variable : public Attributes
{
public:
/*
	class BaseType
	{
	public:
		enum E {
			Bool,
			Float,
			Int,
			Number,
			Object,
			String,
			Void
		};

		static E convert(const std::string& t) {
			if ( t == "bool" ) { return Bool; }
			else if ( t == "float" ) { return Float; }
			else if ( t == "int" ) { return Int; }
			else if ( t == "number" ) { return Number; }
			else if ( t == "object" ) { return Object; }
			else if ( t == "string" ) { return String; }
			else if ( t == "void" ) { return Void; }

			//assert(!"invalid type!");
			return Object;
		}

		static std::string convert(E t) {
			switch ( t ) {
				case Bool: return "bool";
				case Float: return "float";
				case Int: return "int";
				case Number: return "number";
				case Object: return "object";
				case String: return "string";
				case Void: return "void";
			}

			//assert(!"invalid type!");
			return "object";
		}
	};
*/

public:
	Variable();
	Variable(const std::string& name, const std::string& type);
	Variable(const std::string& name, const std::string& type, const std::string& value);
	virtual ~Variable();

public:
	const std::string& name() const;

	const std::string& type() const;

	const std::string& value() const;
	void value(const std::string& value);

public:
	bool operator==(const Variable& other);
	bool operator()();

protected:
	std::string mName;
	std::string mType;
	std::string mValue;

private:

};

typedef std::list<Variable> VariablesList;


}


#endif
