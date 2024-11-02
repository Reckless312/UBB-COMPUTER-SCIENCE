package Controller;

import Exceptions.ControllerException;
import Exceptions.DataStructureExceptions;
import Exceptions.RepositoryException;
import Exceptions.StatementException;
import Model.Adt.*;
import Model.Expressions.ArithmeticExpression;
import Model.Expressions.ValueExpression;
import Model.Expressions.VariableExpression;
import Model.ProgramState;
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

    // changed to void until the program state returned is used
    public void oneStep(ProgramState state) throws ControllerException, DataStructureExceptions, StatementException {
        MyIStack<IStatement> exeStack = state.getExeStack();
        if(exeStack.empty())
            throw new ControllerException("ExeStack is empty");
        IStatement statement = exeStack.pop();
        statement.execute(state);
    }

    public void allStep() throws RepositoryException, ControllerException, DataStructureExceptions, StatementException {
        ProgramState state = repo.getProgramState();
        this.displayCurrentState();
        while(!state.getExeStack().empty()) {
            this.oneStep(state);
            this.displayCurrentState();
        }
    }

    public void displayCurrentState() {
        if(displayFlag == 1) {
            System.out.println(this.repo.getProgramState().toString());
        }
    }

    public IStatement makeStatement1(){
        IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignStatement("v",
                new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));
        return ex1;
    }

    public IStatement makeStatement2(){
        IStatement ex2 = new CompStatement( new VarDeclStatement("a",new IntType()),
                new CompStatement(new VarDeclStatement("b",new IntType()),
                        new CompStatement(new AssignStatement("a", new ArithmeticExpression('+',new ValueExpression(new IntValue(2)),new
                                ArithmeticExpression('*',new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompStatement(new AssignStatement("b",new ArithmeticExpression('+',new VariableExpression("a"), new ValueExpression(new
                                        IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
        return ex2;
    }

    public IStatement makeStatement3(){
        IStatement ex3 = new CompStatement(new VarDeclStatement("a",new BoolType()),
                new CompStatement(new VarDeclStatement("v", new IntType()),
                        new CompStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompStatement(new IfStatement(new VariableExpression("a"),new AssignStatement("v",new ValueExpression(new
                                        IntValue(2))), new AssignStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new
                                        VariableExpression("v"))))));
        return ex3;
    }

    public void MakeProgramState(IStatement statement) {
        MyIStack<IStatement> exeStack = new MyStack<>();
        MyIDictionary<String, IValue> symbolTable = new MyDictionary<>();
        MyIList<IValue> out = new MyList<>();
        ProgramState state = new ProgramState(exeStack, symbolTable, out, statement);
        this.repo.setProgramState(state);
    }

    public void hardCodedStatements(String option) throws ControllerException {
        switch(option){
            case "1":
                this.MakeProgramState(makeStatement1());
                break;
            case "2":
                this.MakeProgramState(makeStatement2());
                break;
            case "3":
                this.MakeProgramState(makeStatement3());
                break;
            default:
                throw new ControllerException("No available option chosen!");
        }
    }
}
