
// library imports

// project imports
import Array;
import Exceptions;
import Object;
import Tokenizer;
import Value;


public namespace Json { }

public object JsonReader {
    public JsonValue parse( string text ) modify throws {
        var tokenizer = new Tokenizer();
        var tokenIt = tokenizer.parseString( text ).getIterator();

        JsonValue value;
        if ( tokenIt.hasNext() ) {
            switch ( tokenIt.next().type ) {
                case TokenType.BRACKET_OPEN: {
                    value = parseArray( tokenIt );

                    if ( tokenIt.current().type != TokenType.BRACKET_CLOSE ) {
                        throw "invalid JSON array";
                    }
                    break;
                }
                case TokenType.CURLY_BRACKET_OPEN: {
                    value = parseObject( tokenIt );

                    if ( tokenIt.current().type != TokenType.CURLY_BRACKET_CLOSE ) {
                        throw "invalid JSON object";
                    }
                    break;
                }
                default: {
                    value = parseValue( tokenIt );

                    if ( tokenIt.hasNext() ) {
                        throw "invalid JSON value";
                    }
                    break;
                }
            }
        }

        return value;
    }

    private JsonValue parseArray( Iterator<Token> t ) {
        var result = new JsonArray();
        
        require( t, TokenType.BRACKET_OPEN );

        while ( t.current().type != TokenType.BRACKET_CLOSE ) {
            result.addMember( parseValue( t ) );

            if ( t.current().type != TokenType.COMMA ) {
                break;
            }
            require( t, TokenType.COMMA );
        }

        require( t, TokenType.BRACKET_CLOSE );

        return JsonValue result;
    }

    private JsonValue parseObject( Iterator<Token> t ) throws {
        var result = new JsonObject();

        require( t, TokenType.CURLY_BRACKET_OPEN );

        while ( t.current().type != TokenType.CURLY_BRACKET_CLOSE ) {
            string key = t.current().value;
            t.next();

            require( t, TokenType.COLON );

            result.addMember( key, parseValue( t ) );

            if ( t.current().type != TokenType.COMMA ) {
                break;
            }
            require( t, TokenType.COMMA );
        }

        require( t, TokenType.CURLY_BRACKET_CLOSE );

        return JsonValue result;
    }

    private JsonValue parseValue( Iterator<Token> t ) throws {
        var token = t.current();

        JsonValue value;
        switch ( token.type ) {
            case TokenType.BRACKET_OPEN: {
                value = parseArray( t );
                break;
            }
            case TokenType.CURLY_BRACKET_OPEN: {
                value = parseObject( t )
                break;
            }
            case TokenType.BOOLEAN: {
                value = new JsonValue( token.value == "true" );
                t.next();
                break;
            }
            case TokenType.IDENTIFIER: {
                value = new JsonValue( token.value );
                t.next();
                break;
            }
            case TokenType.NUMBER: {
                value = new JsonValue( token.value );
                t.next();
                break;
            }
            case TokenType.STRING: {
                value = new JsonValue( token.value );
                t.next();
                break;
            }
            case TokenType.NULL: {
                value = new JsonValue();
                t.next();
                break;
            }
            default: {
                throw "invalid token at " + token.position.toString();
            }
        }

        return value;
    }

    private void require( Iterator<Token> t, TokenType type ) throws {
        if ( t.current().type != type ) {
            throw "required '" + TokenToString( type ) + "' but got '" + TokenToString( t.current().type ) + "' at " + t.current().position.toString();
        }

        if ( t.hasNext() ) {
            t.next();
        }
    }
}
