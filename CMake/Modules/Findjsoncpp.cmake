# - Try to find JSON
# Once done, this will define
#
#  JSON_FOUND - system has JSON
#  JSON_INCLUDE_DIRS - the JSON include directories
#  JSON_LIBRARIES - link these to use JSON

include(LibFindMacros)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(JSON_PKGCONF jsoncpp)

# Include dir
find_path(
    JSON_INCLUDE_DIR
    NAMES json/features.h
    PATH_SUFFIXES jsoncpp
    PATHS ${JSON_PKGCONF_INCLUDE_DIRS} # /usr/include/jsoncpp/json
)

# Finally the library itself
find_library(
    JSON_LIBRARY
    NAMES jsoncpp
    PATHS ${JSON_PKGCONF_LIBRARY_DIRS} #  PATH ./jsoncpp/
)

set(JSON_PROCESS_INCLUDES JSON_INCLUDE_DIR)
set(JSON_PROCESS_LIBS JSON_LIBRARY)
libfind_process(JSON)
