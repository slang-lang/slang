#!/usr/local/bin/oscript /Users/madelmann/workspace/ObjectiveScript/src/Projects/TestSuite/Tests/RealWorldUsage/Basic/Basic.os
10 REM This is a simple BASIC script that tests the IF keyword
20 DIM A = 1
30 DIM B = 2
40 IF A < B THEN GOTO 70
50 PRINT "A < B => FAILED"
60 END
70 PRINT "A < B => SUCCESS"

