package View;

import Controller.Controller;
import Exceptions.*;

public class RunExample extends Command{
    private Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try{
            this.controller.allSteps();
        }
        catch (ControllerException | InterruptedException e) {
            System.out.println(e.getMessage());
        }
        this.controller.clearState();
    }
}
