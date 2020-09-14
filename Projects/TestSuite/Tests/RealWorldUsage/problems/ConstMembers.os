#!/usr/local/bin/slang

public object ConstMember {
    public int Value const;

    public void modify( int value ) modify {
        Value = value;
    }
}

public void Main( int, string ) {
    var constMember = new ConstMember();
    constMember.modify( 17 );
}
