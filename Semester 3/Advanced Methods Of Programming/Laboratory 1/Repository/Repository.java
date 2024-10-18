package Repository;

import Exceptions.RepoFullException;
import Model.ITree;

public class Repository implements IRepo{
    private ITree[] storage;
    private int currentPosition;

    public Repository(int capacity){this.storage = new ITree[capacity];this.currentPosition = 0;}

    @Override
    public void addTree(ITree tree) throws RepoFullException {
        if(this.currentPosition >= this.storage.length){
            throw new RepoFullException("Storage is full");
        }
        this.storage[this.currentPosition] = tree;
        this.currentPosition++;
    }

    @Override
    public ITree[] getTrees() {
        return this.storage;
    }
}
