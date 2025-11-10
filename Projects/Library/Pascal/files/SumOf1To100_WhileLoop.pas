PROGRAM SumOf1To100;
VAR
	COUNT: INTEGER := 1;
	SUM: INTEGER;
BEGIN
	WRITELN( 'Summing the values between 1 and 100' );

	WHILE ( COUNT <= 100 ) DO
	BEGIN
		SUM := SUM + COUNT;
		COUNT := COUNT + 1;
	END;

	WRITELN( 'The total of all digits between 1 and 100 is ' + SUM );
END.
