
// Header
#include "FileOpen.h"

// Library includes
#include <fcntl.h>
#ifdef __APPLE__
#	include <unistd.h>
#elif defined _WIN32
#	include <sys/stat.h>
#	include <sys/types.h>
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
#endif

// Project includes
#include <Core/BuildInObjects/StringObject.h>
#include <Core/Designtime/BuildInTypes/IntegerObject.h>
#include <Core/Designtime/BuildInTypes/StringObject.h>
#include <Core/BuildInObjects/IntegerObject.h>
#include <Core/Repository.h>
#include <Core/Tools.h>
#include <Core/Common/Exceptions.h>
#include <Tools/Strings.h>

// Namespace declarations


namespace ObjectiveScript {
namespace Extensions {
namespace IO {


FileOpen::FileOpen()
: Runtime::Method(0, "fopen", Designtime::IntegerObject::TYPENAME)
{
	ParameterList params;
	params.push_back(Parameter("filename", Designtime::StringObject::TYPENAME, VALUE_NONE));
	params.push_back(Parameter("accessmode", Designtime::StringObject::TYPENAME, VALUE_NONE));

	setSignature(params);
}

Runtime::ControlFlow::E FileOpen::execute(const ParameterList& params, Runtime::Object* result, const Token& token)
{
	ParameterList list = mergeParameters(params);

	try {
		ParameterList::const_iterator it = list.begin();

		std::string param_filename = (*it++).value().toStdString();
		std::string param_accessmode = (*it++).value().toStdString();

		int mode = parseAccessMode(param_accessmode);
		int handle = open(param_filename.c_str(), mode, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

		if ( handle == -1 ) {
			return Runtime::ControlFlow::Throw;
		}

		*result = Runtime::IntegerObject(handle);
	}
	catch ( std::exception& e ) {
		Runtime::Object *data = mRepository->createInstance(Runtime::StringObject::TYPENAME, ANONYMOUS_OBJECT);
		*data = Runtime::StringObject(std::string(e.what()));

		mExceptionData = Runtime::ExceptionData(data, token.position());
		return Runtime::ControlFlow::Throw;
	}

	return Runtime::ControlFlow::Normal;
}

int FileOpen::parseAccessMode(std::string accessmode) const
{
	int mode = 0;

	while ( accessmode.size() > 0 ) {
		switch ( accessmode[0] ) {
			case 'a': mode |= O_APPEND; break;
			case 'c': mode |= O_CREAT; break;
			case 'r': mode |= O_RDONLY; break;
			case 't': mode |= O_TRUNC; break;
			case 'w': mode |= O_WRONLY; break;
			case 'x': mode |= O_EXCL; break;
			default: break;
		}

		accessmode = accessmode.substr(1, accessmode.size());
	}

	return mode;
}


}
}
}