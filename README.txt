How to build ObjectiveScript
============================

These build systems are currently configured:

	- MS Visual Studio 2008 (Express)
	- CMake


MS Visual Studio 2008 (Express)
-------------------------------

Open the solution file "ObjectiveScript.sln" in the folder "VS2008" in your desired branch/trunk and hit "Build"->"Build Solution". This should leave you with the executables "oscript.exe" and "TestSuite.exe".


CMake
-----

Create a build directory next to your source directory (i.e. "<project root>/src" & "<project root>/build") and change into the build directory. Hit "cmake ../src/" to build ObjectiveScript. Per default this creates the (release) binaries "<project root>/build/bin/oscript/oscript" & "<project root>/build/bin/TestSuite/Test". 


After building the targets running the unit tests is a good starting point. You can simply do this by running the "TestSuite" project in MS Visual Studio. CMake builds are a bit more complicated because the script files that are used during the units test have to be accessible for the "TestSuite" binary. The easiest way to accomplish this is making a symlink:

	cd "<project root>/build/bin/TestSuite/"
	ln -s "<project root>/src/Projects/TestSuite/Tests" Tests

Now you should be able to run the units test by executing "./TestSuite" from its containing directory.
