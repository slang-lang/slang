
#ifndef Core_Consts_h
#define Core_Consts_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations

// Global defines


namespace Slang {


// Predefined identifiers
static const char* IDENTIFIER_BASE = "base";
static const char* IDENTIFIER_THIS = "this";

// Keywords
static const char* KEYWORD_ASSERT   = "assert";
static const char* KEYWORD_BREAK    = "break";
static const char* KEYWORD_CASE     = "case";
static const char* KEYWORD_CAST     = "cast";
static const char* KEYWORD_CATCH    = "catch";
static const char* KEYWORD_CONTINUE = "continue";
static const char* KEYWORD_COPY     = "copy";
static const char* KEYWORD_DEFAULT  = "default";
static const char* KEYWORD_DELETE   = "delete";
static const char* KEYWORD_ELSE     = "else";
static const char* KEYWORD_EXIT     = "exit";
static const char* KEYWORD_FINALLY  = "finally";
static const char* KEYWORD_FOR      = "for";
static const char* KEYWORD_FOREACH  = "foreach";
static const char* KEYWORD_IF       = "if";
static const char* KEYWORD_NEW      = "new";
static const char* KEYWORD_PRINT    = "print";
static const char* KEYWORD_RETURN   = "return";
static const char* KEYWORD_SWITCH   = "switch";
static const char* KEYWORD_THROW    = "throw";
static const char* KEYWORD_TRY      = "try";
static const char* KEYWORD_TYPEID   = "typeid";
static const char* KEYWORD_VAR      = "var";
static const char* KEYWORD_WHILE    = "while";

// Language feature states
static const char* LANGUAGE_FEATURE_DEPRECATED     = "deprecated";
static const char* LANGUAGE_FEATURE_NONE           = "";
static const char* LANGUAGE_FEATURE_NOTIMPLEMENTED = "notimplemented";
static const char* LANGUAGE_FEATURE_STABLE         = "stable";
static const char* LANGUAGE_FEATURE_UNSPECIFIED    = "";
static const char* LANGUAGE_FEATURE_UNSTABLE       = "unstable";

// Memory layout
static const char* MEMORY_LAYOUT_ABSTRACT = "abstract";
static const char* MEMORY_LAYOUT_FINAL    = "final";
static const char* MEMORY_LAYOUT_OVERRIDE = "override";
static const char* MEMORY_LAYOUT_STATIC   = "static";
static const char* MEMORY_LAYOUT_VIRTUAL  = "virtual";

// Modifiers
static const char* MODIFIER_HEURISTIC = "heuristic";	// no reserved word, antonym to "recursive"
static const char* MODIFIER_NOTHROW   = "nothrow";		// no reserved word, antonym to "throws"
static const char* MODIFIER_RECURSIVE = "recursive";	// antonym to "heuristic"
static const char* MODIFIER_SEALED    = "sealed";
static const char* MODIFIER_THROWS    = "throws";			// antonym to "nothrow"

// Mutability
static const char* MUTABILITY_CONST  = "const";
static const char* MUTABILITY_MODIFY = "modify";

// Operators
static const char* OPERATOR_IS = "is";

// Reserved words
static const char* RESERVED_WORD_BY_REFERENCE   = "ref";
static const char* RESERVED_WORD_BY_VALUE       = "val";
static const char* RESERVED_WORD_CONSTRUCTOR    = "Constructor";
static const char* RESERVED_WORD_DESTRUCTOR     = "Destructor";
static const char* RESERVED_WORD_ENUM           = "enum";
static const char* RESERVED_WORD_EXTENDS        = "extends";
static const char* RESERVED_WORD_IMPLEMENTS     = "implements";
static const char* RESERVED_WORD_IMPORT         = "import";
static const char* RESERVED_WORD_INTERFACE      = "interface";
static const char* RESERVED_WORD_NAMESPACE      = "namespace";
static const char* RESERVED_WORD_OBJECT         = "object";
static const char* RESERVED_WORD_OPERATOR       = "operator";
static const char* RESERVED_WORD_REPLICATES     = "replicates";
static const char* RESERVED_WORD_SCOPE_OPERATOR = ".";

// System
static const char* ANONYMOUS_OBJECT = "<anonymous>";
static const char* NULL_TYPE        = "<anonymous>";
static const char* SLANG_HOME       = "SLANG_HOME";
static const char* SLANG_LIBRARY    = "SLANG_LIBRARY";
static const char* SYSTEM_LIBRARY   = "SYSTEM.SLANG";
static const char* UNKNOWN          = "unknown";

// Types
static const char* _any = "";
static const char* _bool = "bool";
static const char* _bool_object = "Boolean";
static const char* _double = "double";
static const char* _double_object = "Double";
static const char* _enum = "enum";
static const char* _float = "float";
static const char* _float_object = "Float";
static const char* _int8 = "int8";
static const char* _int16 = "int16";
static const char* _int32 = "int";
static const char* _int64 = "int64";
static const char* _int_object = "Integer";
static const char* _object = "Object";
static const char* _string = "string";
static const char* _string_object = "String";
static const char* _void = "void";
static const char* _unary_ = "__unary__";			// special type to handle unary type operation checks

// Values
static const char* VALUE_FALSE = "false";
static const char* VALUE_NONE  = "";
static const char* VALUE_NULL  = "null";
static const char* VALUE_TRUE  = "true";

// Visibility
static const char* PRIVATE   = "private";
static const char* PROTECTED = "protected";
static const char* PUBLIC    = "public";

// Unsorted
static const char* DEFAULT = "default";
static const char* EMPTY   = "";


}


#endif
