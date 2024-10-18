package View;

import Controller.Controller;
import Exceptions.ControllerNoElementFound;
import Exceptions.RepoFullException;
import Model.Apple;
import Model.Cherry;
import Model.Pear;
import Model.ITree;

public class View {
    private Controller controller;

    public View(Controller controller) {
        try {
            this.controller = controller;

            for(int i = 0; i < 5; i++) {
                Apple apple = new Apple(i);
                Cherry cherry = new Cherry(i);
                Pear pear = new Pear(i);
                this.controller.addToRepo(apple);
                this.controller.addToRepo(cherry);
                this.controller.addToRepo(pear);
            }

            ITree[] oldtree = this.controller.getOlderTrees();
            for(ITree tree : oldtree) {
                if(tree != null) {
                    System.out.println(tree.toString());
                }
            }
        } catch (ControllerNoElementFound | RepoFullException e) {
            System.out.println(e.getMessage());
        }
    }
}
