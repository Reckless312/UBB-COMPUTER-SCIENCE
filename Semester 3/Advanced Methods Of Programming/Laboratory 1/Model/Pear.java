package Model;

public class Pear implements ITree {
    private int age;
    private String name;

    public Pear(int age) {this.age = age;this.name = "Pear";}

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
