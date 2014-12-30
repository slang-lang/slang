
public object ContainerObserver
{
	protected Number mIndex;
	protected Number mSize;

	public Void ContainerObserver() {
		mIndex = 0;
		mSize = 0;
	}

	public Void ~ContainerObserver() {
	}

	public Bool empty() const {
		return mSize == 0;
	}

	public Bool hasNext() const {
		return mIndex + 1 < mSize;
	}

	public Bool hasPrevious() const {
		return mIndex - 1 > 0;
	}

	public Void iterateNext() {
		mIndex += 1;
	}

	public Void iteratePrevious() {
		mIndex -= 1;
	}

	public Number size() const {
		return mSize;
	}
}

public prototype List //extends public ContainerObserver
{
	private UNKNOWN mFirst;
	private UNKNOWN mLast;

	public Void List() {
		mFirst = UNKNOWN();
		mLast = UNKNOWN();
	}

	public UNKNOWN at(Number index) {
		if ( index < mSize ) {
			return mData[index];
		}

		assert(!"index out of range");
		return UNKNOWN();
	}

	public Void push_back(UNKNOWN t) {
		mLast = t;
	}
	
	public Void push_front(UNKNOWN t) {
		mFirst = t;
	}

	public Void pop_back() {
	}
	
	public Void pop_front() {
	}
}


private object Main
{
	public Void Main() {
		List of Number numbers;

		numbers.push_back(1);
		numbers.push_back(2);

		print("numbers.size() = " & numbers.size());

		Number num1 = numbers.at(1);
		print("num1 = " & num1);

		numbers.pop_back();
		print("numbers.size() = " & numbers.size());
	}
}