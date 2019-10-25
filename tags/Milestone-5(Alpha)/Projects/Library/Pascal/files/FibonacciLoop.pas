PROGRAM Fibonacci;
VAR
	I: Integer := 1;
	MAX: Integer := 0;

FUNCTION fibonacciLoop(number: Integer): Integer;
VAR
	fibo1: Integer := 1;
	fibo2: Integer := 1;
	fibonacci: Integer := 1;
	idx: Integer := 3;
BEGIN
	IF ( number = 1 ) OR ( number = 2 ) THEN
		result := 1
	ELSE
	BEGIN
		WHILE ( idx <= number ) DO
		BEGIN
			fibonacci := fibo1 + fibo2;
			fibo1 := fibo2;
			fibo2 := fibonacci;

			idx := idx + 1;
		END;

		result := fibonacci;
	END;
END;

BEGIN
	WRITE( 'Start value: ' );
	READLN( MAX );

	WHILE ( i <= MAX ) DO
	BEGIN
		WRITE( fibonacciLoop(i) );
		WRITE( ', ' );

		i := i + 1;
	END;

	WRITELN( '...' );
END.
