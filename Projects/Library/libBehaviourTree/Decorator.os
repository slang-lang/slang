
import Node;

public abstract object Decorator extends Node {
    public Node Child;

    public void Constructor( string name = "Decorator" ) {
        base.Constructor( NodeType.Decorator, name );
    }

    public void print() {
        print( Name + " has " + ( Child ? "1" : "0" ) + " child(s)" );

        if( Child ) {
            Child.print();
        }
    }

    public void pushChild( Node child ) modify {
        print( Name + ": push child: " + typeid( child ) );

        Child = child;
    }

    public abstract NodeStatus tick() modify;
}

public object ForceFailureDecorator extends Decorator {
    public void Constructor( string name = "ForceFailureDecorator" ) {
        base.Constructor( NodeType.Decorator, name );
    }

    public override NodeStatus tick() modify {
        print( "ForceFailureDecorator: " + Name );

        if ( Status == NodeStatus.Running || Status == NodeStatus.Waiting ) {
            return Status;
        }

        return NodeStatus.Failure;
    }
}

public object ForceSuccessDecorator extends Decorator {
    public void Constructor( string name = "ForceSuccessDecorator" ) {
        base.Constructor( NodeType.Decorator, name );
    }

    public override NodeStatus tick() modify {
        print( "ForceSuccessDecorator: " + Name );

        if ( Status == NodeStatus.Running || Status == NodeStatus.Waiting ) {
            return Status;
        }

        return NodeStatus.Success;
    }
}

public object InverterDecorator extends Decorator {
    public void Constructor( string name = "InverterDecorator" ) {
        base.Constructor( NodeType.Decorator, name );
    }

    public override NodeStatus tick() modify {
        print( "InverterDecorator: " + Name );

        Status = Child.tick();

        if ( Status == NodeStatus.Running || Status == NodeStatus.Waiting ) {
            return Status;
        }

        if ( Status == NodeStatus.Failure ) {
            return NodeStatus.Success;
        }

        return NodeStatus.Failure;
    }
}

public object RepeaterDecorator extends Decorator {
    public void Constructor( string name = "RepeaterDecorator" ) {
        base.Constructor( NodeType.Decorator, name );
    }

    public override NodeStatus tick() modify {
        print( "RepeaterDecorator: " + Name );

        if ( Status == NodeStatus.Running || Status == NodeStatus.Waiting ) {
            return Status;
        }


    }
}
