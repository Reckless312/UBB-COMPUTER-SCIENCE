package Model.Statements;

import Exceptions.DataStructureExceptions;
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

public class ConditionalAssignmentStatement implements IStatement{
    private String id;
    private IExpression exp1, exp2, exp3;

    public ConditionalAssignmentStatement(String id, IExpression exp1, IExpression exp2, IExpression exp3) {
        this.id = id;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIStack<IStatement> exeStack = currentState.getExeStack();
        MyIHeap heap = currentState.getHeap();
        IValue condition = exp1.evaluate(symbolTable, heap);
        IType conditionType = condition.getType();
        if (!conditionType.equals(new BoolType())){
            throw new StatementException("Conditional assignment is not a bool");
        }
        if (condition.equals(new BoolValue())){
            exeStack.push(new AssignStatement(id, exp3));
        }
        else{
            exeStack.push(new AssignStatement(id, exp2));
        }
        return null;
    }

    public IStatement deepCopy() {
        return new ConditionalAssignmentStatement(id, exp1.deepCopy(), exp2.deepCopy(), exp3.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType conditionType = exp1.typeCheck(typeEnv);
        if (!conditionType.equals(new BoolType())){
            throw new StatementException("Conditional assignment is not a bool");
        }
        return typeEnv;
    }

    public String toString() {
        return id + "=" + exp1.toString() + "?" + exp2.toString() + ":" + exp3.toString();
    }
}
