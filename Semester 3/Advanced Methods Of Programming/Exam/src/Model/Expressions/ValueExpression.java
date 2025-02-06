package Model.Expressions;

import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Type.IType;
import Model.Values.IValue;

public class ValueExpression implements IExpression {
    private IValue value;

    public ValueExpression(IValue value) {
        this.value = value;
    }

    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heap) throws ExpressionException {
        return this.value;
    }

    public IExpression deepCopy() {
        return new ValueExpression(this.value.deepCopy());
    }

    public IType typeCheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException {
        return this.value.getType();
    }

    public String toString() {
        return this.value.toString();
    }

}
