
#ifndef Slang_Extensions_LIBC_stdio_stdio_hpp
#define Slang_Extensions_LIBC_stdio_stdio_hpp


// Library includes
#include <fcntl.h>
#include <sys/stat.h>
#ifdef __APPLE__
//#	include <unistd.h>
#elif defined _WIN32
#	include <io.h>
#	pragma warning(disable:4996)

	typedef int mode_t;

	static const mode_t S_ISUID      = 0x08000000;           ///< does nothing
	static const mode_t S_ISGID      = 0x04000000;           ///< does nothing
	static const mode_t S_ISVTX      = 0x02000000;           ///< does nothing
	static const mode_t S_IRUSR      = mode_t(_S_IREAD);     ///< read by user
	static const mode_t S_IWUSR      = mode_t(_S_IWRITE);    ///< write by user
	static const mode_t S_IXUSR      = 0x00400000;           ///< does nothing
#   ifndef STRICT_UGO_PERMISSIONS
	static const mode_t S_IRGRP      = mode_t(_S_IREAD);     ///< read by *USER*
	static const mode_t S_IWGRP      = mode_t(_S_IWRITE);    ///< write by *USER*
	static const mode_t S_IXGRP      = 0x00080000;           ///< does nothing
	static const mode_t S_IROTH      = mode_t(_S_IREAD);     ///< read by *USER*
	static const mode_t S_IWOTH      = mode_t(_S_IWRITE);    ///< write by *USER*
	static const mode_t S_IXOTH      = 0x00010000;           ///< does nothing
#   else
	static const mode_t S_IRGRP      = 0x00200000;           ///< does nothing
	static const mode_t S_IWGRP      = 0x00100000;           ///< does nothing
	static const mode_t S_IXGRP      = 0x00080000;           ///< does nothing
	static const mode_t S_IROTH      = 0x00040000;           ///< does nothing
	static const mode_t S_IWOTH      = 0x00020000;           ///< does nothing
	static const mode_t S_IXOTH      = 0x00010000;           ///< does nothing
#	endif
#else
#	include <cstring>
#endif
#include <map>

// Project includes
#include <Core/Extensions/AExtension.h>

// Forward declarations

// Namespace declarations


namespace Slang {
namespace Extensions {
namespace LIBC {
namespace stdio {


class stdio_t : public AExtension
{
public:
    typedef std::map<int /*file handle*/, FILE*> FileHandles_t;

    static FileHandles_t FileHandles;

public:
	stdio_t();
	~stdio_t() = default;

public:
	void initialize( ExtensionNamespace* scope );
	void provideMethods( ExtensionMethods& methods );
};


}
}
}
}


#endif
