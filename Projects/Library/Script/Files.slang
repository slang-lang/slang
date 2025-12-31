
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
