
// library imports
import System.Collections.Map;
import System.Exception;

// project imports
import Expressions;
import Statements;
import SymbolTable;


public enum ControlFlow {
        Break,
        Continue,
        Exit,
        Normal,
        Return;
}


public object RuntimeException const implements IException {
    public void Constructor(string msg) {
        mMessage = msg;
    }

    public string what() const {
        return mMessage;
    }

    private string mMessage const;
}


public object Interpreter {
    public void Constructor(Statement program) {
         mConstants = new Map<string, String>();
         mProgram = program;
    }

    public int run(bool debug = false) modify throws {
        if ( !mProgram ) {
            return -1;
        }

        if ( debug ) {
           print("Interpreting \"" + (ProgramStatement mProgram).mName + "\"...");
        }

        mControlFlow = ControlFlow.Normal;
        mCurrentScope = new SymbolTable("global");

        visitCompoundStatement((ProgramStatement mProgram).mStatements);

        delete mCurrentScope;

        return 0;
    }

    private string processBinaryExpression(BinaryExpression exp) modify throws {
        string left = processExpression(exp.mLeft);
        string right = processExpression(exp.mRight);

        switch ( exp.mOperator ) {
			// arithmetic operators
			case "DIV": {
				return cast<string>( cast<int>( left ) / cast<int>( right ) );
			}
			case "+": {
				if ( exp.mLeft.mResultType == "STRING" ) {
					return left + right;
				}
				return cast<string>( cast<float>( left ) + cast<float>( right ) );
			}
			case "-": {
				return cast<string>( cast<float>( left ) - cast<float>( right ) );
			}
			case "*": {
				return cast<string>( cast<float>( left ) * cast<float>( right ) );
			}
			case "/": {
				return cast<string>( cast<float>( left ) / cast<float>( right ) );
			}
			case "%": {
				return cast<string>( cast<int>( left ) % cast<int>( right ) );
			}
        }

        throw new RuntimeException("invalid binary operator '" + exp.mOperator + "'!");
    }

    private bool processBooleanBinaryExpression(BooleanBinaryExpression exp) modify throws {
        string left = processExpression(exp.mLeft);
        string right = processExpression(exp.mRight);

        switch ( exp.mOperator ) {
            case "AND": { return cast<float>( left ) && cast<float>( right ); }
            case "OR" : { return cast<float>( left ) || cast<float>( right ); }
            case "="  : { return left == right; }
            case "<"  : { return cast<float>( left ) < cast<float>( right ); }
            case "<=" : { return cast<float>( left ) <= cast<float>( right ); }
            case ">"  : { return cast<float>( left ) > cast<float>( right ); }
            case ">=" : { return cast<float>( left ) >= cast<float>( right ); }
            case "<>" : { return left != right; }
        }

        throw new RuntimeException("invalid binary operator '" + exp.mOperator + "'!");
    }

    private string processConstantExpression(ConstantExpression exp) const throws {
        string name = exp.mConstant;

        var sym = mCurrentScope.lookup(name);
        //var sym = mCurrentScope.at( exp.mStackIndex );
        if ( !sym ) {
            throw new RuntimeException("Symbol '" + name + "' is unknown");
        }

        return cast<string>( (LocalSymbol sym).mValue );
    }

    private string processExpression(Expression exp) modify throws {
        switch ( exp.mExpressionType ) {
            case ExpressionType.BinaryExpression: {
                return processBinaryExpression(BinaryExpression exp);
            }
            case ExpressionType.BooleanBinaryExpression: {
                return cast<string>( processBooleanBinaryExpression(BooleanBinaryExpression exp) );
            }
            case ExpressionType.ConstantExpression: {
                return cast<string>( processConstantExpression(ConstantExpression exp) );
            }
            case ExpressionType.LiteralBooleanExpression: {
                return cast<string>( processLiteralBooleanExpression(LiteralBooleanExpression exp) );
            }
            case ExpressionType.LiteralIntegerExpression: {
                return cast<string>( processLiteralIntegerExpression(LiteralIntegerExpression exp) );
            }
            case ExpressionType.LiteralRealExpression: {
                return cast<string>( processLiteralRealExpression(LiteralRealExpression exp) );
            }
            case ExpressionType.LiteralStringExpression: {
                return processLiteralStringExpression(LiteralStringExpression exp);
            }
            case ExpressionType.MethodExpression: {
                return processMethodExpression(MethodExpression exp);
            }
            case ExpressionType.UnaryExpression: {
                return processUnaryExpression(UnaryExpression exp);
            }
            case ExpressionType.VariableExpression: {
                return processVariableExpression(VariableExpression exp);
            }
            default: {
                throw new RuntimeException("invalid expression type '" + typeid(exp) + "'!");
            }
        }
    }

    private bool processLiteralBooleanExpression(LiteralBooleanExpression exp) const {
        return exp.mValue;
    }

    private int processLiteralIntegerExpression(LiteralIntegerExpression exp) const {
        return exp.mValue;
    }

    private float processLiteralRealExpression(LiteralRealExpression exp) const {
        return exp.mValue;
    }

    private string processLiteralStringExpression(LiteralStringExpression exp) const {
        return exp.mValue;
    }

    private string processMethodExpression(MethodExpression exp) modify {
        var oldScope = mCurrentScope;
        mCurrentScope = new SymbolTable(exp.mMethod.mName, oldScope);

        if ( exp.mParameters && exp.mMethod.mParameters ) {
            // add symbols for parameters
            var paramIt = exp.mParameters.getIterator();
            var sigIt = exp.mMethod.mParameters.getIterator();
            while ( paramIt.hasNext() && sigIt.hasNext() ) {
                paramIt.next();
                sigIt.next();

                string symName = sigIt.current().mName;
                string symType = sigIt.current().mType;
                String symValue = new String( processExpression(paramIt.current()) );

                mCurrentScope.declare(cast<Symbol>( new LocalSymbol(symName, mCurrentScope.size(), symType, false, symValue) ));
            }
        }

        var result = new LocalSymbol("RESULT", mCurrentScope.size(), exp.mResultType, false, new String());
        mCurrentScope.declare(Symbol result);

        // reset control flow to normal to allow method execution
        mControlFlow = ControlFlow.Normal;

        visitCompoundStatement(exp.mMethod.mBody);

        // reset control flow to normal after method execution
        mControlFlow = ControlFlow.Normal;

        var resultValue = cast<string>( result.mValue );
        mCurrentScope = oldScope;

        return resultValue;
    }

    private string processUnaryExpression(UnaryExpression exp) modify throws {
        switch ( exp.mOperator ) {
            case "+": {
                return processExpression(exp.mExpression);
            }
            case "-": {
                return "-" + processExpression(exp.mExpression);
            }
        }

        throw new RuntimeException("invalid unary operator '" + exp.mOperator + "'!");
    }

    private string processVariableExpression(VariableExpression exp) const throws {
        string name = exp.mVariable;

        var sym = mCurrentScope.lookup(name);
        //var sym = mCurrentScope.at( exp.mStackIndex );
        if ( !sym ) {
            throw new RuntimeException("Symbol '" + name + "' is unknown");
        }

        return cast<string>( (LocalSymbol sym).mValue );
    }

    private void visit(Node node) modify throws {
        if ( !node ) {
            return;
        }

        switch ( node.mNodeType ) {
            case NodeType.ExpressionNode: {
                processExpression(Expression node);
                break;
            }
            case NodeType.OperatorNode: {
                throw new RuntimeException("cannot process operator nodes");
            }
            case NodeType.StatementNode: {
                visitStatement(Statement node);
                break;
            }
        }
    }

    private void visitAssignStatement(AssignmentStatement assign) modify throws {
        string name = (VariableExpression assign.mLeft).mVariable;

        var sym = mCurrentScope.lookup(name);
        //var sym = mCurrentScope.at((VariableExpression assign.mLeft).mStackIndex);
        if ( !sym ) {
            throw new RuntimeException("Symbol '" + name + "' is unknown");
        }
        if ( !(sym is LocalSymbol) ) {
            throw new RuntimeException("Symbol '" + name + "' is not of type LocalSymbol");
        }
        if ( (LocalSymbol sym).mIsConst ) {
            throw new RuntimeException("Symbol '" + name + "' is const");
        }

        var obj = (LocalSymbol sym).mValue;
        obj = processExpression(assign.mRight);
    }

    private void visitBreakStatement(BreakStatement stmt) modify throws {
        mControlFlow = ControlFlow.Break;
    }

    private void visitCaseStatement(CaseStatement stmt) modify throws {
        string caseValue = processExpression(stmt.mExpression);

        foreach ( CasePart part : stmt.mCaseParts ) {
            foreach ( Expression exp : part.mExpressions ) {
                string expValue = processExpression(exp);

                if ( expValue == caseValue ) {
                    visitStatement(part.mStatement);
                    return;
                }
            }
        }

        if ( stmt.mElseStatement ) {
            visitStatement(stmt.mElseStatement);
        }
    }

    protected void visitCompoundStatement(CompoundStatement compound) modify throws {
        var oldScope = mCurrentScope;

        try {
            if ( compound.mConstantDeclarations || compound.mVariableDeclarations ) {
                mCurrentScope = new SymbolTable("", oldScope);
            }

            if ( compound.mConstantDeclarations ) {
                visitConstantDeclarationStatement(compound.mConstantDeclarations);
            }

            if ( compound.mVariableDeclarations ) {
                visitVariableDeclarationStatement(compound.mVariableDeclarations);
            }

            foreach ( Statement stmt : compound.mStatements ) {
                visitStatement(stmt);

                if ( mControlFlow != ControlFlow.Normal ) {
                    break;
                }
            }
        }
        finally {
            mCurrentScope = oldScope;
        }
    }

    protected void visitConstantDeclarationStatement(ConstantDeclarationStatement stmt) modify throws {
        foreach ( DeclarationStatement declStmt : stmt.mDeclarations ) {
            string name = declStmt.mName;

            if ( mCurrentScope.lookup(name, true) ) {
                throw new RuntimeException("duplicate symbol '" + name + "' declared");
            }

            var obj = new String("0");
            mCurrentScope.declare(Symbol new LocalSymbol(name, mCurrentScope.size(), declStmt.mType, true, obj));

            if ( declStmt.mValue ) {
                obj = processExpression(declStmt.mValue);
            }
        }
    }

    private void visitContinueStatement(ContinueStatement stmt) modify throws {
        mControlFlow = ControlFlow.Continue;
    }

    private void visitExitStatement(ExitStatement stmt) modify throws {
        var sym = mCurrentScope.lookup("RESULT");
        if ( !sym ) {
            throw new RuntimeException("Symbol 'RESULT' is unknown");
        }
        if ( !(sym is LocalSymbol) ) {
            throw new RuntimeException("Symbol 'RESULT' is not of type LocalSymbol");
        }
        if ( (LocalSymbol sym).mIsConst ) {
            throw new RuntimeException("Symbol 'RESULT' is const");
        }

        var obj = (LocalSymbol sym).mValue;
        obj = processExpression(stmt.mReturnValue);

        mControlFlow = ControlFlow.Return;
    }

    private void visitForStatement(ForStatement stmt) modify throws {
        var sym = mCurrentScope.lookup(stmt.mLoopVariable.mVariable);
        if ( !sym || !(LocalSymbol sym) ) {
            throw new RuntimeException("invalid symbol '" + stmt.mLoopVariable.mVariable + "'");
        }

        var obj = (LocalSymbol sym).mValue;
        obj = processExpression(stmt.mStartExpression);

        while ( processExpression(stmt.mTargetExpression) == "1" ) {
            visitStatement(stmt.mBody);

            switch ( mControlFlow ) {
                case ControlFlow.Break: { mControlFlow = ControlFlow.Normal; return; }
                case ControlFlow.Continue: { mControlFlow = ControlFlow.Normal; break; }
                case ControlFlow.Exit: { return; }
                case ControlFlow.Normal: { break; }
                case ControlFlow.Return: { return; }
            }

            obj = processExpression(stmt.mStepExpression);
        }
    }

    private void visitIfStatement(IfStatement stmt) modify {
        var condition = processExpression(stmt.mCondition);

        if ( condition == "1" ) {
            visitStatement(stmt.mIfBlock);
        }
        else if ( stmt.mElseBlock ) {
            visitStatement(stmt.mElseBlock);
        }
    }

    private void visitMethodStatement(MethodCallStatement stmt) modify throws {
        var oldScope = mCurrentScope;
        mCurrentScope = new SymbolTable(stmt.mName, oldScope);

        if ( stmt.mParameters && stmt.mMethod.mParameters ) {
            // add symbols for parameters
            var paramIt = stmt.mParameters.getIterator();
            var sigIt = stmt.mMethod.mParameters.getIterator();
            while ( paramIt.hasNext() && sigIt.hasNext() ) {
                paramIt.next();
                sigIt.next();

                string symName = sigIt.current().mName;
                string symType = sigIt.current().mType;
                String symValue = new String( processExpression(paramIt.current()) );

                mCurrentScope.declare(Symbol new LocalSymbol(symName, mCurrentScope.size(), symType, false, symValue));
            }
        }

        // reset control flow to normal to allow method execution
	mControlFlow = ControlFlow.Normal;

        visitCompoundStatement(stmt.mMethod.mBody);

        // reset control flow to normal after method execution
	mControlFlow = ControlFlow.Normal;
        mCurrentScope = oldScope;
    }

    private void visitReadlineStatement(ReadlineStatement stmt) modify throws {
        var sym = mCurrentScope.lookup(stmt.mVariable.mVariable);
        if ( !sym || !(sym is LocalSymbol) ) {
            throw new RuntimeException("invalid symbol '" + stmt.mVariable.mVariable + "'");
        }

        var obj = (LocalSymbol sym).mValue;
        obj = cin();
    }

    private void visitRepeatStatement(RepeatStatement repeatStmt) modify throws {
        while ( mControlFlow == ControlFlow.Normal ) {
            foreach ( Statement stmt : repeatStmt.mStatements ) {
                visitStatement(stmt);

                if ( mControlFlow != ControlFlow.Normal ) {
                    break;
                }
            }

            switch ( mControlFlow ) {
                case ControlFlow.Break: { mControlFlow = ControlFlow.Normal; return; }
                case ControlFlow.Continue: { mControlFlow = ControlFlow.Normal; break; }
                case ControlFlow.Exit: { return; }
                case ControlFlow.Normal: { break; }
                case ControlFlow.Return: { return; }
            }

            var condition = processExpression( repeatStmt.mCondition );
            if ( condition == "1" ) {
                break;
            }
        }
    }

    private void visitWriteStatement(WriteStatement stmt) modify {
        cout( processExpression(stmt.mExpression) );
        if ( stmt.mLineBreak ) {
            endl();
        }
    }

    protected void visitStatement(Statement stmt) modify throws {
        if ( !stmt ) {
            return;
        }

        switch ( stmt.mStatementType ) {
            case StatementType.AssignmentStatement: {
                visitAssignStatement(AssignmentStatement stmt);
                break;
            }
            case StatementType.BreakStatement: {
                visitBreakStatement(BreakStatement stmt);
                break;
            }
            case StatementType.CaseStatement: {
                visitCaseStatement(CaseStatement stmt);
                break;
            }
            case StatementType.CompoundStatement: {
                visitCompoundStatement(CompoundStatement stmt);
                break;
            }
            case StatementType.ConstantDeclarationStatement: {
                throw new RuntimeException("inline constant declarations are not allowed");
            }
            case StatementType.ContinueStatement: {
                visitContinueStatement(ContinueStatement stmt);
                break;
            }
            case StatementType.ExitStatement: {
                visitExitStatement(ExitStatement stmt);
                break;
            }
            case StatementType.ForStatement: {
                visitForStatement(ForStatement stmt);
                break;
            }
            case StatementType.IfStatement: {
                visitIfStatement(IfStatement stmt);
                break;
            }
            case StatementType.MethodCallStatement: {
                 visitMethodStatement(MethodCallStatement stmt);
                 break;
            }
            case StatementType.ReadlineStatement: {
                 visitReadlineStatement(ReadlineStatement stmt);
                 break;
            }
            case StatementType.RepeatStatement: {
                 visitRepeatStatement(RepeatStatement stmt);
                 break;
            }
            case StatementType.VariableDeclarationStatement: {
                throw new RuntimeException("inline variable declarations are not allowed");
            }
            case StatementType.WhileStatement: {
                visitWhileStatement(WhileStatement stmt);
                break;
            }
            case StatementType.WriteStatement: {
                visitWriteStatement(WriteStatement stmt);
                break;
            }
            default: {
                throw new RuntimeException("invalid statement type(" + (string stmt.mStatementType) + ") detected!");
            }
        }
    }

    protected void visitVariableDeclarationStatement(VariableDeclarationStatement stmt) modify throws {
        foreach ( DeclarationStatement declStmt : stmt.mDeclarations ) {
            string name = declStmt.mName;
            if ( mCurrentScope.lookup(name, true) ) {
                throw new RuntimeException("duplicate symbol '" + name + "' declared");
            }

            var obj = new String("0");
            mCurrentScope.declare(Symbol new LocalSymbol(name, mCurrentScope.size(), declStmt.mType, false, obj));

            if ( declStmt.mValue ) {
                obj = processExpression(declStmt.mValue);
            }
        }
    }

    private void visitWhileStatement(WhileStatement stmt) modify throws {
        while ( mControlFlow == ControlFlow.Normal ) {
            var condition = processExpression( stmt.mCondition );
            if ( condition != "1" ) {
                break;
            }

            visitStatement( stmt.mBody );

            switch ( mControlFlow ) {
                case ControlFlow.Break: { mControlFlow = ControlFlow.Normal; return; }
                case ControlFlow.Continue: { mControlFlow = ControlFlow.Normal; break; }
                case ControlFlow.Exit: { return; }
                case ControlFlow.Normal: { break; }
                case ControlFlow.Return: { return; }
            }
        }
    }

    protected ControlFlow mControlFlow;
    protected SymbolTable mCurrentScope;
    protected Map<string, String> mConstants;
    protected Statement mProgram;
}

