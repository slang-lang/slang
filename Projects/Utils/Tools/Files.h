
#ifndef Utils_Tools_Files_h
#define Utils_Tools_Files_h


// Library includes
#include <string>
#include <vector>

// Project includes

// Forward declaration

// Namespace declarations


namespace Utils {
namespace Tools {
namespace Files {


bool exists(const std::string& filename);

std::string BuildPath(const std::string& baseFolder, const std::string& filename);
std::string ExtractFileExt(const std::string& filename);
std::string ExtractFilename(const std::string& filename);
std::string ExtractPathname(const std::string& pathname);
std::string GetFullname(const std::string& filename);
std::string RemoveFileExt(const std::string& filename);


}
}
}


#endif
