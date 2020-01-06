
// Header
#include "Files.h"

// Library includes
#include <cassert>
#include <fstream>
#include <limits.h>
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
	std::ifstream file( filename.c_str() );

	return file.good();
}


// Deprecated - begin
std::string _ExtractFileExt(const std::string& filename)
{
	if ( filename.empty() ) {
		return std::string();
	}

	unsigned long d = filename.length();
	while ( filename[d] != '.' && d > 0 ) {
		d--;
	}

	if ( d == 0 ) {
		return std::string();
	}

	d++;

	char buffer[255] = "";
#ifdef _MSC_VER
	sprintf_s(buffer, filename.length(), "%s", filename.c_str());
#else
	snprintf(buffer, filename.length(), "%s", filename.c_str());
#endif

	std::string result;

	for(unsigned long i = d, j = 0; i < filename.length(); i += 1, j += 1) {
		result += buffer[i];
	}

	result[filename.length() - d] = '\0';

	return std::string(result);
}

std::string _RemoveFileExt(const std::string& filename)
{
	if ( filename.empty() ) {
		return std::string();
	}

    unsigned long d = filename.length();
    while ( filename[d] != '.' && d > 0 ) {
	    d--;
    }

	if ( d == 0 ) {
	    return filename;
	}

    std::string buffer = filename;

    buffer[d] = '\0';

    return buffer;
}
// Deprecated - end



std::string BuildLibraryPath(const std::string& baseFolder, const std::string& library)
{
	return BuildPath(baseFolder, library) + ".os";
}

std::string BuildPath(const std::string& baseFolder, const std::string& filename)
{
	std::string result = filename;
	unsigned long npos;

	do {
		npos = result.find_first_of(".");
		if ( npos != std::string::npos ) {
			result[npos] = '/';
		}
	} while ( npos != std::string::npos );

	return GetFullname(baseFolder + result);
}

std::string ExtractFileExt(const std::string& filename)
{
	std::string tmp = filename.substr(filename.find_last_of(".") + 1);

	if ( tmp == filename ) {
		return "";
	}

	return tmp;
}

std::string ExtractFilename(const std::string& filename)
{
	if ( filename.empty() ) {
		return filename;
	}

	unsigned long d = filename.length();
	while ( (filename[d] != '\\' && d > 0) && ( filename[d] != '/' && d > 0) ) {
		d--;
	}

	if ( d == 0 ) {
		return filename;
	}

	d++;
	//int len = filename.length() - d;

	std::string result;

	for ( unsigned long i = d; i < filename.length(); i += 1 ) {
		result += filename[i];
	}

	return result;
}

std::string ExtractPathname(const std::string& pathname)
{
	if ( pathname.empty() ) {
		return pathname;
	}

	unsigned long d = pathname.length();
	while ( (pathname[d] != '\\' && pathname[d] != '/') && d > 0 ) {
		d--;
	}

	if ( d == 0 ) {
		return pathname;
	}

	d++;	// to get the (back)slash
	std::string result;

	for ( unsigned int i = 0; i < d; i += 1 ) {
		result += pathname[i];
	}

	return result;
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
		return std::string();
	}

	std::string ext = ExtractFileExt(filename);
	if ( ext.empty() ) {
	    return filename;
	}

    std::string buffer = filename;
	buffer.resize(filename.length() - ext.length() - 1);

    return buffer;
}
    
#ifdef _MSC_VER
#include <io.h>
#else
#include <glob.h>
    
	std::vector<std::string> globVector(const std::string& pattern)
	{
		glob_t glob_result;
        glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);

		std::vector<std::string> files;
		for ( unsigned int i = 0; i < glob_result.gl_pathc; ++i ) {
			files.push_back(
                std::string(glob_result.gl_pathv[i])
            );
		}
        
		globfree(&glob_result);
		return files;
	}

#endif


FileBrowser::FileBrowser(const std::string& path, const std::string& ext, bool findFolders)
{
	find(path, ext, findFolders);
}

std::string FileBrowser::activeFile()
{
	if ( mFiles.empty() || mFileIndex < 0 || mFileIndex > (int)mFiles.size() - 1 ) {
		return "";
	}

	return mFiles[mFileIndex];
}

void FileBrowser::find(const std::string& path, const std::string& ext, bool findFolders)
{
	reset();

#ifdef _MSC_VER
	struct _finddata_t file;
	long hFile;

	if ( findFolders ) {
		file.attrib &= _A_SUBDIR;
	}

	std::string findStr = path + "/*";
	if ( !ext.empty() ) {
		findStr += "." + ext;
	}

	/* Find first file in current directory */
	hFile = _findfirst(std::string(findStr).c_str(), &file);
	if ( hFile == -1L ) {
		hFile = _findfirst(std::string(findStr).c_str(), &file);

		if ( hFile == -1L ) {
			return;
		}
	}

	if ( _stricmp(file.name, ".") != 0 && _stricmp(file.name, "..") != 0 ) 
		mFiles.push_back(file.name);

	/* Find the rest of the files */
	while ( _findnext( hFile, &file ) == 0 ) {
		if ( _stricmp(file.name, ".") != 0 && _stricmp(file.name, "..") != 0 ) 
			mFiles.push_back(file.name);
	}

	_findclose( hFile );

#else
	mFiles = globVector(path + "/*" + ext);
    (void)findFolders;
#endif

	mFileIndex = -1;
}

std::string FileBrowser::nextFile()
{
	if ( mFileIndex > (int)mFiles.size() - 1 ) {
		mFileIndex = -1;
	}

	mFileIndex++;

	return activeFile();
}

std::string FileBrowser::previousFile()
{
	if ( mFileIndex < 0 ) {
		mFileIndex = (int)mFiles.size();
	}

	mFileIndex--;

	return activeFile();
}

void FileBrowser::reset()
{
	mFiles.clear();
	mFileIndex = -1;
}


}
}
}
