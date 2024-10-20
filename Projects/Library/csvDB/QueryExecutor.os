
// library imports
import libCSVReader;
import libCSVReader.Row;
import System.Collections.Map;
import System.Collections.Vector;

// project imports
import Expressions;
import Tokenizer;


private string expandTableName( string table ) const {
    if ( strfind( table, ".csv" ) == -1 ) {
        table += ".csv";
    }

    return table;
}

public object ParseException const implements IException {
	public void Constructor(string msg, Position position const) {
		mMessage = msg;
		mPosition = position;
	}

	public string what() const {
		return mMessage + (mPosition ? " at " + string mPosition : "");
	}

	private string mMessage const;
	private Position mPosition const;
}


public object QueryExecutor
{
    public void exec( string query ) modify throws {
        mTokenizer     = new Tokenizer();
        mTokens        = mTokenizer.parse( query );
        mTokenIterator = mTokens.getIterator();

        /*
        foreach ( Token t :  mTokens ) {
            print( cast<string>( t ) );
        }
        */

        if ( !mTokenIterator.hasNext() ) {
            throw "invalid query provided!";
        }

        var token = consume();

        switch ( token.mValue ) {
            case "EXPLAIN"  : { explainTable(); break; }
            case "SELECT"   : { parseQuery(); break; }
            default         : { print( "invalid token '" + token.mValue + "'" ); break; }
        }
    }

    private void explainTable() modify {
        require( TokenType.IDENTIFIER );

        var table = expandTableName( current().mValue );

        var data const = new CSVReader( table, true );

        print( cast<string>( data[ 0 ] ) );
    }

    private void parseQuery() modify throws {
        Token token;

        var columnNames = new Vector<string>();

        while ( (token = peek()) &&
                ( ( token.mType == TokenType.IDENTIFIER ) || ( token.mType == TokenType.STRING ) || ( token.mType == TokenType.MATH_MULTIPLY ) ) ) {
            columnNames.push_back( consume().mValue );

            if ( peek().mType == TokenType.COMMA )
                consume();
        }

        if ( columnNames.empty() ) {
            throw "no columns selected!";
        }

        require( TokenType.FROM );

        var fromTable = expandTableName( consume().mValue );

        if ( (token = peek()) && token.mType == TokenType.WHERE ) {
            consume();
            require( TokenType.WHERE );

            // TODO: implement where-clause parsing
        }

        int limit;
        if ( (token = peek()) && token.mType == TokenType.LIMIT ) {
            consume();
            require( TokenType.INTEGER );

            limit = cast<int>( current().mValue ) + 1;  // add 1 for headers
        }

        require( TokenType.SEMICOLON );

        // execute query
        // load full table data
        var data         = new CSVReader( fromTable );
        var dataIt       = data.getIterator();
        var header const = data.header();

        var columnIndices = new Vector<int>();

        // expand column wildcards and prepare column titles
        for ( var idx = 0; idx < columnNames.size(); ) {
            var column = columnNames[ idx ];

            if ( column == "*" ) {
                columnNames.erase( idx );

                for ( var i = 0; i < header.size(); i++ ) {
                    columnNames.insert( idx + i, header[ i ] );
                }

                continue;
            }
            else {
                var colIdx = header.getIdx( column );
                if ( colIdx == -1 ) {
                    colIdx = header.getIdx( "\"" + column + "\"" );
                }

                columnIndices.push_back( colIdx );
            }

            write( " | " + column );

            idx++;
        }

        writeln( " | ");

        // print selected column data
        int rowCount;
        for ( var rowIdx = 1; rowIdx < data.size(); rowIdx++ ) {
            var row const = data[ rowIdx ];

            bool filtered;
            string result;

            for ( var colIdx = 0; colIdx < columnIndices.size(); colIdx++ ) {
                var columnID = columnIndices[ colIdx ];
                if ( columnID == -1 ) {
                    result += " | ";
                    continue;
                }

                var value = row[ columnID ];

                // filter data
                // IMPLEMENT ME

                result += " | " + value;
            }

            if ( filtered ) {
                // row has been filtered out
                continue;
            }

            print( result + " | " );

            rowCount++;

            if ( limit && rowCount >= limit - 1 ) {
                // output limit reached
                break;
            }
        }
    }


//////////////////////////////////////////////////////////////////////////////
// Helpers

	private Token consume() modify throws {
		try { return mTokenIterator.next(); }

		return Token null;
	}

	private Token current() const {
		return mTokenIterator.current();
	}

	private bool isComperator(Token token) const {
		switch ( token.mType ) {
			case TokenType.EQUAL:		{ return true; }
			case TokenType.GREATER:		{ return true; }
			case TokenType.GREATER_EQUAL:	{ return true; }
			case TokenType.LESS:		{ return true; }
			case TokenType.LESS_EQUAL:	{ return true; }
			case TokenType.UNEQUAL:		{ return true; }
			default:			{ return false; }
		}

		return false;
	}

	private Token peek( int pos = 1 ) const throws {
		try { return mTokenIterator.peek( pos ); }

		return Token null;
	}

	private string toString(Expression exp) const {
		return "[" + (exp ? exp.toString() : "<invalid expression>") + "]";
	}

	private string toString(Token token) const {
		return "[" + (token ? token.toString() : "<invalid token>") + "]";
	}

	private void require(TokenType tokenType const) modify throws {
		Token token = consume();

		if ( token.mType != tokenType ) {
			throw new ParseException(TokenToString(tokenType) + " expected but " + toString(token) + " found", token.mPosition);
		}
	}

// Helpers
//////////////////////////////////////////////////////////////////////////////

	private Iterator<Token> mTokenIterator;
	private Tokenizer mTokenizer;
	private List<Token> mTokens;
}
