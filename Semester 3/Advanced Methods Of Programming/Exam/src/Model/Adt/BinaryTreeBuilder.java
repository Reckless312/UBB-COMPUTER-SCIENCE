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

        MyBinaryTree<IStatement> leftSubTree = buildTree(leftStmt);
        MyBinaryTree<IStatement> rightSubTree = buildTree(rightStmt);

        return new MyBinaryTree<>(program, leftSubTree, rightSubTree);
    }
}
