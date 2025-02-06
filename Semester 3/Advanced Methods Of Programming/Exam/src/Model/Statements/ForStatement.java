package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Expressions.IExpression;
import Model.Expressions.RelationExpression;
import Model.Expressions.VariableExpression;
import Model.ProgramState.ProgramState;
import Model.Type.IType;
import Model.Type.IntType;
import Model.Values.IValue;

public class ForStatement implements IStatement{
    private String var;
    private IExpression exp1, exp2, exp3;
    private IStatement stmt;

    public ForStatement(String var, IExpression exp1, IExpression exp2, IExpression exp3, IStatement stmt) {
        this.var = var;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.exp3 = exp3;
        this.stmt = stmt;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException {
        IStatement statement = new CompStatement(new VarDeclStatement(var, new IntType()), new CompStatement(new AssignStatement(var, exp1),
                new WhileStatement(new RelationExpression(new VariableExpression(var), exp2, "<"), new CompStatement(stmt, new AssignStatement(var, exp3)))));
        currentState.getExeStack().push(statement);
        return null;
    }

    public IStatement deepCopy() {
        return new ForStatement(var, exp1.deepCopy(), exp2.deepCopy(), exp3.deepCopy(), stmt.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        typeEnv.update(var, new IntType());
        IType type = exp1.typeCheck(typeEnv);
        IType type2 = exp2.typeCheck(typeEnv);
        IType type3 = exp3.typeCheck(typeEnv);
        if(type.equals(type2) && type.equals(type3) && type.equals(new IntType())) {
            return typeEnv;
        }
        throw new StatementException("One of the expressions is not an integer in the for statement!");
    }

    public String toString() {
        return "For " + var + "=" + exp1.toString() + "; " + var + "<" + exp2.toString() + "; " + var + "=" + exp3.toString() + "do " + stmt.toString();
    }
}
