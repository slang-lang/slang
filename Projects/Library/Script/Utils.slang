
// Library imports
import System.IO.File;

// Project imports
import CoreUtils.ShellResult;


public namespace Utils
{
    public ShellResult free( string params = "" )
    {
        return new ShellResult(
            system( streval( "free {{{params}}} 2>&1" ) ),
            cast<int>( system( "echo $?" ) )
        );
    }

    public ShellResult ps( string params = "" )
    {
        return new ShellResult(
            system( streval( "ps {{{params}}} 2>&1" ) ),
            cast<int>( system( "echo $?" ) )
        );
    }

    public ShellResult uptime( string params = "" )
    {
        return new ShellResult(
            system( streval( "uptime {{{params}}} 2>&1" ) ),
            cast<int>( system( "echo $?" ) )
        );
    }
}

