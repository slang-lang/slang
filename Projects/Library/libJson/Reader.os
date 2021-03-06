
// library imports

// project imports
import Array;
import Exceptions;
import Object;
import Tokenizer;
import Value;


public namespace Json {
}

public object JsonReader {
    public void Constructor() {
        mTokenizer = new Tokenizer();
    }

    public JsonValue parse( string text ) modify throws {
        //print("parse(" + text + ")");

        mTokenizer.parseString( text );

        JsonValue value;
        if ( mTokenizer.hasNextToken() ) {
            switch ( mTokenizer.nextToken().mType ) {
                case TokenType.BRACKET_OPEN: {
                    value = parseArray( mTokenizer );

                    if ( mTokenizer.currentToken().mType != TokenType.BRACKET_CLOSE ) {
                        throw "invalid JSON array";
                    }
                    break;
                }
                case TokenType.CURLY_BRACKET_OPEN: {
                    value = parseObject( mTokenizer );

                    if ( mTokenizer.currentToken().mType != TokenType.CURLY_BRACKET_CLOSE ) {
                        throw "invalid JSON object";
                    }
                    break;
                }
                default: {
                    value = parseValue( mTokenizer );

                    if ( mTokenizer.hasNextToken() ) {
                        throw "invalid JSON value";
                    }
                    break;
                }
            }
        }

        return value;
    }

    private JsonValue parseArray( Tokenizer t ) {
        if ( !t ) {
            return JsonValue null;
        }

        require( t, TokenType.BRACKET_OPEN );

        JsonArray result = new JsonArray();

        while ( t.currentToken().mType != TokenType.BRACKET_CLOSE ) {
            result.addMember( parseValue( t ) );

            if ( t.currentToken().mType != TokenType.COMMA ) {
                break;
            }
            require( t, TokenType.COMMA );
        }

        require( t, TokenType.BRACKET_CLOSE );

        return JsonValue result;
    }

    private JsonValue parseObject( Tokenizer t ) throws {
        if ( !t ) {
            return JsonValue null;
        }

        require( t, TokenType.CURLY_BRACKET_OPEN );

        var result = new JsonObject();

        while ( t.currentToken().mType != TokenType.CURLY_BRACKET_CLOSE ) {
            string key = t.currentToken().mValue;
            t.nextToken();

            require( t, TokenType.COLON );

            result.addMember( key, parseValue( t ) );

            if ( t.currentToken().mType != TokenType.COMMA ) {
                break;
            }
            require( t, TokenType.COMMA );
        }

        require( t, TokenType.CURLY_BRACKET_CLOSE );

        return JsonValue result;
    }

    private JsonValue parseValue( Tokenizer t ) throws {
        if ( !t ) {
            return JsonValue null;
        }

        JsonValue value;

        switch ( t.currentToken().mType ) {
            case TokenType.BRACKET_OPEN: {
                value = parseArray( t );
                break;
            }
            case TokenType.CURLY_BRACKET_OPEN: {
                value = parseObject( t )
                break;
            }
            case TokenType.BOOLEAN: {
                value = new JsonValue( t.currentToken().mValue );
                t.nextToken();
                break;
            }
            case TokenType.IDENTIFIER: {
                value = new JsonValue( t.currentToken().mValue );
                t.nextToken();
                break;
            }
            case TokenType.NUMBER: {
                value = new JsonValue( t.currentToken().mValue );
                t.nextToken();
                break;
            }
            case TokenType.STRING: {
                value = new JsonValue( t.currentToken().mValue );
                t.nextToken();
                break;
            }
            case TokenType.NULL: {
                value = new JsonValue( "null" );
                t.nextToken();
                break;
            }
            default: {
                throw "invalid token at " + t.currentToken().mPosition.toString();
            }
        }

        return value;
    }

    private void require( Tokenizer t, TokenType type ) throws {
        if ( t.currentToken().mType != type ) {
            throw "required '" + TokenToString( type ) + "' but got '" + TokenToString( t.currentToken().mType ) + "'";
        }

        if ( t.hasNextToken() ) {
            t.nextToken();
        }
    }

    private Tokenizer mTokenizer;
}

