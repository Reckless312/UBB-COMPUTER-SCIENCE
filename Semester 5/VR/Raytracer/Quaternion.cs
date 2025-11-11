using System;

namespace rt;

public class Quaternion(double w, double x, double y, double z)
{
    public static readonly Quaternion NONE = new(1, 0, 0, 0);
    public double W { get; set; } = w;
    public double X { get; set; } = x;
    public double Y { get; set; } = y;
    public double Z { get; set; } = z;

    public Quaternion Normalize()
    {
        var a = Math.Sqrt(W*W+X*X+Y*Y+Z*Z);
        W /= a;
        X /= a;
        Y /= a;
        Z /= a;
        return this;
    }
    
    public static Quaternion FromAxisAngle(double aa, Vector axis)
    {
        // TODO: ADD CODE HERE
        
        double qx = axis.X * Math.Sin(aa/2);
        double qy = axis.Y * Math.Sin(aa/2);
        double qz = axis.Z * Math.Sin(aa/2);
        double qw = Math.Cos(aa/2);
        
        return new Quaternion(qw, qx, qy, qz).Normalize();
    }
}