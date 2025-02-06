package Model.Statements;

import Exceptions.DataStructureExceptions;
import Exceptions.StatementException;
import Model.Adt.MyIDictionary;
import Model.Expressions.IExpression;
import Model.Expressions.RelationExpression;
import Model.ProgramState.ProgramState;
import Model.Type.IType;

public class SwitchStatement implements IStatement{
    private IExpression exp, exp1, exp2;
    private IStatement stmt1, stmt2, stmt3;

    public SwitchStatement(IExpression exp, IExpression exp1, IExpression exp2, IStatement stmt1, IStatement stmt2, IStatement stmt3) {
        this.exp = exp;
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.stmt1 = stmt1;
        this.stmt2 = stmt2;
        this.stmt3 = stmt3;
    }

    public ProgramState execute(ProgramState currentState) throws StatementException {
        IStatement switchStatement = new IfStatement(new RelationExpression(exp, exp1, "=="), stmt1,
                new IfStatement(new RelationExpression(exp, exp2, "=="), stmt2, stmt3));
        currentState.getExeStack().push(switchStatement);
        return null;
    }

    public IStatement deepCopy() {
        return new SwitchStatement(exp.deepCopy(), exp1.deepCopy(), exp2.deepCopy(), stmt1.deepCopy(), stmt2.deepCopy(), stmt3.deepCopy());
    }

    public MyIDictionary<String, IType> typeCheck(MyIDictionary<String, IType> typeEnv) throws StatementException, DataStructureExceptions {
        stmt1.typeCheck(typeEnv);
        stmt2.typeCheck(typeEnv);
        stmt3.typeCheck(typeEnv);
        IType type1 = exp1.typeCheck(typeEnv);
        IType type2 = exp2.typeCheck(typeEnv);
        IType type = exp.typeCheck(typeEnv);
        if(type.equals(type1) && type.equals(type2)) {
            return typeEnv;
        }
        throw new StatementException("Expression types don't match");
    }

    public String toString() {
        return "SwitchStatement" + exp.toString() + exp1.toString() + exp2.toString() + stmt1.toString() + stmt2.toString() + stmt3.toString();
    }
}
