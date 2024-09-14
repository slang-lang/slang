
// library imports
import System.Collections.Vector;

// project imports


public enum PortType {
    Input,
    Output;
}

public object PortValue {
    public string Type;
    public string Value;
}

public abstract object Port {
    public string Name const;
    public PortType Type const;
    public PortValue Value;

    public void Constructor( PortType type, string name ) {
        Name = name;
        Type = type;
    }

    public bool operator==( string type ) const {
        if ( Value ) {
            return Value.Type == type;
        }

        return false;
    }
}

public object InputPort extends Port {
    public void Constructor( string name ) {
        base.Constructor( PortType.Input, name );
    }
}

public object OutputPort extends Port {
    public void Constructor( string name ) {
        base.Constructor( PortType.Output, name );
    }
}

public object PortCollection extends Vector<Port>;

