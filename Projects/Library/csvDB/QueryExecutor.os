
// library imports
import libCSVReader;
import System.Collections.Vector;

// project imports
import Expressions;
import Tokenizer;


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
    public void Constructor() {
        mTableData = new Map<string, CSVReader>();
    }

    public void exec( string query ) modify throws {
        mTokenizer     = new Tokenizer();
        mTokens        = mTokenizer.parse( query );
        mTokenIterator = mTokens.getIterator();

        foreach ( Token t :  mTokens ) {
            print( cast<string>( t ) );
        }

        require( TokenType.FROM );

        // data to collect:
        Vector<string> columns = new Vector<string>();
        int limit;
        int rowCount;
        string table;
        Token token;

        token = consume();

        table = token.mValue;
        //print( "FROM: " + table );

        require( TokenType.SELECT );

        while ( (token = consume()) && token.mType == TokenType.IDENTIFIER ) {
            columns.push_back( token.mValue );

            if ( peek().mType == TokenType.COMMA )
                consume();
        }

        if ( columns.empty() ) {
            throw "no columns to select specified!";
        }

        print( toString( token ) );

        if ( token && token.mType == TokenType.WHERE ) {
            // TODO: implement where-clause parsing
        }
        if ( token && token.mType == TokenType.LIMIT ) {
            require( TokenType.INTEGER );

            limit = cast<int>( current().mValue );
        }

        require( TokenType.SEMICOLON );

        // execute query
        // load full table data
        mTableData.insert( table, new CSVReader( table ) );

        // filter data
        // IMPLEMENT ME

        // print selected column data
        foreach ( Pair<string, CSVReader> table : mTableData ) {
            foreach ( DataEntry row : table.second ) {
                string result;

                foreach ( string column : columns ) {
                    result += " | " + row[ "\"" + column + "\"" ];
                }

                print( result + " | " );

                rowCount++;

                if( limit && rowCount >= limit ) {
                    // output limit reached
                    break;
                }
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

    private Map<string, CSVReader> mTableData;
	private Iterator<Token> mTokenIterator;
	private Tokenizer mTokenizer;
	private List<Token> mTokens;
}
