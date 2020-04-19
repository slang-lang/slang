Basic: removed all usages of "val"-keyword
Core: added global version information
Core: changed behaviour of "for"-loops and "foreach"-loops: both constructs have their own scope, so that loop variable names can be reused
Core: removed "val"-keyword so that parameters or (local) variables can either be declared as "by reference" or the system automatically decides according to the type of parameter/variable
Core: fixed a memleak in handling assignments
Core: fixed a bug in handling assignments with value changes (+=, -=, etc.)
slang: Used global version information instead
slang-dbg: Used global version information instead
slang-pkg: Used global version information instead
Pascal: removed all usages of "val"-keyword
System Library: removed all usages of "val"-keyword
Unit tests: added new unit test for for-loop and foreach-loop scope changes
Unit tests: added unit tests for assignment addition and subtraction
Unit tests: removed all usages of "val"-keyword
