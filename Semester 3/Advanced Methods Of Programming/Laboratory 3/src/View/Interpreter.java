package View;

import Controller.Controller;
import Model.Adt.*;
import Model.Expressions.ArithmeticExpression;
import Model.Expressions.RelationExpression;
import Model.Expressions.ValueExpression;
import Model.Expressions.VariableExpression;
import Model.ProgramState.ProgramState;
import Model.Statements.*;
import Model.Type.BoolType;
import Model.Type.IntType;
import Model.Type.StringType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.IRepository;
import Repository.Repository;

import java.io.BufferedReader;

public class Interpreter {
    public static void main(String[] args) {
        IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignStatement("v",
                new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));
        MyIStack<IStatement> executionStack1 = new MyStack<>();
        MyIDictionary<String, IValue> symbolTable1 = new MyDictionary<>();
        MyIList<IValue> out1 = new MyList<>();
        MyIDictionary<IValue, BufferedReader> fileTable1 = new MyDictionary<>();
        ProgramState programState1 = new ProgramState(executionStack1, symbolTable1, out1, fileTable1, ex1);
        IRepository repository1 = new Repository(programState1, "log1.txt");
        Controller controller1 = new Controller(repository1, 1);

        IStatement ex2 = new CompStatement( new VarDeclStatement("a",new IntType()),
                new CompStatement(new VarDeclStatement("b",new IntType()),
                        new CompStatement(new AssignStatement("a", new ArithmeticExpression('+',new ValueExpression(new IntValue(2)),new
                                ArithmeticExpression('*',new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompStatement(new AssignStatement("b",new ArithmeticExpression('+',new VariableExpression("a"), new ValueExpression(new
                                        IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));
        MyIStack<IStatement> executionStack2 = new MyStack<>();
        MyIDictionary<String, IValue> symbolTable2 = new MyDictionary<>();
        MyIList<IValue> out2 = new MyList<>();
        MyIDictionary<IValue, BufferedReader> fileTable2 = new MyDictionary<>();
        ProgramState programState2 = new ProgramState(executionStack2, symbolTable2, out2, fileTable2, ex2);
        IRepository repository2 = new Repository(programState2, "log2.txt");
        Controller controller2 = new Controller(repository2, 1);

        IStatement ex3 = new CompStatement(new VarDeclStatement("a",new BoolType()),
                new CompStatement(new VarDeclStatement("v", new IntType()),
                        new CompStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompStatement(new IfStatement(new VariableExpression("a"),new AssignStatement("v",new ValueExpression(new
                                        IntValue(2))), new AssignStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new
                                        VariableExpression("v"))))));
        MyIStack<IStatement> executionStack3 = new MyStack<>();
        MyIDictionary<String, IValue> symbolTable3 = new MyDictionary<>();
        MyIList<IValue> out3 = new MyList<>();
        MyIDictionary<IValue, BufferedReader> fileTable3 = new MyDictionary<>();
        ProgramState programState3 = new ProgramState(executionStack3, symbolTable3, out3, fileTable3, ex3);
        IRepository repository3 = new Repository(programState3, "log3.txt");
        Controller controller3 = new Controller(repository3, 1);

        IStatement ex4 = new CompStatement(new VarDeclStatement("varf", new StringType()), new CompStatement(new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                new CompStatement(new OpenRFileStatement(new VariableExpression("varf")), new CompStatement(new VarDeclStatement("varc", new IntType()),
                        new CompStatement(new ReadFileStatement(new VariableExpression("varf"),"varc"),
                                new CompStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CloseRFileStatement(new VariableExpression("varf"))))))));
        MyIStack<IStatement> executionStack4 = new MyStack<>();
        MyIDictionary<String, IValue> symbolTable4 = new MyDictionary<>();
        MyIList<IValue> out4 = new MyList<>();
        MyIDictionary<IValue, BufferedReader> fileTable4 = new MyDictionary<>();
        ProgramState programState4 = new ProgramState(executionStack4, symbolTable4, out4, fileTable4, ex4);
        IRepository repository4 = new Repository(programState4, "log4.txt");
        Controller controller4 = new Controller(repository4, 1);

        IStatement ex5 = new CompStatement(new VarDeclStatement("number1", new IntType()),
                new CompStatement(new VarDeclStatement("number2", new IntType()),
                new CompStatement(new AssignStatement("number1", new ValueExpression(new IntValue(2))),
                new CompStatement(new AssignStatement("number2", new ValueExpression(new IntValue(3))), new PrintStatement(new RelationExpression(new VariableExpression("number1"),
                        new VariableExpression("number2"), ">"))))));
        MyIStack<IStatement> executionStack5 = new MyStack<>();
        MyIDictionary<String, IValue> symbolTable5 = new MyDictionary<>();
        MyIList<IValue> out5 = new MyList<>();
        MyIDictionary<IValue, BufferedReader> fileTable5 = new MyDictionary<>();
        ProgramState programState5 = new ProgramState(executionStack5, symbolTable5, out5, fileTable5, ex5);
        IRepository repository5 = new Repository(programState5, "log5.txt");
        Controller controller5 = new Controller(repository5, 1);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));
        menu.addCommand(new RunExample("1", ex1.toString(), controller1));
        menu.addCommand(new RunExample("2", ex2.toString(), controller2));
        menu.addCommand(new RunExample("3", ex3.toString(), controller3));
        menu.addCommand(new RunExample("4", ex4.toString(), controller4));
        menu.addCommand(new RunExample("5", ex5.toString(), controller5));
        menu.show();
    }
}
