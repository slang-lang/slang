PROGRAM Fibonacci;
VAR
	I: Integer := 1;
	MAX: Integer := 0;

FUNCTION fibonacci(number: Integer): Integer;
BEGIN
	IF (number = 1) OR (number = 2) THEN
		result := 1
	ELSE
		result := fibonacci(number - 1) + fibonacci(number - 2);
END;

BEGIN
	WRITE( 'Start value: ' );
	READLN( MAX );

	WHILE ( i <= MAX ) DO
	BEGIN
		WRITE( fibonacci(i) ); WRITE( ', ' );

		i := i + 1;
	END;

	WRITELN( '...' );
END.
