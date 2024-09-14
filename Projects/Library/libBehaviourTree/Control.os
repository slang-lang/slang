
import Node;

public abstract object Control extends Node {
    public NodeCollection Childs;

    public void Constructor( string name = "Control" ) {
        base.Constructor( NodeType.Control, name );

        Childs = new NodeCollection();
    }

    public void print() {
        print( Name + " has " + Childs.size() + " childs" );

        for ( int idx = 0; idx < Childs.size(); idx++ ) {
            var child = Childs.at( idx );

            child.print();
        }
    }

    public void pushChild( Node child ) modify {
        print( Name + ": push child: " + typeid( child ) );

        Childs.push_back( child );
    }

    public abstract NodeStatus tick() modify;
}

public object Fallback extends Control {
    public void Constructor( string name = "Fallback" ) {
        base.Constructor( name );
    }

    public override NodeStatus tick() modify {
        print( "Fallback: " + Name );

        Status = NodeStatus.Running;

        while ( Index < Childs.size() ) {
            var childStatus = Childs.at( Index ).tick();

            if ( childStatus == NodeStatus.Running || childStatus == NodeStatus.Waiting ) {
                print( "Fallback: Running or Waiting" );
                return childStatus;
            }
            else if ( childStatus == NodeStatus.Failure ) {
                print( "Fallback: Failure" );
                Index++;
            }
            else if ( childStatus == NodeStatus.Success ) {
                print( "Fallback: Success" );
                Index = 0;
                return NodeStatus.Success;
            }
        }

        print( "Fallback: Failure" );
        Index = 0;
        return NodeStatus.Failure;
    }

    private int Index = 0;
}

public object ReactiveFallback extends Fallback {
    public void Constructor( string name = "ReactiveFallback" ) {
        base.Constructor( name );
    }

    public override NodeStatus tick() modify {
        print( "ReactiveFallback: " + Name );

        Status = NodeStatus.Running;

        for ( int idx = 0; idx < Childs.size(); idx++ ) {
            var childStatus = Childs.at( idx ).tick();

            if ( childStatus == NodeStatus.Running || childStatus == NodeStatus.Waiting ) {
                print( "ReactiveFallback: Running or Waiting" );
                return childStatus;
            }
            else if ( childStatus == NodeStatus.Success ) {
                print( "ReactiveFallback: Success" );
                return NodeStatus.Success;
            }
        }

        print( "ReactiveFallback: Failure" );
        return NodeStatus.Failure;
    }
}

public object Sequence extends Control {
    public void Constructor( string name = "Sequence" ) {
        base.Constructor( name );
    }

    public override NodeStatus tick() modify {
        print( "Sequence: " + Name );

        Status = NodeStatus.Running;

        while ( Index < Childs.size() ) {
            //print( "Index: " + Index );

            var childStatus = Childs.at( Index ).tick();

            if ( childStatus == NodeStatus.Success ) {
                print( "Sequence: Success" );
                Index++;
            }
            else if ( childStatus == NodeStatus.Running || childStatus == NodeStatus.Waiting ) {
                print( "Sequence: Running or Waiting" );
                return childStatus;
            }
            else if ( childStatus == NodeStatus.Failure ) {
                print( "Sequence: Failure" );
                Index = 0;
                return NodeStatus.Failure;
            }
        }

        print( "Sequence: Success" );
        Index = 0;
        return NodeStatus.Success;
    }

    private int Index = 0;
}

public object ReactiveSequence extends Sequence {
    public void Constructor( string name = "ReactiveSequence" ) {
        base.Constructor( name );
    }

    public override NodeStatus tick() modify {
        print( "ReactiveSequence: " + Name );

        Status = NodeStatus.Running;

        for ( int idx = 0; idx < Childs.size(); idx++ ) {
            var childStatus = Childs.at( idx ).tick();

            if ( childStatus == NodeStatus.Running || childStatus == NodeStatus.Waiting ) {
                print( "ReactiveSequence: Running or Waiting" );
                return childStatus;
            }
            else if ( childStatus == NodeStatus.Failure ) {
                print( "ReactiveSequence: Failure" );
                return NodeStatus.Failure;
            }
        }

        print( "ReactiveSequence: Success" );
        return NodeStatus.Success;
    }
}

public object SequenceStar extends Sequence {
    public void Constructor( string name = "SequenceStar" ) {
        base.Constructor( name );
    }

    public override NodeStatus tick() modify {
        print( "SequenceStar: " + Name );

        Status = NodeStatus.Running;

        while ( Index < Childs.size() ) {
            var childStatus = Childs.at( Index ).tick();

            if ( childStatus == NodeStatus.Success ) {
                print( "SequenceStar: Success" );
                Index++;
            }
            else {
                print( "SequenceStar: Failure" );
                Index = 0;
                return NodeStatus.Failure;
            }
        }

        print( "SequenceStar: Success" );
        Index = 0;
        return NodeStatus.Success;
    }
}
