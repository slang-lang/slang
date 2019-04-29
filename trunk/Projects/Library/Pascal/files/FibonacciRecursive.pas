PROGRAM Fibonacci;
CONST
	START: Integer := 10;
VAR
	I: Integer := 1;

FUNCTION fibonacci(number: Integer): Integer;
BEGIN
	PRINT( 'fibonacci(' + number + ')' );

	IF number <= 2 THEN BEGIN
		result := 1;
	END
	ELSE BEGIN
		result := fibonacci(number - 1) + fibonacci(number - 2);
	END;
END;

BEGIN
	PRINT('Start value: ' + START);

	WHILE ( i < START ) DO
	BEGIN
		PRINT( i + ': ' + fibonacci(i) );

		i := i + 1;
	END;
END.
