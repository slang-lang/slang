=== The Slang Programming Language ===

== A scripting language that you already know ==

The Slang programming language is syntactically similar to Java, but has more advanced features like operator overloading (known from C++) and relies heavily on const-correctness. With the statically typed interpreter design time errors will be catched at.. design time, in contrast to dynamically typed languages where many errors will only occur at run time.



!!!BREAKING CHANGES!!!

- Started the long overdue process of renaming ObjectiveScript to Slang (which included
changing the names of all binaries and updating all existing script files with the
new shebang).

- changed the position of the 'static' keyword, which is now the 2nd possible keyword
after visibility and before language feature state (i.e. public static stable Method(...))

- moved implementation to a more C++14-style (heavily use move semantic and auto)

