package Model.Expressions;

import Exceptions.ExpressionException;
import Model.Values.IValue;
import Model.Adt.MyIDictionary;

public interface IExpression {
    IValue evaluate(MyIDictionary<String, IValue> symbolTable) throws ExpressionException;
    IExpression deepCopy();
}
