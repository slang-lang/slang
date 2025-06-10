
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
	virtual ~IContext() = default;

	virtual void write( const std::string& msg ) = 0;
};


class FileContext : public IContext
{
public:
	explicit FileContext( const std::string& file );
	~FileContext() override;

public:
	void write( const std::string& msg ) override;

private:
	std::ofstream mLogFile;
};


class StdOutContext : public IContext
{
public:
	void write( const std::string& msg ) override;
};


}
}


#endif
