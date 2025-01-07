package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Adt.MyIStack;
import Model.Expressions.IExpression;
import Model.ProgramState.ProgramState;
import Model.Type.BoolType;
import Model.Type.IType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class WhileStatement implements IStatement {
    private IExpression condition;
    private IStatement body;

    public WhileStatement(IExpression condition, IStatement body) {
        this.condition = condition;
        this.body = body;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, ExpressionException {
        MyIStack<IStatement> executionStack = currentState.getExeStack();
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        IValue evaluate = this.condition.evaluate(symbolTable, heap);

        if(!evaluate.getType().equals(new BoolType())) {
            throw new StatementException("Conditional expression is not a boolean!");
        }

        if(evaluate.equals(new BoolValue(true))){
            executionStack.push(this);
            executionStack.push(this.body);
        }

        return null;
    }

    public String toString(){
        return "While " + this.condition.toString() + "Execute " + this.body.toString();
    }

    public IStatement deepCopy() {
        return new WhileStatement(condition.deepCopy(), body.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType expressionType = this.condition.typeCheck(typeEnv);
        if(expressionType instanceof BoolType){
            this.body.typeCheck(typeEnv.deepCopy());
            return typeEnv;
        }
        else {
            throw new StatementException("While Statement Error: Conditional expression is not a boolean!");
        }
    }
}
