package Model.Type;

import Model.Values.IValue;

public interface IType {
    boolean equals(IType other);
    String toString();
    IValue defaultValue();
    IType deepCopy();
}
