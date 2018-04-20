#!/usr/local/bin/oscript /Users/madelmann/workspace/ObjectiveScript/src/Projects/TestSuite/Tests/RealWorldUsage/Basic/Basic.os
10 REM This is a simple BASIC script that tests the IF keyword
20 DIM A = 1
30 DIM B = 2

100 IF A = 1 THEN GOTO 130
110 PRINT "A = 1 => FAILED"
120 END
130 PRINT "A = 1 => SUCCESS"

200 IF B = 3 THEN GOTO 230
210 PRINT "B = 3 => FAILED"
220 END
230 PRINT "B = 3 => SUCCESS"

300 IF A = B THEN GOTO 330
310 PRINT "A = B => FAILED"
320 END
330 PRINT "A = B => SUCCESS"

400 REM END

