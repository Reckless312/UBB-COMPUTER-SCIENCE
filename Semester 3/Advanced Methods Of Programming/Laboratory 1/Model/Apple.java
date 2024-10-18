package Model;

public class Apple implements ITree {
    private int age;
    private String name;

    public Apple(int age) {this.age = age;this.name = "Apple";}

    @Override
    public int GetAge() {
        return this.age;
    }

    @Override
    public String GetName() {return this.name;}

    @Override
    public String toString() {
        return this.name + " tree has an age of " + this.age + " years";
    }
}
