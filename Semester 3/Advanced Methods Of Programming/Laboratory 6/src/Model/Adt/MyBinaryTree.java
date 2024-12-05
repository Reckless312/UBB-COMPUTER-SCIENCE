package Model.Adt;

public class MyBinaryTree<T> implements MyIBinaryTree<T> {
    private T value;
    MyBinaryTree<T> left;
    MyBinaryTree<T> right;

    public MyBinaryTree(T value) {
        this.value = value;
        this.left = null;
        this.right = null;
    }

    public MyBinaryTree(T value, MyBinaryTree<T> left, MyBinaryTree<T> right) {
        this.value = value;
        this.left = left;
        this.right = right;
    }

    public StringBuilder treeTraversal(){
        StringBuilder stringBuilder = new StringBuilder();

        if(left != null){
            stringBuilder.append(left.treeTraversal());
        }

        if(this.isLeaf()){
            stringBuilder.append(value.toString());
            stringBuilder.append('\n');
        }

        if(right != null){
            stringBuilder.append(right.treeTraversal());
        }

        return stringBuilder;
    }

    @Override
    public boolean isLeaf() {
        return this.left == null && this.right == null;
    }
}
