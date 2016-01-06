
public object ContainerObserver
{
	protected number mIndex;
	protected number mSize;

	public void ContainerObserver() {
		mIndex = 0;
		mSize = 0;
	}

	public void ~ContainerObserver() {
	}

	public bool empty() const {
		return mSize == 0;
	}

	public bool hasNext() const {
		return (mIndex + 1) < mSize;
	}

	public bool hasPrevious() const {
		return (mIndex - 1) > 0;
	}

	public void iterateNext() {
		//mIndex += 1;
		mIndex = mIndex + 1;
	}

	public void iteratePrevious() {
		//mIndex -= 1;
		mIndex = mIndex - 1;
	}

	public number size() const {
		return mSize;
	}
}

public prototype List //extends public ContainerObserver
{
	private UNKNOWN mData[];
	private UNKNOWN mFirst;
	private UNKNOWN mLast;

	public void List() {
		mFirst = UNKNOWN();
		mLast = UNKNOWN();
	}

	public UNKNOWN at(number index) {
		if ( index < mSize ) {
			return mData[index];
		}

		assert(!"index out of range");
		return UNKNOWN();
	}

	public void push_back(UNKNOWN t) {
		mLast = t;
	}
	
	public void push_front(UNKNOWN t) {
		mFirst = t;
	}

	public void pop_back() {
	}
	
	public void pop_front() {
	}
}


private object Main
{
	public void Main() {
		List of number numbers;

		numbers.push_back(1);
		numbers.push_back(2);

		print("numbers.size() = " + numbers.size());

		number num1 = numbers.at(1);
		print("num1 = " + num1);

		numbers.pop_back();
		print("numbers.size() = " + numbers.size());
	}
}

