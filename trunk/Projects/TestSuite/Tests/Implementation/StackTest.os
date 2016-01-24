#!/usr/local/bin/oscript

//import System;

public namespace StackTest
{
	private object Node
	{
		public Node Next;
		public number Value;

		public void Node()
		{
		}

		public void Node(number value)
		{
			Value = value;
		}

		public void Node(number value, Node node)
		{
			Next = node;
			Value = value;
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
