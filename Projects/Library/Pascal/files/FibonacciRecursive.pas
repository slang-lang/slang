PROGRAM Fibonacci;
CONST
	START: Integer := 10;
VAR
	I: Integer := 1;

FUNCTION fibonacci(number: Integer): Integer;
BEGIN
	IF number <= 2 THEN
		result := 1
	ELSE
		result := fibonacci(number - 1) + fibonacci(number - 2);
END;

BEGIN
	WRITELN('Start value: ' + START);

	WHILE ( i < START ) DO
	BEGIN
		WRITELN( 'i = ' + i );
		WRITELN( fibonacci(i) + ', ' );
		WRITELN( 'i = ' + i );

		i := i + 1;
	END;

	WRITELN('...');
END.
