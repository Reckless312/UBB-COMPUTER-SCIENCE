package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Adt.MyIHeap;
import Model.Expressions.IExpression;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.StringType;
import Model.Values.IValue;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStatement implements IStatement {
    private IExpression expression;

    public CloseRFileStatement(IExpression expression) {
        this.expression = expression;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException, ExpressionException, DataStructureExceptions {
        MyIDictionary<String, IValue> symbolTable = currentState.getSymbolTable();
        MyIHeap heap = currentState.getHeap();
        IValue evaluate = this.expression.evaluate(symbolTable, heap);
        IType evaluateType = evaluate.getType();

        if(!evaluateType.equals(new StringType())){
            throw new StatementException("Name of the file must be a string!");
        }

        MyIDictionary<IValue, BufferedReader> fileTable = currentState.getFileTable();
        synchronized (fileTable) {
            BufferedReader buffer = fileTable.lookup(evaluate);

            try{
                buffer.close();
            }
            catch(IOException e){
                throw new StatementException("Could not close the file");
            }

            fileTable.delete(evaluate);
        }
        return null;
    }

    public IStatement deepCopy() {
        return new CloseRFileStatement(this.expression.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        IType expressionType = expression.typeCheck(typeEnv);
        if (expressionType instanceof StringType) {
            return typeEnv;
        }
        else{
            throw new StatementException("Close File Statement Error: Argument provided is not a string");
        }
    }

    public String toString() {
        return "Close file: '" + this.expression.toString();
    }
}
