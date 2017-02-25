Core:
added the ability to use incomplete boolean evaluation in special locations (currently available in "if", "switch" and "while" expressions)
added unit tests for incomplete boolean evaluation
added the ability to use single statements instead of compound statements in specific locations (currently available in "for", "foreach" and "while" expressions)
exception handling: the finally block always executes when the try block exits
slightly adjusted how reference types are handled
unified parameter collection for method call and processing of "new" keyword

Core::AST:
added Generator to create parse trees for all methods
added the ability to re-throw exceptions
simplified parsing of multiple keywords
implemented correct assignment of exception values while catching
improved symbol lookup so that namespace can get used
implemented type cast expression
minor optimizations in AST tree structure and tree interpretation
fixed unary minus expression parsing

Debugger:
added possibility to set and store automatic shutdown of debugger; automatic shutdown is only available when no breakpoint has been triggered
fixed stepping over in debugger: debugger now doesn't step into methods unless a step into has been requested explicitely

TestSuite:
added AST unit tests (toggled by GENERATE_PARSE_TREE)

General:
increased version numbers

