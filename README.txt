!!!BREAKING CHANGES!!!

- Started the long overdue process of renaming ObjectiveScript to Slang (which included
changing the names of all binaries and updating all existing script files with the
new shebang).

- changed the position of the 'static' keyword, which is now the 2nd possible keyword
after visibility and before language feature state (i.e. public static stable Method(...))

- moved implementation to a more C++14-style (heavily use move semantic and auto)

