package Model.Type;

import Model.Values.IValue;
import Model.Values.StringValue;

public class StringType implements IType {

    public boolean equals(IType other) {
       return other instanceof StringType;
    }

    public IValue defaultValue() {
        return new StringValue("NULL");
    }

    public IType deepCopy() {
        return new StringType();
    }

    public String toString() {
        return "String";
    }
}
