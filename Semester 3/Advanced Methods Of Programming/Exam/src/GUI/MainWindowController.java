package GUI;

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
import Model.Values.*;
import Repository.IRepository;
import Repository.Repository;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ListView;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

public class MainWindowController implements Initializable{
    @FXML
    private ListView<IStatement> statementsView;
    private Stage stage;
    ProgramStateWindowController controller;

    private List<IStatement> statements;

    public MainWindowController(){
        statements = new ArrayList<>();
        statementsView = new ListView<>();
        stage = new Stage();
    }

    public void initialize(URL url, ResourceBundle resourceBundle) {
        generateStatements();
        statementsView.getItems().addAll(statements);
        statementsView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<IStatement>() {
            @Override
            public void changed(ObservableValue<? extends IStatement> observableValue, IStatement iStatement, IStatement t1) {
                newProgramStateEvent(t1);
            }
        });
    }

    public void generateStatements(){
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

        IStatement ex14 = new CompStatement(new VarDeclStatement("v1", new RefType(new IntType())), new CompStatement(new VarDeclStatement("cnt", new IntType()), new CompStatement(new HeapAllocationStatement("v1", new ValueExpression(new IntValue(2))),
                new CompStatement(new NewSemaphoreStatement("cnt", new HeapReadingExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(1))), new CompStatement(new ForkStatement(new CompStatement(new AcquireStatement("cnt"), new CompStatement(new HeapWritingStatement("v1", new ArithmeticExpression('*', new HeapReadingExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(10)))),
                        new CompStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v1"))), new ReleaseStatement("cnt"))))), new CompStatement(new ForkStatement(new CompStatement(new AcquireStatement("cnt"), new CompStatement(new HeapWritingStatement("v1", new ArithmeticExpression('*', new HeapReadingExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(10)))), new CompStatement(
                                new HeapWritingStatement("v1", new ArithmeticExpression('*',new HeapReadingExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(2)))), new CompStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v1"))), new ReleaseStatement("cnt")))))),
                        new CompStatement(new AcquireStatement("cnt"), new CompStatement(new PrintStatement(new ArithmeticExpression('-', new HeapReadingExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(1)))), new ReleaseStatement("cnt")))))))));

        IStatement ex15 = new CompStatement(new VarDeclStatement("b", new BoolType()), new CompStatement(new VarDeclStatement("c", new IntType()), new CompStatement(new AssignStatement("b", new ValueExpression(new BoolValue(true))), new CompStatement(new ConditionalAssignmentStatement("c", new VariableExpression("b"), new ValueExpression(new IntValue(100)), new ValueExpression(new IntValue(200))),
                new CompStatement(new PrintStatement(new VariableExpression("c")), new CompStatement(new ConditionalAssignmentStatement("c", new ValueExpression(new BoolValue(false)), new ValueExpression(new IntValue(100)), new ValueExpression(new IntValue(200))), new PrintStatement(new VariableExpression("c"))))))));

        IStatement ex16 = new CompStatement(new VarDeclStatement("v1", new RefType(new IntType())), new CompStatement(new VarDeclStatement("v2", new RefType(new IntType())), new CompStatement(new VarDeclStatement("x", new IntType()), new CompStatement(new VarDeclStatement("q", new IntType()),
                new CompStatement(new HeapAllocationStatement("v1", new ValueExpression(new IntValue(20))), new CompStatement(new HeapAllocationStatement("v2", new ValueExpression(new IntValue(30))), new CompStatement(new NewLockStatement("x"), new CompStatement(new ForkStatement(new CompStatement(new ForkStatement(new CompStatement(new LockStatement("x"),
                        new CompStatement(new HeapWritingStatement("v1", new ArithmeticExpression('-', new HeapReadingExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(1)))), new UnlockStatement("x")))), new CompStatement(
                                new LockStatement("x"), new CompStatement(new HeapWritingStatement("v1", new ArithmeticExpression('*', new HeapReadingExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(10)))), new UnlockStatement("x"))))),
                        new CompStatement(new NewLockStatement("q"), new CompStatement(new ForkStatement(new CompStatement(new ForkStatement(new CompStatement(new LockStatement("q"),
                                new CompStatement(new HeapWritingStatement("v2", new ArithmeticExpression('+', new HeapReadingExpression(new VariableExpression("v2")), new ValueExpression(new IntValue(5)))), new UnlockStatement("q")))), new CompStatement(
                                new LockStatement("q"), new CompStatement(new HeapWritingStatement("v2", new ArithmeticExpression('*', new HeapReadingExpression(new VariableExpression("v2")), new ValueExpression(new IntValue(10)))), new UnlockStatement("q"))))),
                                new CompStatement(new NopStatement(), new CompStatement(new NopStatement(), new CompStatement(new NopStatement(), new CompStatement(new NopStatement(),
                                        new CompStatement(new LockStatement("x"), new CompStatement(new PrintStatement(new HeapReadingExpression(new VariableExpression("v1"))), new CompStatement(new UnlockStatement("x"), new CompStatement(new LockStatement("q"), new CompStatement(
                                                new PrintStatement(new HeapReadingExpression(new VariableExpression("v2"))), new UnlockStatement("q"))))))))))))))))))));

        IStatement ex17 = new CompStatement(new VarDeclStatement("a", new RefType(new IntType())), new CompStatement(new HeapAllocationStatement("a", new ValueExpression(new IntValue(20))), new CompStatement(new ForStatement("v", new ValueExpression(new IntValue(0)), new ValueExpression(new IntValue(3)), new ArithmeticExpression('+', new VariableExpression("v"), new ValueExpression(new IntValue(1))), new ForkStatement(new CompStatement(
                new PrintStatement(new VariableExpression("v")), new AssignStatement("v", new ArithmeticExpression('*', new VariableExpression("v"), new HeapReadingExpression(new VariableExpression("a"))))))), new PrintStatement(new HeapReadingExpression(new VariableExpression("a"))))));

        IStatement ex18 = new CompStatement(new VarDeclStatement("v1", new RefType(new IntType())), new CompStatement(new VarDeclStatement("v2", new RefType(new IntType())), new CompStatement(new VarDeclStatement("v3", new RefType(new IntType())), new CompStatement(
                new VarDeclStatement("cnt", new IntType()), new CompStatement(new HeapAllocationStatement("v1", new ValueExpression(new IntValue(2))), new CompStatement(new HeapAllocationStatement("v2", new ValueExpression(new IntValue(3))), new CompStatement(
                        new HeapAllocationStatement("v3", new ValueExpression(new IntValue(4))), new CompStatement(new NewLatchStatement("cnt", new HeapReadingExpression(new VariableExpression("v2"))),
                new CompStatement(new ForkStatement(new CompStatement(new HeapWritingStatement("v1", new ArithmeticExpression('*', new HeapReadingExpression(new VariableExpression("v1")), new ValueExpression(new IntValue(10)))), new CompStatement(
                new PrintStatement(new HeapReadingExpression(new VariableExpression("v1"))), new CompStatement(new CountDownStatement("cnt"), new ForkStatement(new CompStatement(new HeapWritingStatement("v2", new ArithmeticExpression('*',
                        new HeapReadingExpression(new VariableExpression("v2")), new ValueExpression(new IntValue(10)))), new CompStatement(
                        new PrintStatement(new HeapReadingExpression(new VariableExpression("v2"))), new CompStatement(new CountDownStatement("cnt"), new ForkStatement(new CompStatement(new HeapWritingStatement("v3", new ArithmeticExpression('*', new HeapReadingExpression(new VariableExpression("v3")),
                        new ValueExpression(new IntValue(10)))), new CompStatement(
                        new PrintStatement(new HeapReadingExpression(new VariableExpression("v3"))), new CountDownStatement("cnt")))))))))))), new CompStatement(new AwaitStatement("cnt"), new CompStatement(new PrintStatement(new ValueExpression(new IntValue(100))), new CountDownStatement("cnt"))))))))))));

        IStatement ex19 = new CompStatement(new VarDeclStatement("a", new IntType()), new CompStatement(new VarDeclStatement("b", new IntType()), new CompStatement(new VarDeclStatement("c", new IntType()),
                new CompStatement(new AssignStatement("a", new ValueExpression(new IntValue(1))), new CompStatement(new AssignStatement("b", new ValueExpression(new IntValue(2))), new CompStatement(new AssignStatement("c", new ValueExpression(new IntValue(3))), new CompStatement(
                        new AssignStatement("c", new ValueExpression(new IntValue(5))), new CompStatement(new SwitchStatement(new ArithmeticExpression('*', new VariableExpression("a"), new ValueExpression(new IntValue(10))), new ArithmeticExpression('*', new VariableExpression("b"), new VariableExpression("c")), new ValueExpression(new IntValue(10)), new CompStatement(new PrintStatement(new VariableExpression("a")), new PrintStatement(new VariableExpression("b"))), new CompStatement(
                                new PrintStatement(new ValueExpression(new IntValue(100))), new PrintStatement(new ValueExpression(new IntValue(200)))), new PrintStatement(new ValueExpression(new IntValue(300)))), new PrintStatement(new ValueExpression(new IntValue(300)))))))))));

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
        statements.add(ex14);
        statements.add(ex15);
        statements.add(ex16);
        statements.add(ex17);
        statements.add(ex18);
        statements.add(ex19);

        List<IStatement> correctStatements = new ArrayList<>();

        for(int i = 1; i <= statements.size(); i++) {
            try {
                IStatement statement = statements.get(i - 1);
                statement.typeCheck(new MyDictionary<>());
                correctStatements.add(statement);
            } catch (StatementException | ExpressionException | DataStructureExceptions e) {
                alertTheUser(e);
            }
        }

        statements = correctStatements;
    }

    public IRepository createRepository(IStatement statement){
        MyIStack<IStatement> executionStack = new MyStack<>();
        MyIDictionary<String, IValue> symbolTable = new MyDictionary<>();
        MyIList<IValue> out = new MyList<>();
        MyIDictionary<IValue, BufferedReader> fileTable = new MyDictionary<>();
        MyIHeap heap = new MyHeap();
        MyIConcurrentTable<ITuple<Integer, ObservableList<Integer>, Integer>> semaphoreTable = new MySemaphoreTable<>();
        MyIConcurrentTable<Integer> lockTable = new MyLockTable();
        MyIConcurrentTable<Integer> latchTable = new MyLatchTable();
        ProgramState programState = new ProgramState(executionStack, symbolTable, out, fileTable, heap, semaphoreTable, lockTable, latchTable, statement);
        return new Repository(programState, "log" + programState.getId() + ".txt");
    }

    public void newProgramStateEvent(IStatement statement){
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("secondbuilder.fxml"));
            Parent root = loader.load();

            controller = loader.getController();
            controller.setRepo(createRepository(statement));

            Scene scene = new Scene(root);

            stage.setScene(scene);
            stage.show();
        } catch (Exception e) {
            alertTheUser(e);
        }
    }

    public void alertTheUser(Exception e){
        Alert alert = new Alert(Alert.AlertType.ERROR);
        alert.setTitle("Error");
        alert.setHeaderText("An exception occurred");
        alert.setContentText(e.getMessage());
        alert.showAndWait();
    }
}
