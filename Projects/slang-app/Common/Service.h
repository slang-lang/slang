
#ifndef Slang_slang_app_Service_h
#define Slang_slang_app_Service_h


// Library includes
#include <string>
#include <fcgiapp.h>

// Project includes

// Forward declarations
namespace Slang {
    class Script;
}

// Namespace declarations


class Service
{
public:
    Service( std::string path, std::string entryPoint, Slang::Script* script );
    ~Service() = default;

    const std::string& getPath() const {
        return mPath;
    }

public:
    bool handleRequest( const FCGX_Request& request );

private:
    void initialize();

private:
    std::string mEntryPoint;
    std::string mPath;
    Slang::Script* mScript{ nullptr };
};


#endif
