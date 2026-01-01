
// Library imports
import System.IO.File;

// Project imports
import CoreUtils.ShellResult;


public namespace Files
{

    public bool fileExists( string filename ) const
    {
        return System.IO.File.Exists( filename );
    }

    public ShellResult cat( string params = "" )
    {
        return new ShellResult(
            system( streval( "cat {{{params}}} 2>&1" ) ),
            cast<int>( system( "echo $?" ) ),
            false
        );
    }

    public ShellResult df( string params = "" )
    {
        return new ShellResult(
            system( streval( "df {{{params}}} 2>&1" ) ),
            cast<int>( system( "echo $?" ) )
        );
    }

    public ShellResult du( string params = "" )
    {
        return new ShellResult(
            system( streval( "du {{{params}}} 2>&1" ) ),
            cast<int>( system( "echo $?" ) )
        );
    }

    public ShellResult ls( string params = "" )
    {
        return new ShellResult(
            system( streval( "ls {{{params}}} 2>&1" ) ),
            cast<int>( system( "echo $?" ) )
        );
    }

    public ShellResult mkdir( string directory, bool ignoreParents = false, int mode = 0 )
    {
        string params;

        if ( mode ) {
            params += streval( " -m {{{mode}}} " );
        }
        if ( ignoreParents ) {
            params += " -p ";
        }

        return new ShellResult(
            system( streval( "mkdir {{{params}}} {{{directory}}} 2>&1" ) ),
            cast<int>( system( "echo $?" ) )
        );
    }

}
