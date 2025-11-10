Program RepeatUntil;
Var idx: Integer;
begin
    WriteLn('Repeat until loop test');

    repeat
        idx := idx + 1;
        WriteLn('idx := ' + idx);
    until (idx >= 10);

    WriteLn('Done.');
end.