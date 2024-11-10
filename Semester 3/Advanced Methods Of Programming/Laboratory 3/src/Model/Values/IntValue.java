package Model.Values;

import Model.Type.IType;
import Model.Type.IntType;

public class IntValue implements IValue {
    private int value;

    public IntValue() {
        this.value = 0;
    }

    public IntValue(int value) {
        this.value = value;
    }

    public int getValue() {
        return this.value;
    }

    public String toString() {
        return "Integer: " + value;
    }

    public IValue deepCopy() {
        return new IntValue(this.value);
    }

    public IType getType() {
        return new IntType();
    }

    public boolean equals(IValue other) {
        IType otherType = other.getType();
        if (!otherType.equals(this.getType())) {
            return false;
        }
        return ((IntValue)other).getValue() == this.getValue();
    }

    public IValue defaultValue(){
        return new IntValue(0);
    }
}
