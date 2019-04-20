PROGRAM SumOf1To100;
VAR
	COUNT: INTEGER := 1;
	SUM: INTEGER;
BEGIN
	PRINT( 'Summing the values between 1 and 100' );

	WHILE ( COUNT <= 100 ) DO
	BEGIN
		COUNT := COUNT + 1;
		SUM := SUM + COUNT;
	END;

	PRINT( 'The total of all digits between 1 and 100 is ' + SUM );
END.
