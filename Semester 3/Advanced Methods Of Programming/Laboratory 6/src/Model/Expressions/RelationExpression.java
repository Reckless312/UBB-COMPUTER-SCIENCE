package Model.Expressions;

import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Type.BoolType;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;

public class RelationExpression implements IExpression {
    private IExpression leftExpression;
    private IExpression rightExpression;
    private String relationalOperator;

    public RelationExpression(IExpression leftExpression, IExpression rightExpression, String relationalOperator) {
        this.leftExpression = leftExpression;
        this.rightExpression = rightExpression;
        this.relationalOperator = relationalOperator;
    }

    public IValue evaluate(MyIDictionary<String, IValue> symbolTable, MyIHeap heap) throws ExpressionException {
        IValue resultLeft = leftExpression.evaluate(symbolTable, heap);
        IValue resultRight = rightExpression.evaluate(symbolTable, heap);

        if (!resultLeft.getType().equals(new IntType())) {
            throw new ExpressionException("Result type does not match the value type for the LEFT OPERAND");
        }
        if (!resultRight.getType().equals(new IntType())) {
            throw new ExpressionException("Result type does not match the value type for the RIGHT OPERAND");
        }

        return switch(this.relationalOperator){
            case "<" -> new BoolValue(((IntValue)resultLeft).getValue() < ((IntValue)resultRight).getValue());
            case "<=" -> new BoolValue(((IntValue)resultLeft).getValue() <= ((IntValue)resultRight).getValue());
            case "==" -> new BoolValue(((IntValue)resultLeft).getValue() == ((IntValue)resultRight).getValue());
            case "!=" -> new BoolValue(((IntValue)resultLeft).getValue() != ((IntValue)resultRight).getValue());
            case ">" -> new BoolValue(((IntValue)resultLeft).getValue() > ((IntValue)resultRight).getValue());
            case ">=" -> new BoolValue(((IntValue)resultLeft).getValue() >= ((IntValue)resultRight).getValue());
            default -> throw new ExpressionException("Invalid relational operator");
        };
    }

    public IExpression deepCopy() {
        return new RelationExpression(leftExpression.deepCopy(), rightExpression.deepCopy(), relationalOperator);
    }

    public IType typeCheck(MyIDictionary<String, IType> typeEnv) throws ExpressionException {
        IType type1, type2;
        type1 = this.leftExpression.typeCheck(typeEnv);
        type2 = this.rightExpression.typeCheck(typeEnv);
        if (type1.equals(new IntType())){
            if (type2.equals(new IntType())){
                return new BoolType();
            }
            else {
                throw new ExpressionException("Relation Expression Error: Second operand is not an integer");
            }
        }
        else {
            throw new ExpressionException("Relation Expression Error: First operand is not an integer");
        }
    }

    public String toString(){
        return "(" + leftExpression.toString() + " " + relationalOperator + " " + rightExpression.toString() + ")";
    }
}
