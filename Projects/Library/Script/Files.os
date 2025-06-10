
import System.IO.File;


public namespace Script {

    public bool IfExists( string filename ) const {
       return System.IO.File.Exists( filename );
    }

}
