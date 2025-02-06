package Model.Type;

import Model.Values.IValue;
import Model.Values.IntValue;

public class IntType implements IType {
    public boolean equals(IType otherType){
        return otherType instanceof IntType;
    }
    public String toString() {return "Integer";}

    public IValue defaultValue() {
        return new IntValue();
    }

    public IType deepCopy() {
        return new IntType();
    }

}
