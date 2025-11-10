UNIT IAmAUnit;

INTERFACE

FUNCTION GETNAME(): String;

IMPLEMENTATION

VAR
	name: String;

FUNCTION GETNAME(): String;
BEGIN
	Result := name;
END;

BEGIN
	name := 'I am a unit';
END.
