package Model.Adt;
import Exceptions.DataStructureExceptions;

import java.util.List;
import java.util.Stack;
public class MyStack<T> implements MyIStack<T> {
    private Stack<T> stack;

    public MyStack() {
        this.stack = new Stack<>();
    }

    public MyStack(Stack<T> stack) {
        this.stack = stack;
    }

    public Stack<T> getStack() {
        return this.stack;
    }

    public T pop() throws DataStructureExceptions {
        if (this.stack.isEmpty()) {
            throw new DataStructureExceptions("Stack is empty");
        }
        return this.stack.pop();
    }

    public void push(T element) {
        this.stack.push(element);
    }

    public boolean empty() {
        return this.stack.empty();
    }

    public String toString() {
        StringBuilder result = new StringBuilder();
        List<T> reversedElements = this.stack.reversed();

        for (T elem : reversedElements) {
            result.append(elem.toString()).append("\n");
        }

        return result.toString();
    }

    public void clear() {
        this.stack.clear();
    }

    @Override
    public List<T> reverse() {
        return List.of();
    }
}
