
// library imports

// project imports
import Position;


public enum JobState {
	New = 1,
	Started,
	Done,
	Cancelled;
}

public enum JobType {
	Park = 1,
	Get,
	Put,
	Wait;
}

public object Job {
    public int jobID;
    public JobType typeID;
    public int levelID;
    public int orderID;
    public Position position;
    public int sequence;
    public int shuttleID;
    public JobState stateID;

    // For testing only - begin
    public int endTime;
    public int startTime;
    // For testing only - end;

    public void Constructor() {
        position = new Position();
    }

    public string =operator(string) const {
        return "Job { jobID: " + jobID +
                ", typeID: " + cast<string>( typeID ) +
                ", stateID: " + cast<string>( stateID ) +
                ", shuttleID: " + shuttleID +
                ", orderID: " + orderID +
                ", position: " + cast<string>(position) +
                ", sequence: " + sequence +
                ", startTime: " + startTime +
                ", endTime: " + endTime +
                " }";
    }
}

