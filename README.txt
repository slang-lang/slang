Core:
added ability to use incomplete boolean evaluation in special locations (currently available in "if", "switch" and "while" expressions)
added unit tests for incomplete boolean evaluation

Core::AST:
added Generator to create parse trees for all methods
improved symbol lookup so that namespace can get used
implemented type cast expression
fixed unary minus expression parsing

Debugger:
added possibility to set and store automatic shutdown of debugger; automatic shutdown is only available when no breakpoint has been triggered
fixed stepping over in debugger: debugger now doesn't step into methods unless a step into has been requested explicitely

TestSuite:
added AST unit tests (toggled by GENERATE_PARSE_TREE)

