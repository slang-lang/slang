
// library imports
import System.String;

// project imports
import libs.Strings;


public object ShellCommand implements ICollection, IIterable
{
    public void Constructor( string cmd ) {
		Command     = cmd;
        TableResult = new Vector<Line>();
    }

    public int getExitCode() const {
        return ExitCode;
    }

	public string getOutput() const {
		return ShellOutput;
	}

	public string Run( string params = "", bool parseOutput = true ) modify
	{
		ShellOutput = system( streval( "{{{Command}}} {{{params}}} 2>&1" ) );
		ExitCode    = cast<int>( system( "echo $?" ) );

		if ( parseOutput ) {
			ParseOutput();
		}

		return ShellOutput;
	}

    // ICollection interface implementation
    // {
    public Line at( int index ) const {
        return TableResult.at( index );
    }

    public int size() const {
        return TableResult.size();
    }

    public Line operator[]( int index ) const {
        return TableResult.at( index );
    }
    // }

    // IIterable interface implementation
    // {
    public Iterator<Line> getIterator() const {
        return TableResult.getIterator();
    }
    // }

	private void ParseOutput() modify {
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

    protected string       Command;
    protected int          ExitCode;
	protected string       ShellOutput;
	protected Vector<Line> TableResult;
}

