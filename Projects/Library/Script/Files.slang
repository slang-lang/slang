
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

    public ShellResult cat( string file, string params = "" )
    {
        return new ShellResult(
            system( streval( "cat {{{params}}} {{{file}}} 2>&1" ) ),
            EXIT_CODE,
            false
        );
    }

    public ShellResult cd( string directory, string params = "" )
    {
        return new ShellResult(
            system( streval( "cd {{{directory}}} {{{params}}} 2>&1" ) ),
            EXIT_CODE,
            false
        );
    }

    public ShellResult chmod( string mode, string file, string params = "" )
    {
        return new ShellResult(
            system( streval( "chmod {{{mode}}} {{{file}}} {{{params}}} 2>&1" ) ),
            EXIT_CODE,
            false
        );
    }

    public ShellResult chown( string owner, string group, string file, string params = "" )
    {
        return new ShellResult(
            system( streval( "chown {{{owner}}}:{{{group}}} {{{file}}} {{{params}}} 2>&1" ) ),
            EXIT_CODE,
            false
        );
    }

    public ShellResult df( string params = "" )
    {
        return new ShellResult(
            system( streval( "df {{{params}}} 2>&1" ) ),
            EXIT_CODE
        );
    }

    public ShellResult du( string params = "" )
    {
        return new ShellResult(
            system( streval( "du {{{params}}} 2>&1" ) ),
            EXIT_CODE
        );
    }

    public ShellResult file( string file, string params = "" )
    {
        return new ShellResult(
            system( streval( "file {{{params}}} {{{file}}} 2>&1" ) ),
            EXIT_CODE,
            false
        );
    }

    public ShellResult find( string params )
    {
        return new ShellResult(
            system( streval( "find {{{params}}} 2>&1" ) ),
            EXIT_CODE
        );
    }

    public ShellResult ls( string params = "" )
    {
        return new ShellResult(
            system( streval( "ls {{{params}}} 2>&1" ) ),
            EXIT_CODE
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
            EXIT_CODE
        );
    }

    public ShellResult mv( string source, string destination, string params = "" )
    {
        return new ShellResult(
            system( streval( "mv {{{source}}} {{{destination}}} {{{params}}} 2>&1" ) ),
            EXIT_CODE,
            false
        );
    }

    public ShellResult pwd( string params = "" )
    {
        return new ShellResult(
            system( streval( "pwd {{{params}}} 2>&1" ) ),
            EXIT_CODE,
            false
        );
    }

}
