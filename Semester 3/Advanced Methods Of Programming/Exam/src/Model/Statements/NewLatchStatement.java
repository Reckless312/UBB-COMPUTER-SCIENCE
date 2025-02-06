package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIConcurrentTable;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Expressions.IExpression;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class NewLatchStatement implements IStatement{
    private String id;
    private IExpression expression;

    public NewLatchStatement(String id, IExpression expression) {
        this.id = id;
        this.expression = expression;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, ExpressionException, DataStructureExceptions {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        MyIConcurrentTable<Integer> latchTable = currentState.getLatchTable();
        IValue value = expression.evaluate(symbolTable, heap);
        IType type = value.getType();
        if (!type.equals(new IntType())){
            throw new StatementException("The type of expression is not an integer");
        }
        synchronized (latchTable){
            IValue value2 = symbolTable.lookup(id);
            IType type2 = value2.getType();
            if(!type2.equals(new IntType())){
                throw new StatementException("The type of expression is not an integer");
            }
            latchTable.add(((IntValue) value).getValue());
            symbolTable.update(id, new IntValue(latchTable.previouslyAddedLocation()));
        }
        return null;
    }

    public IStatement deepCopy() {
        return new NewLatchStatement(id, expression.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType type = expression.typeCheck(typeEnv);
        if (!type.equals(new IntType())){
            throw new StatementException("The type of expression is not an integer");
        }
        IType value2 = typeEnv.lookup(id);
        if(!value2.equals(new IntType())){
            throw new StatementException("The type of expression is not an integer");
        }
        return typeEnv;
    }

    public String toString() {
        return "NewLatchStatement " + id + " " + expression.toString();
    }
}
