PROGRAM SumOf1To100;
VAR
	COUNT: INTEGER := 1;
	SUM: INTEGER;
BEGIN
	WRITELN( 'Summing the values between 1 and 100' );

	FOR COUNT := 1 TO 100 DO
	BEGIN
		SUM := SUM + COUNT;
	END;

	WRITELN( 'The total of all digits between 1 and 100 is ' + SUM );
END.
