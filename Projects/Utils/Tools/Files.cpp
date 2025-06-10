// Header
#include "Files.h"

// Library includes
#include <cassert>
#include <climits>
#include <fstream>
#ifdef _MSC_VER
#	include <windows.h>
#	include <tchar.h>
#	include <stdio.h>
#endif

// Project includes

// Namespace declarations


namespace Utils {
namespace Tools {
namespace Files {


bool exists(const std::string& filename)
{
#if defined(__cplusplus) && __cplusplus >= 201703L
    // Use modern std::filesystem if available (C++17 and later)
    try {
        return std::filesystem::exists( filename );
    }
    catch ( const std::filesystem::filesystem_error& ) {
        return false;
    }
#else
    // Fallback to traditional file check for older C++ versions
    std::ifstream file( filename );

    return file.is_open() && file.good();
#endif
}

std::string BuildPath(const std::string& baseFolder, const std::string& filename)
{
	std::string result = filename;
	unsigned long npos;

	do {
		npos = result.find_first_of('.');
		if ( npos != std::string::npos ) {
			result[npos] = '/';
		}
	} while ( npos != std::string::npos );

	return GetFullname(baseFolder + result);
}

std::string ExtractFileExt(const std::string& filename)
{
    if ( filename.empty() ) {
        return "";
    }

    auto separatorPos = filename.find_last_of( '.' );
    if ( separatorPos == std::string::npos ) {
        return "";
    }

    return filename.substr( separatorPos + 1 );
}

std::string ExtractFilename(const std::string& filename)
{
    if ( filename.empty() ) {
        return filename;
    }

    auto lastSeparatorPos = filename.find_last_of(  "\\/" );
    if ( lastSeparatorPos == std::string::npos ) {
        return filename;
    }

    return filename.substr( lastSeparatorPos + 1 );
}

std::string ExtractPathname(const std::string& pathname)
{
    if ( pathname.empty() ) {
        return pathname;
    }

    auto lastSeparatorPos = pathname.find_last_of( "\\/" );
    if ( lastSeparatorPos == std::string::npos ) {
        return pathname;
    }

    return pathname.substr( 0, lastSeparatorPos + 1 );
}

std::string GetFullname(const std::string& filename)
{
#ifdef _MSC_VER
#define PATH_MAX 1024

	char full_path[PATH_MAX];
	GetFullPathName(filename.c_str(), PATH_MAX, full_path, 0);

	return std::string(full_path);

#else

	char full_path[PATH_MAX];
	char* result = realpath(filename.c_str(), full_path);
	(void)result;

	return std::string(full_path);

#endif
}

std::string RemoveFileExt(const std::string& filename)
{
    if ( filename.empty() ) {
        return "";
    }

    auto fileExtension = ExtractFileExt( filename );
    if ( fileExtension.empty() ) {
        return filename;
    }

    return filename.substr( 0, filename.length() - fileExtension.length() - 1 );
}

#ifdef _MSC_VER
#include <io.h>
#else
#include <glob.h>

	std::vector<std::string> globVector(const std::string& pattern)
	{
		glob_t glob_result;
		glob(pattern.c_str(), GLOB_TILDE, nullptr, &glob_result);

		std::vector<std::string> files;
		for ( unsigned int i = 0; i < glob_result.gl_pathc; ++i ) {
			files.emplace_back(glob_result.gl_pathv[i]);
		}

		globfree(&glob_result);
		return files;
	}

#endif


}
}
}