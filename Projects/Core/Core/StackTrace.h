
#ifndef ObjectiveScript_Stacktrace_h
#define ObjectiveScript_Stacktrace_h


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
		StackLevel(const std::string& method, const ParameterList& params);

	public:
		std::string toString() const;

	public:
		const std::string mMethod;
		const ParameterList mParameters;

	private:
		void operator=(const StackLevel&)/* = delete*/;
	};

public:
	~StackTrace();

public:
	void clear();
	StackLevel currentStackLevel() const;
	void popStack();
	void print();
	void pushStack(const std::string& method, const ParameterList& params);

private:
	typedef std::list<StackLevel> Stack;

private:
	StackTrace();

	StackTrace(StackTrace const&)/* = delete*/;
	void operator=(StackTrace const&)/* = delete*/;

private:
	Stack mStack;
};


}


#endif
