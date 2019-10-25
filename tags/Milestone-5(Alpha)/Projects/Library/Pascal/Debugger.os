
// library imports

// project imports
import Interpreter;


public object Debugger extends Interpreter {
    public void Constructor(Statement program) {
        base.Constructor(program);
    }

    public int run(bool debug = false) modify throws {
        if ( !mProgram ) {
            return -1;
        }

	    if ( debug ) {
	        print("Debugging \"" + (ProgramStatement mProgram).mName + "\"...");
	    }

        mCurrentScope = new SymbolTable("global");

        visitCompoundStatement((ProgramStatement mProgram).mStatements);

        delete mCurrentScope;

        return 0;
    }
}
