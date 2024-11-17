package Model.Adt;

import Model.Statements.CompStatement;
import Model.Statements.IStatement;

public class BinaryTreeBuilder implements ITreeBuilder<IStatement> {
    public MyBinaryTree<IStatement> buildTree(IStatement program) {
        if(!(program instanceof CompStatement)){
            return new MyBinaryTree<>(program);
        }

        CompStatement compStat = (CompStatement) program;
        IStatement leftStmt = compStat.getFirst();
        IStatement rightStmt = compStat.getSecond();

        MyBinaryTree<IStatement> leftSubTree = new MyBinaryTree<>(leftStmt);
        MyBinaryTree<IStatement> rightSubTree = new MyBinaryTree<>(rightStmt);

        return new MyBinaryTree<>(program, leftSubTree, rightSubTree);
    }
}
