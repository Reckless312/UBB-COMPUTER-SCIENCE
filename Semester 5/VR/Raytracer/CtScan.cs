﻿using System;
using System.IO;
using System.Text.RegularExpressions;

namespace rt;

public class CtScan: Geometry
{
    private readonly Vector _position;
    private readonly double _scale;
    private readonly ColorMap _colorMap;
    private readonly byte[] _data;

    private readonly int[] _resolution = new int[3];
    private readonly double[] _thickness = new double[3];
    private readonly Vector _v0;
    private readonly Vector _v1;

    public CtScan(string datFile, string rawFile, Vector position, double scale, ColorMap colorMap) : base(Color.NONE)
    {
        _position = position;
        _scale = scale;
        _colorMap = colorMap;

        var lines = File.ReadLines(datFile);
        foreach (var line in lines)
        {
            var kv = Regex.Replace(line, "[:\\t ]+", ":").Split(":");
            if (kv[0] == "Resolution")
            {
                _resolution[0] = Convert.ToInt32(kv[1]);
                _resolution[1] = Convert.ToInt32(kv[2]);
                _resolution[2] = Convert.ToInt32(kv[3]);
            } else if (kv[0] == "SliceThickness")
            {
                _thickness[0] = Convert.ToDouble(kv[1]);
                _thickness[1] = Convert.ToDouble(kv[2]);
                _thickness[2] = Convert.ToDouble(kv[3]);
            }
        }

        _v0 = position;
        _v1 = position + new Vector(_resolution[0]*_thickness[0]*scale, _resolution[1]*_thickness[1]*scale, _resolution[2]*_thickness[2]*scale);

        var len = _resolution[0] * _resolution[1] * _resolution[2];
        _data = new byte[len];
        using FileStream f = new FileStream(rawFile, FileMode.Open, FileAccess.Read);
        if (f.Read(_data, 0, len) != len)
        {
            throw new InvalidDataException($"Failed to read the {len}-byte raw data");
        }
    }
    
    private ushort Value(int x, int y, int z)
    {
        if (x < 0 || y < 0 || z < 0 || x >= _resolution[0] || y >= _resolution[1] || z >= _resolution[2])
        {
            return 0;
        }

        return _data[z * _resolution[1] * _resolution[0] + y * _resolution[0] + x];
    }

    public override Intersection GetIntersection(Line line, double minDist, double maxDist)
    {
        // TODO: ADD CODE HERE
        // TODO: IMPROVE CT SCAN OUTBOUND CHECKING

        double stepT = 0.2;
        
        double opacityThreshold = 0.99;

        Color hitColor = Color.NONE;
        double hitOpacity = 0;

        (double, double)? entryAndExit = FindIntersection(line);

        if (!entryAndExit.HasValue)
        {
            return Intersection.NONE;
        }

        bool firstHit = false;
        double firstHitDistance = 0;

        for (double currentDistance = entryAndExit.Value.Item1; currentDistance < entryAndExit.Value.Item2; currentDistance+= stepT)
        {
            Vector currentPosition = line.CoordinateToPosition(currentDistance);
            int[] indexes = GetIndexes(currentPosition);
            ushort value = Value(indexes[0], indexes[1], indexes[2]);

            if (value == 0)
            {
                continue;
            }
            
            if (!firstHit)
            {
                firstHitDistance = currentDistance;
                firstHit = true;
            }
            
            Color currentColor = GetColor(currentPosition);
            hitColor += currentColor * currentColor.Alpha * (1.0 - hitOpacity);
            hitOpacity += currentColor.Alpha * (1.0 - hitOpacity);

            if (hitOpacity > opacityThreshold)
            {
                Vector hitPosition = line.CoordinateToPosition(firstHitDistance);
                return new Intersection(true, true, this, line, firstHitDistance, GetNormal(hitPosition), Material.FromColor(hitColor), hitColor);
            }
        }

        if (firstHit)
        {
            Vector hitPosition = line.CoordinateToPosition(firstHitDistance);
            return new Intersection(true, true, this, line, firstHitDistance, GetNormal(hitPosition), Material.FromColor(hitColor), hitColor);
        }
        
        return Intersection.NONE;
    }

    private (double entry, double exit)? FindIntersection(Line line)
    {
        // Define bounds of the box
        Vector min = _v0;
        Vector max = _v1;

        Vector tMin = new Vector(min - line.X0);
        Vector tMax = new Vector(max - line.X0);

        tMin.Divide(line.Dx);
        tMax.Divide(line.Dx);

        double tx1 = Math.Min(tMin.X, tMax.X);
        double tx2 = Math.Max(tMin.X, tMax.X);
        double ty1 = Math.Min(tMin.Y, tMax.Y);
        double ty2 = Math.Max(tMin.Y, tMax.Y);
        double tz1 = Math.Min(tMin.Z, tMax.Z);
        double tz2 = Math.Max(tMin.Z, tMax.Z);

        double tEnter = Math.Max(tx1, Math.Max(ty1, tz1));
        double tExit = Math.Min(tx2, Math.Min(ty2, tz2));

        if (tExit < tEnter || tExit < 0)
            return null;

        return (tEnter, tExit);
    }
    
    private int[] GetIndexes(Vector v)
    {
        return new []{
            (int)Math.Floor((v.X - _position.X) / _thickness[0] / _scale), 
            (int)Math.Floor((v.Y - _position.Y) / _thickness[1] / _scale),
            (int)Math.Floor((v.Z - _position.Z) / _thickness[2] / _scale)};
    }
    private Color GetColor(Vector v)
    {
        int[] idx = GetIndexes(v);

        ushort value = Value(idx[0], idx[1], idx[2]);
        return _colorMap.GetColor(value);
    }

    private Vector GetNormal(Vector v)
    {
        int[] idx = GetIndexes(v);
        double x0 = Value(idx[0] - 1, idx[1], idx[2]);
        double x1 = Value(idx[0] + 1, idx[1], idx[2]);
        double y0 = Value(idx[0], idx[1] - 1, idx[2]);
        double y1 = Value(idx[0], idx[1] + 1, idx[2]);
        double z0 = Value(idx[0], idx[1], idx[2] - 1);
        double z1 = Value(idx[0], idx[1], idx[2] + 1);

        return new Vector(x1 - x0, y1 - y0, z1 - z0).Normalize();
    }
}