

public abstract object Thread {
    public void Constructor(string name) {
        mName = name;

        start();
    }

    public string getName() const {
        return mName;
    }

    private void start() modify {
        // this method will be overwritten by deriving objects

        createThread( cast<Thread>(this) );
    }

    public void run() modify abstract;
/*
    public void run() modify {
        createThread( cast<Thread>(this) );
    }
*/

    private string mName;
}

