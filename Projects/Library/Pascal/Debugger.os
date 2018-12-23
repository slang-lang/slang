
// library imports

// project imports
import Interpreter;


public object Debugger extends Interpreter {
    public void Constructor(Statement program) {
        base.Constructor(program);
    }

    public int run() modify throws {
        if ( !mProgram ) {
            return -1;
        }

        print("Debugging \"" + (ProgramStatement mProgram).mName + "\"...");

        var compound = (ProgramStatement mProgram).mStatements;

        if ( compound.mConstantDeclarations ) {
            visitConstantDeclarationStatement(compound.mConstantDeclarations);
        }

        if ( compound.mVariableDeclarations ) {
            visitVariableDeclarationStatement(compound.mVariableDeclarations);
        }

        foreach ( Statement stmt : compound.mStatements ) {
            visitStatement(stmt);
        }

        return 0;
    }
}
