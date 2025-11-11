using System;


namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; }
        private Vector SemiAxesLength { get; }
        private double Radius { get; }
        
        public Quaternion Rotation { get; set;  } = Quaternion.NONE;
        
        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color) : base(material, color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color) : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid (Ellipsoid e) : this(new Vector(e.Center), new Vector(e.SemiAxesLength), e.Radius, new Material(e.Material), new Color(e.Color))
        {
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist)
        {
            // TODO: ADD CODE HERE
            
            Vector localPosition = new Vector(line.X0);
            Vector localDirection = new Vector(line.Dx);
            Vector localCenter = new Vector(Center);
            
            localPosition.Rotate(Rotation);
            localDirection.Rotate(Rotation);
            localCenter.Rotate(Rotation);
            
            double a = new Vector(localDirection.X / SemiAxesLength.X, localDirection.Y / SemiAxesLength.Y, localDirection.Z / SemiAxesLength.Z).Length2();
            double b = new Vector(localDirection.X / SemiAxesLength.X, localDirection.Y / SemiAxesLength.Y, localDirection.Z / SemiAxesLength.Z) * new Vector((localPosition.X - localCenter.X) / SemiAxesLength.X, (localPosition.Y - localCenter.Y) / SemiAxesLength.Y, (localPosition.Z - localCenter.Z) / SemiAxesLength.Z) * 2;
            double c = new Vector((localPosition.X - localCenter.X) / SemiAxesLength.X, (localPosition.Y - localCenter.Y) / SemiAxesLength.Y, (localPosition.Z - localCenter.Z) / SemiAxesLength.Z).Length2() - Radius * Radius;
            
            double discriminant = b * b - 4 * a * c;

            if (discriminant < 0)
            {
                return Intersection.NONE;
            }
            
            double t1 = (-b - Math.Sqrt(discriminant)) / (2 * a);
            double t2 = (-b + Math.Sqrt(discriminant)) / (2 * a);

            double t = 0;
            bool isVisible = false;

            if (t1 > minDist && t1 < maxDist)
            {
                t = t1;
                isVisible = true;
            }
            else if (t2 > minDist && t2 < maxDist)
            {
                t = t2;
            }
            else
            {
                return Intersection.NONE;
            }

            Vector hitPosition = line.CoordinateToPosition(t);
            
            Vector localHit = new Vector(hitPosition);
            localHit.Rotate(Rotation);

            Vector localNormal = new Vector((localHit.X - localCenter.X) / (SemiAxesLength.X * SemiAxesLength.X),
                (localHit.Y - localCenter.Y) / (SemiAxesLength.Y * SemiAxesLength.Y),
                (localHit.Z - localCenter.Z) / (SemiAxesLength.Z * SemiAxesLength.Z));

            localNormal.Normalize();
            
            Quaternion inverse = new Quaternion(Rotation.W, -Rotation.X, -Rotation.Y, -Rotation.Z);
            localNormal.Rotate(inverse);
            
            return new Intersection(true, isVisible, this, line, t, localNormal, Material, Color);
        }
        
        private Vector GetNormal(Vector point)
        {
            Vector normal = new Vector(
                (point.X - Center.X) / (SemiAxesLength.X * SemiAxesLength.X),
                (point.Y - Center.Y) / (SemiAxesLength.Y * SemiAxesLength.Y),
                (point.Z - Center.Z) / (SemiAxesLength.Z * SemiAxesLength.Z)
            );
            return normal.Normalize();
        }
    }
}
