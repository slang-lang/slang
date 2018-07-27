#!/usr/local/bin/Basic.os
100 REM This is probably the canonical BASIC example
110 REM Program. Note that REM statements are ignored.
120 PRINT "This is a test program."
130 PRINT "Summing the values between 1 and 100"
140 LET A=0
150 FOR I = 1 TO 100
160 LET A = A + i
170 NEXT I
180 PRINT "The total of all digits between 1 and 100 is " + A
190 END
