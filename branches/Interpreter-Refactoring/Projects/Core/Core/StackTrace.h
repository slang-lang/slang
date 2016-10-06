
#ifndef ObjectiveScript_Core_Stacktrace_h
#define ObjectiveScript_Core_Stacktrace_h


// Library includes
#include <list>
#include <string>

// Project includes
#include "Types.h"

// Forward declarations

// Namespace declarations


namespace ObjectiveScript {


class StackTrace
{
// Singleton
// {
public:
	static StackTrace& GetInstance();
// }

public:
	class StackLevel
	{
	public:
		StackLevel();
		StackLevel(const unsigned long level, const std::string& method, const ParameterList& params);

	public:
		std::string toString() const;

	public:
		const unsigned long mLevel;
		const std::string mMethod;
		const ParameterList mParameters;

	private:
		void operator=(const StackLevel&)/* = delete*/;
	};

	typedef std::list<StackLevel> Stack;

public:
	~StackTrace();

public:
	void clear();
	StackLevel currentStackLevel() const;
	const Stack& getStack() const;
	void popStack();
	void print();
	void pushStack(const std::string& method, const ParameterList& params);

private:
	StackTrace();

	StackTrace(StackTrace const&)/* = delete*/;
	void operator=(StackTrace const&)/* = delete*/;

private:
	Stack mStack;
};


}


#endif
