package Main;

import Controller.Controller;
import Repository.Repository;
import View.View;

public class main {
    public static void main(String[] args) {
        Repository repo = new Repository(10);
        Controller controller = new Controller(repo);
        View view = new View(controller);

    }
}
