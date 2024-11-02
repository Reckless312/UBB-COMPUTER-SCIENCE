import Controller.Controller;
import Repository.IRepository;
import Repository.Repository;
import View.View;

public class Main {
    public static void main(String[] args) {
        IRepository repo = new Repository();
        Controller controller = new Controller(repo, 1);
        View view = new View(controller);
        view.start();
    }
}
