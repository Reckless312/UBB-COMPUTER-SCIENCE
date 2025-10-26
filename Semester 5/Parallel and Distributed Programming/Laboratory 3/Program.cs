using System.Text;

int[,] firstMatrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
int[,] secondMatrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

int firstMatrixNrRows = firstMatrix.GetLength(0), firstMatrixNrColumns = firstMatrix.GetLength(1);
int secondMatrixNrRows = secondMatrix.GetLength(0), secondMatrixNrColumns = secondMatrix.GetLength(1);
int productMatrixNrRows = firstMatrixNrRows, productMatrixNrColumns = secondMatrixNrColumns;
int nrThreads = 2;

int[,] productMatrix = new int[productMatrixNrRows, productMatrixNrColumns];

List<Thread> threads = new List<Thread>();
MatrixProductMethod method = MatrixProductMethod.ColumnWise;

bool IsProductPossible(int nrColumnsFirstMatrix, int nrRowsSecondMatrix)
{
    return nrColumnsFirstMatrix == nrRowsSecondMatrix;
}

void InitializeThreads()
{
    for (int i = 0; i < nrThreads; i++)
    {
        int threadId = i;
        threads.Add(new Thread(() => ParalelProduct(threadId)));
    }
}

void MatrixProductElement(int row, int column, int threadId)
{
    int i = 0, sum = 0;

    StringBuilder debugString = new StringBuilder();
    
    debugString.Append("Thread: ").Append(threadId).Append(" | assigned for row: ").Append(row).Append(" column: ").Append(column).Append(" | ");
    
    while (i < firstMatrixNrRows)
    {
        sum += firstMatrix[row, i] * secondMatrix[i, column];
        debugString.Append(firstMatrix[row, i]).Append(" * ").Append(secondMatrix[i, column]).Append(" + ");
        i++;
    }
    productMatrix[row, column] = sum;
    
    debugString.Remove(debugString.Length - 3, 3);
    Console.WriteLine(debugString.ToString());
}

void IterateRowWise(int threadId, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        MatrixProductElement(i / productMatrixNrColumns, i % productMatrixNrColumns, threadId);
    }
}

void ExecuteRowWise(int threadId, int nrElements, int nrElementsPerThread)
{
    int start = threadId * nrElementsPerThread;
    int end = start + nrElementsPerThread;

    if (nrElementsPerThread == 0 && threadId == 0)
    {
        IterateRowWise(threadId, 0, nrElements);
    }
            
    IterateRowWise(threadId, start, end);

    if (nrElementsPerThread != 0 && threadId == nrThreads - 1)
    {
        IterateRowWise(threadId, end, nrElements);
    }
}

void IterateColumnWise(int threadId, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        MatrixProductElement(i / productMatrixNrRows, i % productMatrixNrRows, threadId);
    }
}

void ExecuteColumnWise(int threadId, int nrElements, int nrElementsPerThread)
{
    int start = threadId * nrElementsPerThread;
    int end = start + nrElementsPerThread;

    if (nrElementsPerThread == 0 && threadId == 0)
    {
        IterateColumnWise(threadId, 0, nrElements);
    }
            
    IterateColumnWise(threadId, start, end);

    if (nrElementsPerThread != 0 && threadId == nrThreads - 1)
    {
        IterateColumnWise(threadId, end, nrElements);
    }
}

void ParalelProduct(int threadId)
{
    int nrElements = productMatrixNrRows * productMatrixNrColumns;
    int nrElementsPerThread = nrElements / nrThreads;
    switch (method)
    {
        case MatrixProductMethod.RowWise:
            ExecuteRowWise(threadId, nrElements, nrElementsPerThread);
            break;
        case MatrixProductMethod.ColumnWise:
            ExecuteColumnWise(threadId, nrElements, nrElementsPerThread);       
            break;
        case MatrixProductMethod.KWise:
            break;
    }
}

void Main()
{
    if (!IsProductPossible(firstMatrixNrColumns, secondMatrixNrRows))
    {
        Console.WriteLine("Can't calculate the product");
        return;
    }
    
    InitializeThreads();
    
    foreach (Thread thread in threads)
    {
        thread.Start();
    }
    
    foreach (Thread thread in threads)
    {
        thread.Join();
    }
    
    Console.WriteLine("Done");
}

Main();

enum MatrixProductMethod
{
    RowWise,
    ColumnWise,
    KWise,
}