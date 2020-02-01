
// library imports
import libLog.Logger;
import System.Collections.Map;

// project imports
import Path;
import Shuttle;
import Storage;


public object PathFinder {
    public void Constructor(ILogger logger /*, GraphStorage storage*/) {
        mLogger = new Logger(logger, "PathFinder");
        mPaths = new Map<Shuttle, Path>();
/*
        mStorage = storage;

        if ( !mStorage.dataIsLoaded() ) {
            mStorage.load();
        }
*/
    }

    public Path findGenericPath(Position start, Position end) modify {
        mLogger.info("findGenericPath(" + cast<string>(start) + ", " + cast<string>(end) + ")");

        return new Path(start, end);
    }

    public Path findPathForShuttle(Shuttle shuttle, Position end) modify {
        mLogger.info("findPathForShuttle(" + cast<string>(shuttle.position) + ", " + cast<string>(end) + ")");

        var path = new Path(shuttle.position, end);

        if ( mPaths.contains(shuttle) ) {
            mPaths.remove(shuttle);
            mPaths.insert(shuttle, path);
        }

        return path;
    }

    private Logger mLogger;
    private Map<Shuttle, Path> mPaths;
    //private GraphStorage mStorage;
}
