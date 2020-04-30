# The Slang Programming Language

The Slang programming language is syntactically similar to Java and functionally similar to C++ (hence slang). In contrast to Java it offers more advanced features like operator overloading and RAII (both known from C++) and relies heavily on const-correctness. Checked exceptions are present but are strongly mitigated in constrast to Java's checked exceptions, which makes it easier to work with. With the statically typed parser/interpreter design time errors will be catched at.. design time, in contrast to dynamically typed languages where many errors will simply occur at run time. So syntax errors will be detected before running your program.
Slang offers native data types like bool, double, float, int and string as well as user defined object types and a system library with data types similar to the Java boxed types like Integer and String. Collections like List, Map, etc. can be used with object and value types and can also be used as raw types (i.e. List == List< Object >).




# !!!BREAKING CHANGES!!!

- Started the long overdue process of renaming ObjectiveScript to Slang (which included
changing the names of all binaries and updating all existing script files with the
new shebang).

- changed the position of the 'static' keyword, which is now the 2nd possible keyword
after visibility and before language feature state (i.e. public static stable Method(...))

- merged the memory layout tokens (static, instance) and modifier tokens (final, override, virtual) into the new memory layout types (final, override, static, virtual)

- moved the implementation to a more C++14-style (heavily use move semantic and auto)

