#!/usr/bin/env slang

import MsgQueue;


public void Main( int, string )
{
    assert( TestCase1() );
    assert( TestCase2() );
    assert( TestCase3() );
}

private bool TestCase1()
{
    var queue = new MsgQueue( 10000, false );

    return queue.IsOpen();
}

private bool TestCase2()
{
    var queue = new MsgQueue( 10000, false );

    return queue.IsOpen();
}

private bool TestCase3()
{
    var queue = new MsgQueue( 10000, false );

    return queue.IsOpen();
}
