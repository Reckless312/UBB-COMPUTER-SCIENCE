package Model.Type;

import Model.Values.IValue;
import Model.Values.RefValue;

public class RefType implements IType{
    private IType inner;

    public RefType(IType inner) {
        this.inner = inner;
    }

    public IType getInner() {
        return inner;
    }

    public boolean equals(IType other) {
        if (other instanceof RefType) {
            return inner.equals(((RefType) other).getInner());
        }
        return false;
    }

    public String toString() {
        return "Ref(" + inner.toString() + ")";
    }

    public IValue defaultValue() {
        return new RefValue(0, inner);
    }

    public IType deepCopy() {
        return new RefType(inner.deepCopy());
    }
}
