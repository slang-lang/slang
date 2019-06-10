Program RepeatUntilExit;
Var idx: Integer;
begin
    WriteLn('Repeat until loop test');

    repeat
        idx := idx + 1;

        WriteLn('idx := ' + idx);

        continue;
    until ( idx >= 10 );

    WriteLn('Done.');
end.
