#!/usr/bin/env slang

import FileReader.Scanner;
import System.Collections.List;
import System.Collections.Map;
import libJson;
import libSemVer;


public void Main( int argc, string args )
{
    var modules = new List<Module>();

    var files = new String( system( "ls */module.json" ) );

    try {
        foreach ( string m : files.SplitBy( LINEBREAK ) ) {
            if ( m ) {
                var module = loadModule( m );

                foreach ( Dependency dep : module.Dependencies ) {
                    foreach ( Module existing : modules ) {
                        if ( dep.Name != existing.Name )
                            continue;

                        if ( dep.VersionMin && dep.VersionMin > existing.Version ) {
                            print( cast<string>( dep.VersionMin ) + " > " + cast<string>( existing.Version ) );

                            throw module.Name + "(" + cast<string>( module.Version ) + ") is not compatible with " + existing.Name + "(" + cast<string>( module.Version ) + ")";
                        }

                        if ( dep.VersionMax && dep.VersionMax < existing.Version ) {
                            print( cast<string>( dep.VersionMax ) + " < " + cast<string>( existing.Version ) );

                            throw module.Name + "(" + cast<string>( module.Version ) + ") is not compatible with " + existing.Name + "(" + cast<string>( module.Version ) + ")";
                        }
                    }
                }

                modules.push_back( module );

                print( cast<string>( module ) );
            }
        }

        print( "Dependencies are OK" );
    }
    catch ( string e ) {
        print( e );
    }
}


public Module loadModule( string filename )
{
    if ( !System.IO.File.Exists( filename ) ) {
        print( "File '" + filename + "' not found!" );
        return Module null;
    }

    var content = new Scanner( filename ).getText();
    // print( content );

    var reader = new JsonReader();

    return Module.FromJson( reader.parse( content ) );
}


public object Module
{
    public List<Dependency> Dependencies;
    public string           Name;
    public SemVer           Version;

    public static Module FromJson( JsonValue value )
    {
        if ( !value || !(value is JsonObject) ) {
            return Module null;
        }

        var data = JsonObject value;

        var module = new Module() {
            module.Dependencies = new List<Dependency>();
            module.Name         = data[ "name_short" ].asString();
            module.Version      = SemVer.FromString( data[ "version" ].asString() );

            if ( data.isMember( "dependencies" ) ) {
                var arr const = JsonArray data[ "dependencies" ];

                foreach ( JsonValue d : arr ) {
                    module.Dependencies.push_back( Dependency.FromJson( d ) );
                }
            }
        }

        return module;
    }

    public string =operator( string ) const {
        string dependencies;

        foreach ( Dependency d : Dependencies ) {
            dependencies += "{ "
                + d.Name + ": " + cast<string>( d.VersionMin ) + "-" + cast<string>( d.VersionMax )
                + " }";
        }

        return Name + ":" + cast<string>( Version ) + " [" + dependencies + "]";
    }
}

public object Dependency
{
    public string Name;
    public SemVer VersionMax;
    public SemVer VersionMin;

    public string =operator( string ) const {
        return "";
    }

    public static Dependency FromJson( JsonValue value )
    {
        if ( !value || !(value is JsonObject) ) {
            return Dependency null;
        }

        var data = JsonObject value;

        var dependency = new Dependency() {
            dependency.Name = data[ "module" ].asString();

            if ( data.isMember( "version_max" ) )
                dependency.VersionMax = SemVer.FromString( data[ "version_max" ].asString() );

            if ( data.isMember( "version_min" ) )
                dependency.VersionMin = SemVer.FromString( data[ "version_min" ].asString() );
        }

        return dependency;
    }
}

