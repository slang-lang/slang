
#ifndef Core_Consts_h
#define Core_Consts_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations

// Global defines


namespace ObjectiveScript {


// Boolean values
static const char* BOOL_FALSE = "false";
static const char* BOOL_TRUE = "true";

// Predefined identifiers
static const char* IDENTIFIER_BASE = "base";
static const char* IDENTIFIER_THIS = "this";

// Keywords
static const char* KEYWORD_ASSERT = "assert";
static const char* KEYWORD_BREAK = "break";
static const char* KEYWORD_CASE = "case";
static const char* KEYWORD_CATCH = "catch";
static const char* KEYWORD_CONTINUE = "continue";
static const char* KEYWORD_COPY = "copy";
static const char* KEYWORD_DEFAULT = "default";
static const char* KEYWORD_DELETE = "delete";
static const char* KEYWORD_ELSE = "else";
static const char* KEYWORD_EXIT = "exit";
static const char* KEYWORD_FINALLY = "finally";
static const char* KEYWORD_FOR = "for";
static const char* KEYWORD_IF = "if";
static const char* KEYWORD_NEW = "new";
static const char* KEYWORD_PRINT = "print";
static const char* KEYWORD_RETURN = "return";
static const char* KEYWORD_SWITCH = "switch";
static const char* KEYWORD_THROW = "throw";
static const char* KEYWORD_TRY = "try";
static const char* KEYWORD_WHILE = "while";

// Language feature states
static const char* LANGUAGE_FEATURE_DEPRECATED = "deprecated";
static const char* LANGUAGE_FEATURE_NONE = "";
static const char* LANGUAGE_FEATURE_NOTIMPLEMENTED = "notimplemented";
static const char* LANGUAGE_FEATURE_STABLE = "stable";
static const char* LANGUAGE_FEATURE_UNSTABLE = "unstable";

// Modifiers
static const char* MODIFIER_ABSTRACT = "abstract";
static const char* MODIFIER_CONST = "const";
static const char* MODIFIER_FINAL = "final";
static const char* MODIFIER_MODIFY = "modify";
static const char* MODIFIER_RECURSIVE = "recursive";
static const char* MODIFIER_SEALED = "sealed";
static const char* MODIFIER_STATIC = "static";

// Operators
static const char* OPERATOR_IS = "is";

// Reserved words
static const char* RESERVED_WORD_BY_REFERENCE = "ref";
static const char* RESERVED_WORD_BY_VALUE = "val";
static const char* RESERVED_WORD_ENUM = "enum";
static const char* RESERVED_WORD_EXTENDS = "extends";
static const char* RESERVED_WORD_IMPLEMENTS = "implements";
static const char* RESERVED_WORD_IMPORT = "import";
static const char* RESERVED_WORD_INTERFACE = "interface";
static const char* RESERVED_WORD_NAMESPACE = "namespace";
static const char* RESERVED_WORD_OBJECT = "object";
static const char* RESERVED_WORD_OPERATOR = "operator";
static const char* RESERVED_WORD_PROTOTYPE = "prototype";
static const char* RESERVED_WORD_REPLICATES = "replicates";
static const char* RESERVED_WORD_SCOPE_OPERATOR = ".";
static const char* RESERVED_WORD_THROWS = "throws";
static const char* RESERVED_WORD_USING = "using";

// System
static const char* ANONYMOUS_OBJECT = "<anonymous>";
static const char* NULL_TYPE = "<anonymous>";
static const char* OBJECT = "Object";
static const char* OBJECTIVESCRIPT_LIBRARY = "OBJECTIVESCRIPT_LIBRARY";
static const char* SYSTEM_LIBRARY = "SYSTEM.OS";
static const char* UNKNOWN = "unknown";

// Types
static const char* PROTOTYPE_TYPE = "UNKNOWN";

// Values
static const char* VALUE_NONE = "";
static const char* VALUE_NULL = "null";

// Visibility
static const char* PRIVATE = "private";
static const char* PROTECTED = "protected";
static const char* PUBLIC = "public";


}


#endif