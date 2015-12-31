
#ifndef Core_Consts_h
#define Core_Consts_h


// Library includes

// Project includes

// Forward declarations

// Namespace declarations

// Global defines
//#define USE_EXTREME_CONST_CORRECTNESS


namespace ObjectiveScript {


// Boolean values
static const char* FALSE = "false";
static const char* TRUE = "true";

// Keywords
static const char* KEYWORD_ASSERT = "assert";
static const char* KEYWORD_BREAK = "break";
static const char* KEYWORD_CASE = "case";
static const char* KEYWORD_DELETE = "delete";
static const char* KEYWORD_ELSE = "else";
static const char* KEYWORD_FOR = "for";
static const char* KEYWORD_IF = "if";
static const char* KEYWORD_IMPORT = "import";
static const char* KEYWORD_NEW = "new";
static const char* KEYWORD_PRINT = "print";
static const char* KEYWORD_RETURN = "return";
static const char* KEYWORD_SWITCH = "switch";
static const char* KEYWORD_WHILE = "while";

// Language feature states
static const char* LANGUAGE_FEATURE_DEPRECATED = "deprecated";
static const char* LANGUAGE_FEATURE_NONE = "";
static const char* LANGUAGE_FEATURE_NOTIMPLEMENTED = "notimplemented";
static const char* LANGUAGE_FEATURE_STABLE = "stable";
static const char* LANGUAGE_FEATURE_UNKNOWN = "unknown";
static const char* LANGUAGE_FEATURE_UNSTABLE = "unstable";

// Modifiers
static const char* MODIFIER_CONST = "const";
static const char* MODIFIER_FINAL = "final";
static const char* MODIFIER_MODIFY = "modify";
static const char* MODIFIER_STATIC = "static";

// Reserved words
static const char* RESERVED_WORD_BY_REFERENCE = "ref";
static const char* RESERVED_WORD_BY_VALUE = "val";
static const char* RESERVED_WORD_EXTENDS = "extends";
static const char* RESERVED_WORD_INTERFACE = "interface";
static const char* RESERVED_WORD_OBJECT = "object";
static const char* RESERVED_WORD_OPERATOR = "operator";
static const char* RESERVED_WORD_PROTOTYPE = "prototype";
static const char* RESERVED_WORD_USING = "using";

// System
static const char* ANONYMOUS_OBJECT = "<anonymous>";
static const char* SYSTEM_LIBRARY = "SYSTEM.OS";
static const char* TEMPORARY_OBJECT = "<temporary>";

// Types
static const char* PROTOTYPE_TYPE = "UNKNOWN";

// Values
static const char* VALUE_NULL = "null";

// Visibility
static const char* PRIVATE = "private";
static const char* PROTECTED = "protected";
static const char* PUBLIC = "public";


}


#endif
