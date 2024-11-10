package Model.Expressions;

import Exceptions.ExpressionException;
import Model.Adt.MyIDictionary;
import Model.Type.IntType;
import Model.Values.IValue;
import Model.Values.IntValue;

public class ArithmeticExpression implements IExpression {
    private IExpression firstExpression;
    private IExpression secondExpression;
    private int operator; // 1-plus, 2-minus, 3-star, 4-divide
    private char operatorChar;

    public ArithmeticExpression(char operator, IExpression firstExpression, IExpression secondExpression) {
        this.firstExpression = firstExpression;
        this.secondExpression = secondExpression;

        if (operator == '+') {
            this.operator = 1;
        }
        else if (operator == '-') {
            this.operator = 2;
        }
        else if (operator == '*') {
            this.operator = 3;
        }
        else if (operator == '/') {
            this.operator = 4;
        }
        else{
            this.operator = -1;
        }

        this.operatorChar = operator;
    }

    public IValue evaluate(MyIDictionary<String, IValue> symbolTable) throws ExpressionException {
        IValue firstValue, secondValue;
        firstValue = firstExpression.evaluate(symbolTable);

        if(firstValue.getType().equals(new IntType())){
            secondValue = secondExpression.evaluate(symbolTable);
            if(secondValue.getType().equals(new IntType())){
                IntValue firstInteger = (IntValue) firstValue;
                IntValue secondInteger = (IntValue) secondValue;

                int firstNumber = firstInteger.getValue();
                int secondNumber = secondInteger.getValue();

                switch(operator){
                    case 1: return new IntValue(firstNumber + secondNumber);
                    case 2: return new IntValue(firstNumber - secondNumber);
                    case 3: return new IntValue(firstNumber * secondNumber);
                    case 4: if (secondNumber != 0)
                        return new IntValue(firstNumber / secondNumber);
                    else throw new ExpressionException("Division by zero");
                }
            }
            else
                throw new ExpressionException("Second operand is not an integer");
        }
        else
            throw new ExpressionException("First operand is not an integer");
        throw new ExpressionException("Operator doesn't have a corresponding value");
    }

    @Override
    public IExpression deepCopy() {
        return new ArithmeticExpression(this.operatorChar, this.firstExpression.deepCopy(), this.secondExpression.deepCopy());
    }

    public String toString() {
        return "( " + firstExpression.toString() + " " + this.operatorChar + " " + secondExpression.toString() + " )";
    }
}
