#!/usr/local/bin/oscript

import System.Collections.AbstractCollection;
import System.Collections.IIterateable;
import System.Collections.Iterator;
import System.Exception;
import System.String;

// helper Node class
private object Node {
    public String item;
    public Node next;
}

public object StringStackIterator extends Iterator {
    private Node mCurrent;
    private Node mFirst;

    public void Constructor(Node first ref) {
        mFirst = first;

        mCurrent = mFirst;
    }

    public String current() const {
        return mCurrent.item;
    }

    public bool hasNext() const {
        return bool mCurrent.next;
    }

    public void next() modify throws {
        if ( !hasNext() ) {
            throw new OutOfBoundsException("index out of bounds");
        }

        mCurrent = mCurrent.next;
    }

    public void reset() modify {
        mCurrent = mFirst;
    }

    public String =operator(Object none ref) const {
        return current();
    }
}

public object LinkedStackOfStrings implements IIterateable {
    private int n;          // size of the stack
    private Node first;     // top of stack

    // is the stack empty?
    public bool isEmpty() {
        //return !first;
	return !n;
    }

    // number of elements on the stack
    public int size() {
        return n;
    }

    // peek at last element
    public String peek() throws {
        if ( isEmpty() ) {
            throw new Exception("Stack underflow");
        }

        return String first.item;
    }

    // add an element to the stack
    public void push(String item ref) modify {
        Node oldfirst = first;
        first = new Node();
        first.item = item;
        first.next = oldfirst;
        n++;
    }

    // delete and return the most recently added element
    public String pop() modify throws {
        if ( isEmpty() ) {
            throw new Exception("Stack underflow");
        }

        String item = first.item;      	// save item to return
        first = first.next;		// delete first node
        n--;
        return item;			// return the saved item
    }

	public StringStackIterator getIterator() const {
		return new StringStackIterator(first);
	}
}

