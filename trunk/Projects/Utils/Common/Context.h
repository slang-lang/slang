
#ifndef Utils_Common_Context_h
#define Utils_Common_Context_h


// Library includes
#include <iostream>
#include <fstream>

// Project includes

// Forward declarations

// Namespace declarations


namespace Utils {
namespace Common {


class IContext
{
public:
	virtual ~IContext() { }

public:
	virtual void write(const char* msg) = 0;
};


class Context : public IContext
{
public:
	Context(const char* file);
	~Context();

public:
	void write(const char* msg);

protected:

private:
	std::ofstream	mLogFile;
};


class StdOutContext : public IContext
{
public:
	void write(const char* msg);

protected:

private:

};


}
}


#endif
