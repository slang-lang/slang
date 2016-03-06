#!/usr/local/bin/oscript

//import System;

public namespace StackTest
{
	private object Node
	{
		private Node _next;
		private number _value;

		public void Node()
		{
		}

		public void Node(number value)
		{
			_value = value;
		}

		public void Node(number value, Node node)
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

		public bool empty() const
		{
			return (first);
		}

		public number pop()
		{
			if ( first ) {
				Node temp = first.value;
				first = first.Next;
				return temp;
			}
			else {
				throw;
			}
		}

		public void push(number value) modify
		{
			first = new Node(value, first);
		}
	}

	public object Main
	{
		public void Main(number argc = 0, string argv = "")
		{
			Stack stack = new Stack();
			
			for ( number bla = 0; bla < 10; bla = bla + 1 ) {
				stack.push(bla);
			}
			
			delete stack;
		}
	}
}
