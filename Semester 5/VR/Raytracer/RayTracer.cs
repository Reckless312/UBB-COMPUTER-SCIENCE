using System;

namespace rt
{
    class RayTracer(Geometry[] geometries, Light[] lights)
    {
        private double ImageToViewPlane(int n, int imgSize, double viewPlaneSize)
        {
            return -n * viewPlaneSize / imgSize + viewPlaneSize / 2;
        }

        private Intersection FindFirstIntersection(Line ray, double minDist, double maxDist)
        {
            var intersection = Intersection.NONE;

            foreach (var geometry in geometries)
            {
                var intr = geometry.GetIntersection(ray, minDist, maxDist);

                if (!intr.Valid || !intr.Visible) continue;

                if (!intersection.Valid || !intersection.Visible)
                {
                    intersection = intr;
                }
                else if (intr.T < intersection.T)
                {
                    intersection = intr;
                }
            }

            return intersection;
        }

        private bool IsLit(Vector point, Light light)
        {
            // TODO: ADD CODE HERE
            Vector toLight = light.Position - point;
            double distanceToLight = toLight.Length();
            toLight.Normalize();
            
            Vector offsetPoint = point + toLight * 0.01;
            
            Line shadowRay = new Line(offsetPoint, light.Position);

            bool skip = true;

            foreach (var geometry in geometries)
            {
                if (skip)
                {
                    skip = false;
                    continue;
                }
                
                Intersection intersection = geometry.GetIntersection(shadowRay, 0.01, distanceToLight - 0.01);
                
                if (!intersection.Valid || !intersection.Visible)
                {
                    continue;
                }
                
                if (intersection.T < distanceToLight)
                {
                    return false;
                }
            }
            return true;
        }

        public void Render(Camera camera, int width, int height, string filename)
        {
            var background = new Color(0.2, 0.2, 0.2, 1.0);

            var image = new Image(width, height);

            for (var i = 0; i < width; i++)
            {
                for (var j = 0; j < height; j++)
                {
                    // TODO: ADD CODE HERE
                    double x = ImageToViewPlane(i, width, camera.ViewPlaneWidth);
                    double y = ImageToViewPlane(j, height, camera.ViewPlaneHeight);
                    
                    Vector right = camera.Up ^ camera.Direction;
                    Vector rayDirection = (camera.Direction * camera.ViewPlaneDistance + (right * x) + (camera.Up * y)).Normalize();
                    Vector rayEnd = camera.Position + rayDirection;
                    
                    Line line = new Line(camera.Position, rayEnd);
                    Intersection firstIntersection = FindFirstIntersection(line, camera.FrontPlaneDistance, camera.BackPlaneDistance);

                    if (!firstIntersection.Valid)
                    {
                        
                        image.SetPixel(i, j, background);
                        continue;
                    }

                    Color newColor = new Color();

                    foreach (Light light in lights)
                    {
                        newColor += light.Ambient * firstIntersection.Material.Ambient;
                        
                        if (!IsLit(firstIntersection.Position, light))
                        {
                            continue;
                        }
                        
                        Vector toLight = (light.Position - firstIntersection.Position).Normalize();

                        if (firstIntersection.Normal * toLight > 0)
                        {
                            newColor += firstIntersection.Material.Diffuse * light.Diffuse * (firstIntersection.Normal * toLight);
                        }
                        
                        Vector toCamera = (firstIntersection.Line.X0 - firstIntersection.Position).Normalize();
                        Vector reflection = (firstIntersection.Normal  * (firstIntersection.Normal * toLight) * 2 - toLight).Normalize();

                        if (toCamera * reflection > 0)
                        {
                            newColor += firstIntersection.Material.Specular * light.Specular *
                                        Math.Pow(toCamera * reflection, firstIntersection.Material.Shininess);
                        }
                    }
                    
                    image.SetPixel(i, j, newColor);
                }
            }

            image.Store(filename);
        }
    }
}