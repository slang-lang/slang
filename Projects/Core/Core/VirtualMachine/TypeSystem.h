
#ifndef ObjectiveScript_Core_VirtualMachine_TypeSystem_h
#define ObjectiveScript_Core_VirtualMachine_TypeSystem_h


// Library includes
#include <map>
#include <string>

// Project includes
#include <Core/Designtime/Parser/Token.h>

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class TypeSystem
{
public:
	TypeSystem();
	~TypeSystem();

public:
	void deinit();
	void init();

public:
	void define(const std::string& left, Token::Type::E operation, const std::string& right, const std::string& result);

	std::string getType(const std::string& left, Token::Type::E operation, const std::string& right) const;

private:
	typedef std::map</*left*/ std::string,
			         std::map</*operation*/ Token::Type,
							  std::map</*right*/ std::string, /*result*/ std::string>>> TypeMap;

private:
	TypeMap mTypeMap;
};


}


#endif
