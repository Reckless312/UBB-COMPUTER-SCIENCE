package Model.Values;

import Model.Type.IType;

public interface IValue {
    IType getType();
    boolean equals(IValue value);
    String toString();
    IValue deepCopy();
}
