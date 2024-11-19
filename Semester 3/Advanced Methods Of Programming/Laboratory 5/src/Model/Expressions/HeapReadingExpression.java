package Model.Expressions;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Type.RefType;
import Model.Values.IValue;
import Model.Values.RefValue;

public class HeapReadingExpression implements IExpression {
    private IExpression expression;

    public HeapReadingExpression(IExpression expression) {
        this.expression = expression;
    }

    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heap) throws ExpressionException, DataStructureExceptions {
        IValue evaluate = expression.evaluate(symbolTable, heap);
        if(!(evaluate instanceof RefValue)){
            throw new ExpressionException("Type mismatch");
        }
        Integer address = ((RefValue)evaluate).getAddress();
        IValue value = heap.getValueFromAddress(address);
        return value;
    }

    public String toString(){
        return "(Read from heap " + expression.toString() + ")";
    }

    public IExpression deepCopy() {
        return new HeapReadingExpression(expression.deepCopy());
    }
}
