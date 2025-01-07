package View;

import Controller.Controller;
import Exceptions.DataStructureExceptions;
import Exceptions.ExpressionException;
import Exceptions.StatementException;
import Model.Adt.*;
import Model.Expressions.*;
import Model.ProgramState.ProgramState;
import Model.Statements.*;
import Model.Type.BoolType;
import Model.Type.IntType;
import Model.Type.RefType;
import Model.Type.StringType;
import Model.Values.BoolValue;
import Model.Values.IValue;
import Model.Values.IntValue;
import Model.Values.StringValue;
import Repository.IRepository;
import Repository.Repository;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;

public class Interpreter {
    public static void main(String[] args) {
        IStatement ex1 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignStatement("v",
                new ValueExpression(new IntValue(2))), new PrintStatement(new VariableExpression("v"))));

        IStatement ex2 = new CompStatement( new VarDeclStatement("a",new IntType()),
                new CompStatement(new VarDeclStatement("b",new IntType()),
                        new CompStatement(new AssignStatement("a", new ArithmeticExpression('+',new ValueExpression(new BoolValue(false)),new
                                ArithmeticExpression('*',new ValueExpression(new IntValue(3)), new ValueExpression(new IntValue(5))))),
                                new CompStatement(new AssignStatement("b",new ArithmeticExpression('+',new VariableExpression("a"), new ValueExpression(new
                                        IntValue(1)))), new PrintStatement(new VariableExpression("b"))))));

        IStatement ex3 = new CompStatement(new VarDeclStatement("a",new BoolType()),
                new CompStatement(new VarDeclStatement("v", new IntType()),
                        new CompStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                new CompStatement(new IfStatement(new VariableExpression("a"),new AssignStatement("v",new ValueExpression(new
                                        IntValue(2))), new AssignStatement("v", new ValueExpression(new IntValue(3)))), new PrintStatement(new
                                        VariableExpression("v"))))));

        IStatement ex4 = new CompStatement(new VarDeclStatement("varf", new StringType()), new CompStatement(new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                new CompStatement(new OpenRFileStatement(new VariableExpression("varf")), new CompStatement(new VarDeclStatement("varc", new IntType()),
                        new CompStatement(new ReadFileStatement(new VariableExpression("varf"),"varc"),
                                new CompStatement(new ReadFileStatement(new VariableExpression("varf"), "varc"), new CompStatement(new PrintStatement(new VariableExpression("varc")), new CloseRFileStatement(new VariableExpression("varf")))))))));

        IStatement ex5 = new CompStatement(new VarDeclStatement("number1", new IntType()),
                new CompStatement(new VarDeclStatement("number2", new IntType()),
                new CompStatement(new AssignStatement("number1", new ValueExpression(new IntValue(2))),
                new CompStatement(new AssignStatement("number2", new ValueExpression(new IntValue(3))), new PrintStatement(new RelationExpression(new VariableExpression("number1"),
                        new VariableExpression("number2"), ">"))))));

        IStatement ex6 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))),new CompStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new VariableExpression("a")))))));

        IStatement ex7 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))),new CompStatement(new HeapAllocationStatement("a", new VariableExpression("v")),
                        new CompStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))), new PrintStatement(new ArithmeticExpression('+', new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))), new ValueExpression(new IntValue(5)))))))));

        IStatement ex8 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))), new CompStatement(new HeapWritingStatement("v", new ValueExpression(new IntValue(30))), new PrintStatement(new ArithmeticExpression('+', new HeapReadingExpression(new VariableExpression("v")), new ValueExpression(new IntValue(5))))))));

        IStatement ex9 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new AssignStatement("v", new ValueExpression(new IntValue(4))), new CompStatement(new WhileStatement(new RelationExpression(new VariableExpression("v"), new ValueExpression(new IntValue(0)), ">"), new CompStatement(new PrintStatement(new VariableExpression("v")), new AssignStatement("v",
                new ArithmeticExpression('-', new VariableExpression("v"), new ValueExpression(new IntValue(1)))))), new PrintStatement(new VariableExpression("v")))));

        IStatement ex10 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))), new CompStatement(new HeapAllocationStatement("a", new VariableExpression("v")), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                       new PrintStatement(new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a")))))))));

        IStatement ex11 = new CompStatement(new VarDeclStatement("v", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                new CompStatement(new VarDeclStatement("a", new RefType(new RefType(new IntType()))), new CompStatement(new HeapAllocationStatement("a", new VariableExpression("v")), new CompStatement(new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                        new CompStatement(new HeapAllocationStatement("a", new VariableExpression("v")), new CompStatement(new VarDeclStatement("b", new RefType(new IntType())),
                                new CompStatement(new HeapAllocationStatement("b", new ValueExpression(new IntValue(1))), new HeapAllocationStatement("a", new VariableExpression("b"))))))))));

        IStatement ex12 = new CompStatement(new VarDeclStatement("v", new IntType()), new CompStatement(new VarDeclStatement("a", new RefType(new IntType())), new CompStatement(new AssignStatement("v", new ValueExpression(new IntValue(10))),
                new CompStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))), new CompStatement(new ForkStatement(new CompStatement(new HeapWritingStatement("a", new ValueExpression(new IntValue(30))),new CompStatement(
                        new AssignStatement("v", new ValueExpression(new IntValue(32))), new CompStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new HeapReadingExpression(new VariableExpression("a"))))))),
                        new CompStatement(new PrintStatement(new VariableExpression("v")), new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))))))));

        IStatement ex13 = new CompStatement(new VarDeclStatement("v", new IntType()), new VarDeclStatement("v", new IntType()));

        List<IStatement> statements = new ArrayList<>();
        statements.add(ex1);
        statements.add(ex2);
        statements.add(ex3);
        statements.add(ex4);
        statements.add(ex5);
        statements.add(ex6);
        statements.add(ex7);
        statements.add(ex8);
        statements.add(ex9);
        statements.add(ex10);
        statements.add(ex11);
        statements.add(ex12);
        statements.add(ex13);

        TextMenu menu = new TextMenu();
        menu.addCommand(new ExitCommand("0", "exit"));

        for(int i = 1; i <= 13; i++) {
            MyIStack<IStatement> executionStack = new MyStack<>();
            MyIDictionary<String, IValue> symbolTable = new MyDictionary<>();
            MyIList<IValue> out = new MyList<>();
            MyIDictionary<IValue, BufferedReader> fileTable = new MyDictionary<>();
            MyIHeap heap = new MyHeap();
            try {
                IStatement statement = statements.get(i - 1);
                statement.typeCheck(new MyDictionary<>());
                ProgramState programState = new ProgramState(executionStack, symbolTable, out, fileTable, heap, statements.get(i - 1));
                IRepository repository = new Repository(programState, "log" + i + ".txt");
                Controller controller = new Controller(repository, 1);
                menu.addCommand(new RunExample("" + i, statements.get(i - 1).toString(), controller));
            } catch (StatementException | ExpressionException | DataStructureExceptions e) {
                System.out.println(e.getMessage());
            }
        }
        menu.show();
    }
}
