
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
        tokenizer = new Tokenizer();
    }

    public JsonValue process(string text) modify throws {
        print("process(" + text + ")");

        tokenizer.parseString(text);

        JsonValue value;
        if ( tokenizer.hasNextToken() ) {
            switch ( tokenizer.nextToken().mType ) {
                case TokenType.BRACKET_OPEN: {
                    value = parseArray(tokenizer);

                    if ( tokenizer.currentToken().mType != TokenType.BRACKET_CLOSE ) {
                        throw "invalid JSON array";
                    }
                    break;
                }
                case TokenType.CURLY_BRACKET_OPEN: {
                    value = parseObject(tokenizer);

                    if ( tokenizer.currentToken().mType != TokenType.CURLY_BRACKET_CLOSE ) {
                        throw "invalid JSON object";
                    }
                    break;
                }
                default: {
                    value = parseValue(tokenizer);

                    if ( tokenizer.hasNextToken() ) {
                        throw "invalid JSON value";
                    }
                    break;
                }
            }
        }

        return value;
    }

    private JsonValue parseArray(Tokenizer t) {
        if ( !t ) {
            return JsonValue null;
        }

        //print("Array::Begin");

        require(t, TokenType.BRACKET_OPEN);

        JsonArray result = new JsonArray();

        while ( t.currentToken().mType != TokenType.BRACKET_CLOSE ) {
            result.addMember(parseValue(t));

            if ( t.currentToken().mType != TokenType.COMMA ) {
                break;
            }
            require(t, TokenType.COMMA);
        }

        require(t, TokenType.BRACKET_CLOSE);

        //print("Array::End");

        return JsonValue result;
    }

    private JsonValue parseObject(Tokenizer t) throws {
        if ( !t ) {
            return JsonValue null;
        }

        //print("Object::Begin");

        require(t, TokenType.CURLY_BRACKET_OPEN);

        JsonObject result = new JsonObject();

        while ( t.currentToken().mType != TokenType.CURLY_BRACKET_CLOSE ) {
            string key = t.currentToken().mValue;
            //print("key: '" + key + "'");
            t.nextToken();

            require(t, TokenType.COLON);

            result.addMember(key, parseValue(t));

            if ( t.currentToken().mType != TokenType.COMMA ) {
                break;
            }
            require(t, TokenType.COMMA);
        }

        require(t, TokenType.CURLY_BRACKET_CLOSE);

        //print("Object::End");

        return JsonValue result;
    }

    private JsonValue parseValue(Tokenizer t) throws {
        if ( !t ) {
            return JsonValue null;
        }

        //print("Value::Begin");

        JsonValue value;

        switch ( t.currentToken().mType ) {
            case TokenType.BRACKET_OPEN: {
                value = parseArray(t);
                break;
            }
            case TokenType.CURLY_BRACKET_OPEN: {
                value = parseObject(t)
                break;
            }
            case TokenType.BOOLEAN: {
                value = new JsonValue(t.currentToken().mValue);
                t.nextToken();
                break;
            }
            case TokenType.IDENTIFIER: {
                value = new JsonValue(t.currentToken().mValue);
                t.nextToken();
                break;
            }
            case TokenType.NUMBER: {
                value = new JsonValue(t.currentToken().mValue);
                t.nextToken();
                break;
            }
            case TokenType.STRING: {
                value = new JsonValue(t.currentToken().mValue);
                t.nextToken();
                break;
            }
            case TokenType.NULL: {
                value = new JsonValue("null");
                t.nextToken();
                break;
            }
            default: {
                throw "invalid JsonValue";
            }
        }

        //print("value: '" + value.toString() + "'");
        //print("Value::End");

        return value;
    }

    private void require(Tokenizer t, TokenType type) {
        //print("require: '" + TokenToString(type) + "'" +
        //      " got: '" + TokenToString(t.currentToken().mType) + "'");

        assert( t.currentToken().mType == type );

        if ( t.hasNextToken() ) {
            t.nextToken();
        }
    }

    private Tokenizer tokenizer;
}
