package Model.Expressions;

import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Operators.LogicalOperator;
import Model.Type.BoolType;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;

public class LogicalExpression implements IExpression {
    private LogicalOperator operator;
    private IExpression leftOperator;
    private IExpression rightOperator;

    public LogicalExpression(IExpression leftOperator, IExpression rightOperator, LogicalOperator operator) {
        this.leftOperator = leftOperator;
        this.rightOperator = rightOperator;
        this.operator = operator;
    }

    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heap) throws ExpressionException {
        IValue resultLeft = leftOperator.evaluate(symbolTable, heap);
        IValue resultRight = rightOperator.evaluate(symbolTable, heap);

        if (!resultLeft.getType().equals(new BoolType())) {
            throw new ExpressionException("Result type does not match the value type for the LEFT OPERAND");
        }
        if (!resultRight.getType().equals(new BoolType())) {
            throw new ExpressionException("Result type does not match the value type for the RIGHT OPERAND");
        }

        return switch(operator) {
            case AND -> new BoolValue(((BoolValue)resultLeft).getValue() && ((BoolValue)resultRight).getValue());
            case OR -> new BoolValue(((BoolValue)resultLeft).getValue() || ((BoolValue)resultRight).getValue());
        };
    }

    public IExpression deepCopy() {
        return new LogicalExpression(leftOperator.deepCopy(), rightOperator.deepCopy(), operator);
    }

    public IType typeCheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException {
        IType type1, type2;
        type1 = this.leftOperator.typeCheck(typeEnv);
        type2 = this.rightOperator.typeCheck(typeEnv);
        if (type1.equals(new BoolType())){
            if (type2.equals(new BoolType())){
                return new BoolType();
            }
            else {
                throw new ExpressionException("Logical Expression Error: Second operand is not a boolean");
            }
        }
        else {
            throw new ExpressionException("Logical Expression Error: First operand is not a boolean");
        }
    }

    public String toString() {
        return "(" + leftOperator.toString() + " " + this.operator + " " + rightOperator.toString() + ")";
    }
}