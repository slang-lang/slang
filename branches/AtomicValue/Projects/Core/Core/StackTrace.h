
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
	~StackTrace();

public:
	void popStack();
	void print();
	void pushStack(const std::string& method, const ParameterList& params);

private:
	class Trace
	{
	public:
		std::string mMethod;
		ParameterList mParameters;
	};

	typedef std::list<Trace> Stack;

private:
	StackTrace();

	StackTrace(StackTrace const&)/* = delete*/;
	void operator=(StackTrace const&)/* = delete*/;

private:
	Stack mStack;
};


}


#endif
