#!/usr/local/bin/slang

import SemVer;


public void Main(int argc = 0, string args = "") {
    assert( TestCase1() );
    assert( TestCase2() );
    assert( TestCase3() );
    assert( TestCase4() );
}

private bool TestCase1() {
    print("TestCase 1: happy path without additional label");

    var ver = SemVer.FromString("1.2.3");

    assert( ver.Major == 1 );
    assert( ver.Minor == 2 );
    assert( ver.Bugfix == 3 );

    return cast<string>( ver ) == "1.2.3";
}

private bool TestCase2() {
    print("TestCase 2: happy path with additional label");

    var ver = SemVer.FromString("1.2.3-rc1");

    assert( ver.Major == 1 );
    assert( ver.Minor == 2 );
    assert( ver.Bugfix == 3 );
    assert( ver.Label == "rc1" );

    return cast<string>( ver ) == "1.2.3-rc1";
}

private bool TestCase3() {
    print("TestCase 3: sad path");

    try {
        var ver = SemVer.FromString("1.2");
    }
    catch ( string e ) {
        assert( e == "invalid semantic version number '1.2'" );

        return true;
    }

    return false;
}

private bool TestCase4() {
    print("TestCase 4: increment version number");

    var ver123 = new SemVer(1, 2, 3);
    assert( cast<string>( ver123 ) == "1.2.3" );

    var ver124 = ver123.nextBugfix();
    assert( cast<string>( ver124 ) == "1.2.4" );

    var ver130 = ver124.nextMinor();
    assert( cast<string>( ver130 ) == "1.3.0" );

    var ver200 = ver130.nextMajor();
    assert( cast<string>( ver200 ) == "2.0.0" );

    return true;
}
