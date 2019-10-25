Program ProcedureWithManyParameters;

Procedure Proc1(param1: Integer; param2: String; param3: Boolean);
Begin
	WRITELN('param1: ' + param1);
	WRITELN('param2: ' + param2);
	WRITELN('param3: ' + param3);
End;

Begin
	Proc1(1, '2', true);
End.

