package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Expressions.IExpression;
import Model.ProgramState;
import Model.Type.IType;
import Model.Values.IValue;

public class AssignStatement implements IStatement {
    private String id;
    private IExpression expression;

    public AssignStatement(String id, IExpression expression) {
        this.id = id;
        this.expression = expression;
    }

    public String toString() {
        return "(Variable name: " + id + " = " + expression.toString()+")";
    }

    public ProgramState execute(ProgramState currentState) throws ExpressionException, StatementException, DataStructureExceptions {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();

        if (symbolTable.isDefined(id)){
            IValue value = expression.evaluate(symbolTable);
            IType idType = (symbolTable.lookup(id)).getType();
            if(value.getType().equals(idType)){
                symbolTable.update(id, value);
            }
            else{
                throw new StatementException("The variable with the name: " + id + " has a different type than the assignment value");
            }
        }
        else{
            throw new StatementException("The variable with the name: " + id + " was not found");
        }
        return currentState;
    }

    @Override
    public IStatement deepCopy() {
        return new AssignStatement(this.id, this.expression.deepCopy());
    }
}
