PROGRAM Complex;
BEGIN
    BEGIN
        number := 2;
        a := number;
        b := 10 * a + 10 * number / 4;
        c := a - -b;

        PRINT( c );
    END;

    x := 11;
    PRINT( x );
END.
