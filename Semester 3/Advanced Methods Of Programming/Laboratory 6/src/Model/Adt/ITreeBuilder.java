package Model.Adt;

import Model.Statements.IStatement;

public interface ITreeBuilder<T>{
    MyBinaryTree<IStatement> buildTree(IStatement program);
}
