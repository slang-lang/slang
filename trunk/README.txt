Core:
added ability to use incomplete boolean evaluation in special locations (currently available in "if", "switch" and "while" expressions)
added unit tests for incomplete boolean evaluation

Debugger:
added possibility to set and store automatic shutdown of debugger; automatic shutdown is only available when no breakpoint has been triggered
fixed stepping over in debugger: debugger now doesn't step into methods unless a step into has been requested explicitely

