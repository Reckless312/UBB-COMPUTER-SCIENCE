package View;

import Controller.Controller;
import Exceptions.*;

import java.util.Scanner;

public class View {
    private Controller controller;

    public View(Controller controller) {
        this.controller = controller;
    }

    public void start() {
        System.out.println("Welcome to the Toy Language Interpreter!");

        while (true) {
            System.out.println("1.Select a program");
            System.out.println("2.Execute the program");
            System.out.println("3.Exit");

            Scanner scanner = new Scanner(System.in);
            if (!scanner.hasNextInt()) {
                System.out.println("Answer not a number!");
                continue;
            }
            String response  = scanner.nextLine();

            if (response.equals("1")) {
                System.out.println("Select program 1, 2 or 3");
                try {
                    if (!scanner.hasNextInt()) {
                        System.out.println("Answer not a number!");
                        continue;
                    }
                    String programChoice  = scanner.nextLine();
                    this.controller.hardCodedStatements(programChoice);
                }
                catch (ControllerException e) {
                    System.out.println(e.getMessage());
                }
            }
            else if (response.equals("2")) {
                try {
                    this.controller.allStep();
                }
                catch (ControllerException | RepositoryException | DataStructureExceptions | StatementException |
                       ExpressionException e) {
                    System.out.println(e.getMessage());
                }
            }
            else if (response.equals("3")) {
                break;
            }
            else
                System.out.println("Wrong option!");
        }
    }
}
