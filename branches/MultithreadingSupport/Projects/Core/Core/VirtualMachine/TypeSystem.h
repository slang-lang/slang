
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
private:
	class Right {
	public:
		bool contains(const std::string& right) const {
			return mRight.find(right) != mRight.end();
		}
		void insert(const std::string& right) {
			mRight.insert(
				std::make_pair(right, std::string())
			);
		}

		std::string& operator[](const std::string& index) {
			std::map<std::string, std::string>::iterator it = mRight.find(index);

			return it->second;
		}

		std::map</*right*/ std::string, /*result*/std::string> mRight;
	};

	class Operation {
	public:
		bool contains(Token::Type::E operation) const {
			return mOperation.find(operation) != mOperation.end();
		}
		void insert(Token::Type::E operation) {
			mOperation.insert(
				std::make_pair(operation, Right())
			);
		}

		Right& operator[](Token::Type::E index) {
			std::map<Token::Type::E, Right>::iterator it = mOperation.find(index);

			return it->second;
		}

		std::map</*operation*/ Token::Type::E, /*right*/ Right> mOperation;
	};

	class TypeMap {
	public:
		bool contains(const std::string& left) const {
			return mTypes.find(left) != mTypes.end();
		}
		void insert(const std::string& left) {
			mTypes.insert(
				std::make_pair(left, Operation())
			);
		}

		Operation& operator[](const std::string& index) {
			std::map<std::string, Operation>::iterator it = mTypes.find(index);

			return it->second;
		}

		std::map</*left*/ std::string, /*operation*/ Operation> mTypes;
	};

public:
	TypeSystem();
	~TypeSystem();

public:
	void deinit();
	void init();

public:
	void define(const std::string& left, Token::Type::E operation, const std::string& right, const std::string& result);
	bool exists(const std::string& left, Token::Type::E operation, const std::string& right);
	std::string getType(const std::string& left, const Token& operation, const std::string& right);

private:
	void initBool();
	void initDouble();
	void initFloat();
	void initInt();
	void initObject();
	void initString();

private:
	TypeMap mTypeMap;
};


}


#endif
