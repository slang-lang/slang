PROGRAM Fibonacci;
CONST
	START: INTEGER := 10;
VAR
	fib1: INTEGER;
	fib2: INTEGER;
	fibonacci: INTEGER;
	i: INTEGER := 1;
	j: INTEGER;
BEGIN
	WRITELN('Start value: ' + START);

	WHILE ( i <= START ) DO
	BEGIN
		j := 3;
		fib1 := 1;
		fib2 := 1;
		fibonacci := 1;

		WHILE ( j <= i ) DO
		BEGIN
			fibonacci := fib1 + fib2;
			fib1 := fib2;
			fib2 := fibonacci;

			j := j + 1;
		END;

		WRITE( fibonacci ); WRITE( ' ' );

		i := i + 1;
	END;

	WRITELN( '...' );
END.
