
// Library imports
import System.IO.File;

// Project imports
import _config_.Config;
import EntityLookup;


public object CodeExporter {
    public void process() modify throws {
        // connect to database
        connect();

        mEntityLookup = new EntityLookup( mDatabaseHandle, Config.Database );
        mEntityLookup.fetchEntities();

        // prepare output folders for lookups, tables and views
        prepareFolders();

        // export files for all functions
        exportFunctions();

        // export files for all procedure
        exportProcedures();

        // export files for all tables
        exportTables();

        // export files for all views
        exportViews();

        // disconnect from database
        disconnect();
    }

    private void connect() modify throws {
        mDatabaseHandle = mysql_init();
        mDatabaseHandle = mysql_real_connect( mDatabaseHandle, Config.Host, cast<int>( Config.Port ), Config.User, Config.Password, Config.Database );

        if ( !mDatabaseHandle ) {
            throw "failed to connect to database '" + Config.Database + "'";
        }
    }

    private void disconnect() modify throws {
        mysql_close( mDatabaseHandle );
    }

    private void exportFunctions() modify throws {
        var entities = mEntityLookup.getFunctions();

        int count;
        foreach ( string entity : entities ) {
            var query = "SHOW CREATE FUNCTION " + entity;

            var error = mysql_query( mDatabaseHandle, query );
            if ( error ) {
                throw mysql_error( mDatabaseHandle );
            }

            var result = mysql_store_result( mDatabaseHandle );
            if ( mysql_fetch_row( result ) ) {
                var content = mysql_get_field_value( result, "Create Function" );

                var outFile = new System.IO.File( Config.TargetDirectory + "/functions/" + entity + ".sql", System.IO.File.AccessMode.WriteOnly );
                outFile.write( content + ";" );
                outFile.close();
            }

            count++;
        }

        print( "" + count + " functions exported." );
    }

    private void exportProcedures() modify throws {
        var entities = mEntityLookup.getProcedures();

        int count;
        foreach ( string entity : entities ) {
            var query = "SHOW CREATE PROCEDURE " + entity;

            var error = mysql_query( mDatabaseHandle, query );
            if ( error ) {
                throw mysql_error( mDatabaseHandle );
            }

            var result = mysql_store_result( mDatabaseHandle );
            if ( mysql_fetch_row( result ) ) {
                var content = mysql_get_field_value( result, "Create Procedure" );

                var outFile = new System.IO.File( Config.TargetDirectory + "/procedures/" + entity + ".sql", System.IO.File.AccessMode.WriteOnly );
                outFile.write( content + ";" );
                outFile.close();
            }

            count++;
        }

        print( "" + count + " procedures exported." );
    }

    private void exportTables() modify throws {
        var entities = mEntityLookup.getTables();

        int count;
        foreach ( Pair<string, EntityType> entity : entities ) {
            var query = "SHOW CREATE TABLE " + entity.first;

            var error = mysql_query( mDatabaseHandle, query );
            if ( error ) {
                throw mysql_error( mDatabaseHandle );
            }

            var result = mysql_store_result( mDatabaseHandle );
            if ( mysql_fetch_row( result ) ) {
                var content = mysql_get_field_value( result, 1 );

                var outFile = new System.IO.File( Config.TargetDirectory + "/tables/" + entity.first + ".sql", System.IO.File.AccessMode.WriteOnly );
                outFile.write( content + ";" );
                outFile.close();
            }

            count++;
        }

        print( "" + count + " tables exported." );
    }

    private void exportViews() modify throws {
        var entities = mEntityLookup.getViews();

        int count;
        foreach ( Pair<string, EntityType> entity : entities ) {
            var query = "SHOW CREATE TABLE " + entity.first;

            var error = mysql_query( mDatabaseHandle, query );
            if ( error ) {
                throw mysql_error( mDatabaseHandle );
            }

            var result = mysql_store_result( mDatabaseHandle );
            if ( mysql_fetch_row( result ) ) {
                var content = mysql_get_field_value( result, 1 );

                var outFile = new System.IO.File( Config.TargetDirectory + "/views/" + entity.first + ".sql", System.IO.File.AccessMode.WriteOnly );
                outFile.write( content + ";" );
                outFile.close();
            }

            count++;
        }

        print( "" + count + " views exported." );
    }

    private void prepareFolders() modify {
        system( "mkdir -p " + Config.TargetDirectory + "/functions" );
        system( "mkdir -p " + Config.TargetDirectory + "/procedures" );
        system( "mkdir -p " + Config.TargetDirectory + "/tables" );
        system( "mkdir -p " + Config.TargetDirectory + "/views" );
    }

    private int mDatabaseHandle;
    private EntityLookup mEntityLookup;
}

