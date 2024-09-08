
# make sure the user-settings file exists
set( USER_ENV "$ENV{HOME}/.dev/slang" )
include( ${USER_ENV} OPTIONAL RESULT_VARIABLE found )
if ( "${found}" STREQUAL "NOTFOUND" )
    message( FATAL_ERROR "Your user-env file [${USER_ENV}] does not exist" )
endif()

