using System.Runtime.CompilerServices;
using System.Text;

// IDK SOMEHOW ON 12 THREADS -> 800 for both row and column; 1100 - 1200 for K wise; it takes around 1000 threads to hinder the overall performance;

int nrThreads = 12;
int randomMaxValue = 100;

int firstMatrixNrRows = 2500;
int firstMatrixNrColumns = 5000;
int secondMatrixNrRows = 5000;
int secondMatrixNrColumns = 2500;

int productMatrixNrRows = firstMatrixNrRows, productMatrixNrColumns = secondMatrixNrColumns;

int nrElements = productMatrixNrRows * productMatrixNrColumns;
int nrElementsPerThread = nrElements / nrThreads;

int[,] firstMatrix = new int[firstMatrixNrRows, firstMatrixNrColumns];
int[,] secondMatrix = new int[secondMatrixNrRows, secondMatrixNrColumns];
int[,] productMatrix = new int[productMatrixNrRows, productMatrixNrColumns];

string folder = "/home/Cora/GitHub/UBB-COMPUTER-SCIENCE/Semester 5/Parallel and Distributed Programming/Laboratory 3/";
string matrixFolder = Path.Combine(folder, "matrix.txt");

System.Diagnostics.Stopwatch stopwatch = new System.Diagnostics.Stopwatch();
System.Diagnostics.Stopwatch stopwatchFirstMethod = new System.Diagnostics.Stopwatch();
System.Diagnostics.Stopwatch stopwatchSecondMethod = new System.Diagnostics.Stopwatch();
List<Thread> threads = [];

bool IsProductPossible(int nrColumnsFirstMatrix, int nrRowsSecondMatrix)
{
    return nrColumnsFirstMatrix == nrRowsSecondMatrix;
}

void InitializeThreads(int method)
{
    for (int i = 0; i < nrThreads; i++)
    {
        int threadId = i;
        threads.Add(new Thread(() => Execute(threadId, method)));
    }
}

void InitializeMatrixRandomly(int[,] matrix, int nrRows, int nrColumns)
{
    Random random = new Random();
    for (int i = 0; i < nrRows; i++)
    {
        for (int j = 0; j < nrColumns; j++)
        {
            matrix[i, j] = random.Next(randomMaxValue);
        }
    }
}

void PrintMatrixToFolder(int[,] matrix, string header)
{
    int nrRows = matrix.GetLength(0);
    int nrColumns = matrix.GetLength(1);
    
    File.AppendAllText(matrixFolder, header + "\n");
    
    for (int i = 0; i < nrRows; i++)
    {
        for (int j = 0; j < nrColumns; j++)
        {
            File.AppendAllText(matrixFolder, matrix[i, j] + " ");
        }
        File.AppendAllText(matrixFolder, "\n");
    }
}

[MethodImpl(MethodImplOptions.NoOptimization)]
void MatrixProductElement(int row, int column, int threadId)
{
    int index = 0, sum = 0;

    //StringBuilder debugString = new StringBuilder();
    
    //debugString.Append("Thread: ").Append(threadId).Append(" | assigned for row: ").Append(row).Append(" column: ").Append(column).Append(" | ");
    
    /*while (index < firstMatrixNrRows)
    {
        sum += firstMatrix[row, index] * secondMatrix[index, column];
        //debugString.Append(firstMatrix[row, index]).Append(" * ").Append(secondMatrix[index, column]).Append(" + ");
        index++;
    }*/
    
    productMatrix[row, column] = 1;
    
    //debugString.Remove(debugString.Length - 3, 3);
    //Console.WriteLine(debugString);
}

void Iterate(int threadId, int start, int end, int method)
{
    int k;

    if (method == 0)
    {
        for (int i = start; i < end; i++)
        {
            MatrixProductElement(i / productMatrixNrColumns, i % productMatrixNrColumns, threadId);
        }
    }
    else if (method == 1)
    {
        for (int i = start; i < end; i++)
        {
            MatrixProductElement(i % productMatrixNrRows, i / productMatrixNrRows, threadId);
        }
    }
    else
    {
        k = nrThreads;
        start = threadId;
        end = nrElements;
        for (int i = start; i < end; i+=k)
        {
            MatrixProductElement(i / productMatrixNrColumns, i % productMatrixNrColumns, threadId);
        }
    }
}

void Execute(int threadId, int method)
{
    int start = threadId * nrElementsPerThread;
    int end = start + nrElementsPerThread;

    if (nrElementsPerThread == 0)
    {
        if (threadId == 0)
        {
            Iterate(threadId, 0, nrElements, method);
        }

        return;
    }

    Iterate(threadId, start, end, method);

    if (threadId == nrThreads - 1)
    {
        Iterate(threadId, end, nrElements, method);
    }
}

void Main()
{
    if (!IsProductPossible(firstMatrixNrColumns, secondMatrixNrRows))
    {
        Console.WriteLine("Can't calculate the product");
        return;
    }
    
    // Boom
    if (firstMatrixNrRows <= 0 || firstMatrixNrColumns <= 0 || secondMatrixNrRows <= 0 || secondMatrixNrColumns <= 0)
    {
        Console.WriteLine("Can't calculate the product");
        return;   
    }
    
    File.WriteAllText(matrixFolder, "");
    //PrintMatrixToFolder(firstMatrix, "First Matrix");
    //PrintMatrixToFolder(secondMatrix, "Second Matrix");

    for (int i = 0; i < 10; i++)
    {
        
        threads.Clear();
        InitializeThreads(0);
    
        stopwatch.Start();
        foreach (Thread thread in threads)
        {
            thread.Start();
        }
    
        foreach (Thread thread in threads)
        {
            thread.Join();
        }
        stopwatch.Stop();
        
        threads.Clear();
        InitializeThreads(1);
    
        stopwatchFirstMethod.Start();
        foreach (Thread thread in threads)
        {
            thread.Start();
        }

        foreach (Thread thread in threads)
        {
            thread.Join();
        }
        stopwatchFirstMethod.Stop();
        
        threads.Clear();
        InitializeThreads(2);
    
        stopwatchSecondMethod.Start();
        foreach (Thread thread in threads)
        {
            thread.Start();
        }
        
        foreach (Thread thread in threads)
        {
            thread.Join();
        }
        stopwatchSecondMethod.Stop();
    }
    
    //PrintMatrixToFolder(productMatrix, "Product Matrix");
    string totalTime = "Time taken row: " + stopwatch.Elapsed.TotalMilliseconds / 10 + " ms";
    string firstMethodTime = "Time taken column: " + stopwatchFirstMethod.Elapsed.TotalMilliseconds / 10 + " ms";
    string secondMethodTime = "Time taken k: " + stopwatchSecondMethod.Elapsed.TotalMilliseconds / 10 + " ms";
    Console.WriteLine(totalTime);
    Console.WriteLine(firstMethodTime);
    Console.WriteLine(secondMethodTime);
    File.AppendAllText(matrixFolder, totalTime);
}

Main();