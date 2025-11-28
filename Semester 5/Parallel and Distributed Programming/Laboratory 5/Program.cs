using System.Diagnostics;

class Solution
{
    private const int MAX_DEPTH = 2; 
    
    public static int[] RandomizePolynomialCoefficients(int size)
    {
        int[] polynomial = new int[size];
        Random rnd = new Random();

        for (int i = 0; i < size; i++)
        {
            polynomial[i] = rnd.Next(-1000, 1000);
        }

        return polynomial;
    }

    public static int[] MultiplyPolynomialsSequentially(int[] A, int[] B)
    {
        int[] product = new int[A.Length + B.Length - 1];
        for (int i = 0; i < A.Length; i++)
        {
            for (int j = 0; j < B.Length; j++)
            {
                product[i + j] += A[i] * B[j];
            }
        }
        return product;
    }
    
    public static int[] MultiplyPolynomialsParallel(int[] A, int[] B)
    {
        int[] product = new int[A.Length + B.Length - 1];
    
        Parallel.For(0, A.Length, i =>
        {
            int termA = A[i];
            for (int j = 0; j < B.Length; j++)
            {
                Interlocked.Add(ref product[i + j], termA * B[j]);
            }
        });
    
        return product;
    }

    public static int[] AddCoefficients(int[] A, int[] B)
    {
        int n = Math.Max(A.Length, B.Length);
        int[] result = new int[n];
        for (int i = 0; i < n; i++)
        {
            if (i >= A.Length)
            {
                result[i] = B[i];
            }
            else if (i >= B.Length)
            {
                result[i] = A[i];
            }
            else
            {
                result[i] = A[i] + B[i];
            }
        }
        return result;
    }

    public static int[] SubstractCoefficients(int[] A, int[] B)
    {
        int n = Math.Max(A.Length, B.Length);
        int[] result = new int[n];
        for (int i = 0; i < n; i++)
        {
            if (i >= A.Length)
            {
                result[i] = -B[i];
            }
            else if (i >= B.Length)
            {
                result[i] = A[i];
            }
            else
            {
                result[i] = A[i] - B[i];
            }
        }
        return result;
    }

    public static int[] MultiplyWithScalar(int[] A, int scalar)
    {
        int[] result = new int[A.Length];
        for (int i = 0; i < A.Length; i++)
        {
            result[i] = A[i] * scalar;
        }
        return result;
    }

    public static int[] ShiftRight(int[] A, int n)
    {
        int[] result = new int[A.Length + n];
        Array.Copy(A, 0, result, n, A.Length);
        return result;
    }
    
    public static int[] MultiplyPolynomialsKaratsuba(int[] A, int[] B)
    {
        int n = Math.Max(A.Length, B.Length);
        
        if (n <= 4)
        {
            return MultiplyPolynomialsSequentially(A, B);
        }

        int[] equalA = new int[n];
        int[] equalB = new int[n];
        
        Array.Copy(A, equalA, A.Length);
        Array.Copy(B, equalB, B.Length);
        
        int m = n / 2;
        int[] A1 = new int[m];
        int[] A2 = new int[n - m];
        Array.Copy(equalA, 0, A1, 0, m);
        Array.Copy(equalA, m, A2, 0, n - m);
        int[] B1 = new int[m];
        int[] B2 = new int[n - m];
        Array.Copy(equalB, 0, B1, 0, m);
        Array.Copy(equalB, m, B2, 0, n - m);
        
        int[] A1WithA2 = AddCoefficients(A1, A2);
        int[] B1WithB2 = AddCoefficients(B1, B2);
        
        int[] Z0 = MultiplyPolynomialsKaratsuba(A1, B1);
        int[] Z2 = MultiplyPolynomialsKaratsuba(A2, B2);
        int[] A1A2KaratsubaB1B2 = MultiplyPolynomialsKaratsuba(A1WithA2, B1WithB2);
        
        int[] Intermediate = SubstractCoefficients(A1A2KaratsubaB1B2, Z0);
        int[] Z1 = SubstractCoefficients(Intermediate, Z2);

        return AddCoefficients(Z0, AddCoefficients(ShiftRight(Z1, m), ShiftRight(Z2, 2 * m)));
    }
    
    public static int[] MultiplyPolynomialsKaratsubaParallel(int[] A, int[] B, int depth)
    {
        int n = Math.Max(A.Length, B.Length);

        if (n <= 4)
        {
            return MultiplyPolynomialsSequentially(A, B);
        }

        int[] equalA = new int[n];
        int[] equalB = new int[n];
        
        Array.Copy(A, equalA, A.Length);
        Array.Copy(B, equalB, B.Length);
        
        int m = n / 2;
        int[] A1 = new int[m];
        int[] A2 = new int[n - m];
        Array.Copy(equalA, 0, A1, 0, m);
        Array.Copy(equalA, m, A2, 0, n - m);
        int[] B1 = new int[m];
        int[] B2 = new int[n - m];
        Array.Copy(equalB, 0, B1, 0, m);
        Array.Copy(equalB, m, B2, 0, n - m);
        
        int[] A1WithA2 = AddCoefficients(A1, A2);
        int[] B1WithB2 = AddCoefficients(B1, B2);

        if (depth < MAX_DEPTH)
        {
            Task<int[]> Z0 = Task.Run(() => MultiplyPolynomialsKaratsubaParallel(A1, B1, depth + 1));
            Task<int[]> Z2 = Task.Run(() => MultiplyPolynomialsKaratsubaParallel(A2, B2, depth + 1));
            Task<int[]> A1A2KaratsubaB1B2 = Task.Run(() => MultiplyPolynomialsKaratsubaParallel(A1WithA2, B1WithB2, depth + 1));
            
            Task.WaitAll(Z0, Z2, A1A2KaratsubaB1B2);
        
            int[] Intermediate = SubstractCoefficients(A1A2KaratsubaB1B2.Result, Z0.Result);
            int[] Z1 = SubstractCoefficients(Intermediate, Z2.Result);

            return AddCoefficients(Z0.Result, AddCoefficients(ShiftRight(Z1, m), ShiftRight(Z2.Result, 2 * m)));
        }
        else
        {
            int[] Z0 = MultiplyPolynomialsKaratsuba(A1, B1);
            int[] Z2 = MultiplyPolynomialsKaratsuba(A2, B2);
            int[] A1A2KaratsubaB1B2 = MultiplyPolynomialsKaratsuba(A1WithA2, B1WithB2);
        
            int[] Intermediate = SubstractCoefficients(A1A2KaratsubaB1B2, Z0);
            int[] Z1 = SubstractCoefficients(Intermediate, Z2);

            return AddCoefficients(Z0, AddCoefficients(ShiftRight(Z1, m), ShiftRight(Z2, 2 * m)));
        }
    }

    public static void PrintPolynomial(int[] polynomial)
    {
        for (int i = 0; i < polynomial.Length; i++)
        {
            Console.Write(polynomial[i] + " ");
        }

        Console.WriteLine();
    }
    
    public static void Main()
    {
        Stopwatch stopwatch = new Stopwatch();
        
        int[] P = RandomizePolynomialCoefficients(100000);
        int[] Q = RandomizePolynomialCoefficients(100000);

        stopwatch.Start();
        int[] result1 = MultiplyPolynomialsSequentially(P, Q);
        stopwatch.Stop();
        
        Console.WriteLine("Sequential O(n^2):");
        //PrintPolynomial(result1);
        Console.WriteLine(stopwatch.ElapsedMilliseconds);
        
        stopwatch.Reset();
        
        stopwatch.Start();
        int[] result2 = MultiplyPolynomialsKaratsuba(P, Q);
        stopwatch.Stop();
        
        Console.WriteLine("Karatsuba:");
        //PrintPolynomial(result2);
        Console.WriteLine(stopwatch.ElapsedMilliseconds);
        
        stopwatch.Reset();
        
        stopwatch.Start();
        int[] result3 = MultiplyPolynomialsParallel(P, Q);
        stopwatch.Stop();
        
        Console.WriteLine("Parallel:");
        //PrintPolynomial(result3);
        Console.WriteLine(stopwatch.ElapsedMilliseconds);
        
        stopwatch.Reset();
        
        stopwatch.Start();
        int[] result4 = MultiplyPolynomialsKaratsubaParallel(P, Q, 0);
        stopwatch.Stop();
        
        Console.WriteLine("Karatsuba Parallel:");
        //PrintPolynomial(result4);
        Console.WriteLine(stopwatch.ElapsedMilliseconds);
    }
}