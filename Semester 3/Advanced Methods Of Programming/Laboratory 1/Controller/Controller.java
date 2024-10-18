package Controller;

import Exceptions.ControllerNoElementFound;
import Exceptions.RepoFullException;
import Repository.IRepo;
import Model.ITree;

public class Controller {
    private IRepo repo;

    public Controller(IRepo repo) {this.repo = repo;}

    public void addToRepo(ITree tree) throws RepoFullException {
        this.repo.addTree(tree);
    }

    public ITree[] getOlderTrees() throws ControllerNoElementFound {
        ITree[] Trees = this.repo.getTrees();
        ITree[] OlderTrees = new ITree[Trees.length];

        int pos = 0;
        for(ITree tree : Trees) {
            if(tree != null && tree.GetAge() >= 3) {
                OlderTrees[pos] = tree;
                pos++;
            }
        }

        if (pos == 0) {
            throw new ControllerNoElementFound("No tree found");
        }

        return OlderTrees;
    }
}
