package Repository;

import Exceptions.RepoFullException;
import Model.ITree;

public interface IRepo {
    public void addTree(ITree tree) throws RepoFullException;
    public ITree[] getTrees();
}
