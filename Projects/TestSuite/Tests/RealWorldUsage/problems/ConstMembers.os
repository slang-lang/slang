#!/usr/local/bin/slang

public object ConstMember {
    public int Value const;

    public void mod( int value ) modify throws {
        Value = value;
        throw "this should not be possible!";
    }
}

public void Main( int, string ) {
    var constMember = new ConstMember();
    constMember.mod( 17 );
}

