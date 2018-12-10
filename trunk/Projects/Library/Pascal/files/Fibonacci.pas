PROGRAM Fibonacci;
BEGIN
	VAR start: INTEGER := 10;
	PRINT('Start value: ' + start);

	VAR fib1: INTEGER;
	VAR fib2: INTEGER;
	VAR fibonacci: INTEGER;

	VAR i: INTEGER := 1;
	VAR j: INTEGER;

	WHILE ( i <= start ) DO
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

		PRINT( 'fibonacci: ' + fibonacci );

		i := i + 1;
	END;
END.
