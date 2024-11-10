package Controller;

import Exceptions.ControllerException;
import Exceptions.DataStructureExceptions;
import Exceptions.RepositoryException;
import Exceptions.StatementException;
import Model.Adt.*;
import Model.Expressions.ArithmeticExpression;
import Model.Expressions.ValueExpression;
import Model.Expressions.VariableExpression;
import Model.ProgramState.ProgramState;
import Model.Statements.*;
import Model.Type.BoolType;
import Model.Type.IntType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Repository.IRepository;

public class Controller {
    private IRepository repo;
    private int displayFlag;

    public Controller(IRepository repo, int displayFlag) {
        this.repo = repo;
        this.displayFlag = displayFlag;
    }

    public void oneStep(ProgramState state) throws ControllerException, DataStructureExceptions, StatementException {
        MyIStack<IStatement> exeStack = state.getExeStack();
        if(exeStack.empty())
            throw new ControllerException("ExeStack is empty");
        IStatement statement = exeStack.pop();
        statement.execute(state);
    }

    public void allStep() throws RepositoryException, ControllerException, DataStructureExceptions, StatementException {
        ProgramState state = repo.getProgramState();
        this.repo.logPrgStateExec();
        switch (displayFlag) {
            case 0:
                while (!state.getExeStack().empty()) {
                    this.oneStep(state);
                    this.repo.logPrgStateExec();
                }
                System.out.println(state.toString());
                break;
            case 1:
                System.out.println(state.toString());
                while(!state.getExeStack().empty()) {
                    this.oneStep(state);
                    this.repo.logPrgStateExec();
                    System.out.println(state.toString());
                }
                break;
            default:
                break;
        }
       state.clear();
    }
}
