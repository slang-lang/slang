
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
    public void exec( string query ) modify throws {
        mTokenizer     = new Tokenizer();
        mTokens        = mTokenizer.parse( query );
        mTokenIterator = mTokens.getIterator();

        /*
        foreach ( Token t :  mTokens ) {
            print( cast<string>( t ) );
        }
        */

        // data to collect:
        Vector<string> columns = new Vector<string>();
        int limit;
        int rowCount;
        string table;
        Token token;

        require( TokenType.SELECT );

        while ( (token = peek()) && ( token.mType == TokenType.IDENTIFIER ) || ( token.mType == TokenType.MATH_MULTIPLY ) ) {
            columns.push_back( consume().mValue );

            if ( peek().mType == TokenType.COMMA )
                consume();
        }

        if ( columns.empty() ) {
            throw "no columns selected!";
        }

        require( TokenType.FROM );

        table = consume().mValue;
        if ( strfind( table, ".csv" ) == -1 ) {
            table += ".csv";
        }

        if ( (token = peek()) && token.mType == TokenType.WHERE ) {
            consume();
            require( TokenType.WHERE );

            // TODO: implement where-clause parsing
        }
        if ( (token = peek()) && token.mType == TokenType.LIMIT ) {
            consume();
            require( TokenType.INTEGER );

            limit = cast<int>( current().mValue ) + 1;  // add 1 for headers
        }

        require( TokenType.SEMICOLON );

        // execute query
        // load full table data
        var data   = new CSVReader( table, true );
        var dataIt = data.getIterator();

        var columnWidth  = new Map<int, int>();
        var header const = data.header();

        // expland column wildcards and prepare column titles
        for ( var idx = 0; idx < columns.size(); idx++ ) {
            var column = columns[ idx ];

            if ( column == "*" ) {
                columns.erase( idx );

                for ( var i = 0; i < header.size(); i++ ) {
                    print( i );
                    columns.insert( idx + i, header[ i ] );
                }

                continue;
            }

            write( " | " + column );

            columnWidth.insert( idx, strlen( column ) );
        }

        writeln( " | ");

        // print selected column data
        foreach ( DataEntry row : data ) {
            string result;

            foreach ( string column : columns ) {
                var value = row[ "\"" + column + "\"" ];

                // filter data
                // IMPLEMENT ME

                result += " | " + value;
            }

            print( result + " | " );

            rowCount++;

            if ( limit && rowCount >= limit ) {
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
