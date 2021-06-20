
import Nodes;

public object CloseFridge extends Action {
    public void Constructor() {
        base.Constructor( "Close fridge" );
    }

    public NodeStatus tick() modify {
        return NodeStatus.Success;
    }
}

public object GrabBeer extends Action {
    private int Value;

    public void Constructor( int value ) {
        base.Constructor( "Grab beer" );

        Value = value;
    }

    public NodeStatus tick() modify {
        if ( !Value ) {
            return NodeStatus.Failure;
        }

        return NodeStatus.Success;
    }
}

public object OpenFridge extends Action {
    public void Constructor() {
        base.Constructor( "Open fridge" );
    }

    public NodeStatus tick() modify {
        return NodeStatus.Success;
    }
}
