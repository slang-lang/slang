#!/usr/local/bin/oscript

import System.Exception;

public namespace StackTest
{
	private object Node
	{
		private Node _next;
		private int _value;

		public void Node()
		{
		}

		public void Node(int value)
		{
			_value = value;
		}

		public void Node(int value, Node node)
		{
			_next = node;
			_value = value;
		}
	}

	private object Stack
	{
		private Node first;

		public void Stack()
		{
		}

		public ~Stack()
		{
		}

		public bool empty() const
		{
			return first;
		}

		public int pop()
		{
			if ( first ) {
				Node temp = first.value;
				first = first.Next;
				return temp;
			}

			throw new Exception("cannot pop beyond first node");
		}

		public void push(int value) modify
		{
			first = new Node(value, first);
		}
	}

	public object Main
	{
		public void Main(int argc = 0, string argv = "")
		{
			Stack stack = new Stack();
			
			for ( int bla = 0; bla < 10; bla = bla + 1 ) {
				stack.push(bla);
			}
			
			delete stack;
		}
	}
}
