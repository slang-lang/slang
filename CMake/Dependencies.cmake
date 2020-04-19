
# make sure the user-settings file exists
SET(USER_ENV "$ENV{HOME}/.dev/slang")
INCLUDE(${USER_ENV} OPTIONAL RESULT_VARIABLE found)
if ( "${found}" STREQUAL "NOTFOUND" )
    MESSAGE(FATAL_ERROR "Your user-env file [${USER_ENV}] does not exist")
endif()

