PROGRAM Complex;
BEGIN
    BEGIN
        VAR number: INTEGER := 2;
        VAR a: INTEGER := number;
        VAR b: INTEGER := 10 * a + 10 * number / 4;
        VAR c: INTEGER := a - -b;

        PRINT( c );
    END;

    VAR x: INTEGER := 11;
    PRINT( x );
END.
