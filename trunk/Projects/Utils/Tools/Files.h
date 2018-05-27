
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

std::string BuildLibraryPath(const std::string& baseFolder, const std::string& library);
std::string BuildPath(const std::string& baseFolder, const std::string& filename);
std::string _ExtractFileExt(const std::string& filename);
std::string ExtractFileExt(const std::string& filename);
std::string ExtractFilename(const std::string& filename);
std::string ExtractPathname(const std::string& pathname);
std::string GetFullname(const std::string& filename);
std::string _RemoveFileExt(const std::string& filename);
std::string RemoveFileExt(const std::string& filename);

class FileBrowser
{
public:
	FileBrowser(const std::string& path, const std::string& ext, bool findFolders = false);

public:
	void find(const std::string& path, const std::string& ext, bool findFolders = false);
	void reset();

	std::string activeFile();
	std::string nextFile();
	std::string previousFile();

private:
	typedef std::vector<std::string> StringVector;

private:
	int mFileIndex;
	StringVector mFiles;
};


}
}
}


#endif
