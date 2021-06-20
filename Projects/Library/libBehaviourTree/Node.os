
// library imports
import System.Collections.Vector;

// project imports
import Port;


public enum NodeStatus {
    Success,        // execution finished successfully
    Running,        // will not be used in a single threaded environment
    Waiting,        // Running but waiting for additional input (to emulate a multithreaded environment)
    Failure;        // execution failed
}

public enum NodeType {
    Action,         // node is a leaf and thus can perform an action
    Condition,      //
    Control,        // 1-n childs, example sequence, fallback, etc.
    Decorator;      // only 1 child, create your own decorators like repeaters, inverters, etc.
}

public abstract object Node {
    public string Name const;
    public PortCollection Ports;
    public NodeStatus Status;
    public NodeType Type const;

    public void Constructor( NodeType type, string name ) {
        Name = name;
        Ports = new PortCollection();
        Type = type;
    }

    public PortCollection providedPorts() const {
        return Ports;
    }

    public abstract void print();
    public abstract NodeStatus tick() modify;
}

public object NodeCollection extends Vector<Node>;
