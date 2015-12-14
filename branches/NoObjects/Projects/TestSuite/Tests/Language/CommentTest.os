#!/usr/local/bin/oscript

public namespace
{
	public object Main
	{
		public void Main(Number argc = 0, String argv = "")
		{
			test_comments();
		}

		public void test_comments(/*number param1*/)
		{
			//this is a single line comment
			// this is another single line comment
			/*this is a multi
				line comment*/
			/* this is another multi
				line comment */
			/*
			print("this will not be executed");
			*/
			print("this is /* not */ a comment");
		}
	}
}
