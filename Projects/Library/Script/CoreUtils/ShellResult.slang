
// library imports
import System.String;

// project imports
import libs.Strings;


public object ShellResult const implements ICollection, IIterable
{
    public void Constructor( string shellOutput, int exitCode, bool parsing = true )
    {
        ExitCode    = exitCode;
        ShellOutput = shellOutput;
        TableResult = new Vector<Line>();

        if ( parsing ) {
            var str = new String( ShellOutput );

            foreach ( string line : str.SplitBy( LINEBREAK ) ) {
                if ( !line ) {
                    continue;
                }

                var tok = new String( line );

                var row = new Line();
                foreach ( string token : tok.SplitBy( " " ) ) {
                    if ( token ) {
                        row.push_back( token );
                    }
                }

                TableResult.push_back( row );
            }
        }
    }

    // ShellResult interface implementation
    // {
    public int getExitCode() const
    {
        return ExitCode;
    }

    public string getOutput() const
    {
        return ShellOutput;
    }

    public int =operator( int ) const
    {
        return ExitCode;
    }

    public string =operator( string ) const
    {
        return ShellOutput;
    }
    // }

    // ICollection interface implementation
    // {
    public Line at( int index ) const
    {
        return TableResult.at( index );
    }

    public int size() const
    {
        return TableResult.size();
    }

    public Line operator[]( int index ) const
    {
        return TableResult.at( index );
    }
    // }

    // IIterable interface implementation
    // {
    public Iterator<Line> getIterator() const
    {
        return TableResult.getIterator();
    }
    // }

    private int          ExitCode const;
    private string       ShellOutput const;
    private Vector<Line> TableResult const;
}

