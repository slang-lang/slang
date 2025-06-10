
public object MsgQueue const
{
    public void Constructor( int queueID, bool isOwner = false )
    {
        Owner   = isOwner;
        QueueID = queueID;

        Handle = msgget( QueueID, Owner );
    }

    public void Destructor()
    {
        if ( Handle ) {
            Handle = msgctl( Handle );
        }
    }

    public bool IsOpen() const
    {
        return Handle != 0;
    }

    public string Receive( bool waitForMessage = false ) const
    {
		return msgrcv( Handle, waitForMessage );
    }

    public bool Send( string message ) const
    {
		return msgsnd( Handle, message ) != -1;
    }

    private int Handle const;
    private bool Owner const;
    private int QueueID const;
}
