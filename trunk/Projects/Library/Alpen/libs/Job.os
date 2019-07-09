
// library imports

// project imports


public enum JobState {
	New = 1,
	Started,
	Done,
	Cancelled;
}

public enum JobType {
	Unkown = 0,
	Park, 
	Get,
	Put;
}

public object Job {
    public int jobID;
    public JobType jobTypeID;
    public int levelID;
    public int orderID;
    public int positionID;
    public int sequence;
    public int shuttleID;
    public JobState stateID;

    public string =operator(string) const {
        return "Job { jobID: " + jobID +
                ", jobTypeID: " + cast<string>( jobTypeID ) +
                ", stateID: " + cast<string>( stateID ) +
                ", shuttleID: " + shuttleID +
                ", orderID: " + orderID +
                ", levelID: " + levelID +
                ", positionID: " + positionID +
                ", sequence: " + sequence +
                " }";
    }
}

