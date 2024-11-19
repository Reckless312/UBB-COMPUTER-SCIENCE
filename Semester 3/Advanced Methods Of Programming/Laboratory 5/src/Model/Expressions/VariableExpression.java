package Model.Expressions;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Values.IValue;

public class VariableExpression implements IExpression {
    private String id;

    public VariableExpression(String id) {
        this.id = id;
    }

    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heap) throws ExpressionException, DataStructureExceptions {
        return symbolTable.lookup(id);
    }

    @Override
    public IExpression deepCopy() {
        return new VariableExpression(id);
    }

    public String toString() {
        return id;
    }
}
