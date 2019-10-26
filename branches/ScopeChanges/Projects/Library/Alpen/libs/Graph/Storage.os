
// library imports
import libLog.Logger;
import System.Collections.List;

// project imports
import Edge;
import Node;


public object GraphStorage {
	public void Constructor(ILogger logger) {
		mDataLoaded = false;
		mEdges = new List<Edge>();
		mLogger = new Logger(logger, "GraphStorage");
		mNodes = new List<Node>();
	}

	public bool dataIsLoaded() const {
		return mDataLoaded;
	}

	public List<Edge> getEdges() const {
		return mEdges;
	}

	public List<Node> getNodes() const {
		return mNodes;
	}

	public void load() modify {
		mLogger.info("Loading graph data...");

		loadNodes();
		loadEdges();

		mLogger.info("Done loading graph data.");

		mDataLoaded = true;
	}

	private void loadEdges() modify {
	}

	private void loadNodes() modify {
	}

	private bool mDataLoaded;
	private List<Edge> mEdges;
	private Logger mLogger;
	private List<Node> mNodes;
}

