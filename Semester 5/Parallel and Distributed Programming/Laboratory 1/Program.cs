// Threads | Warehouses | Products | Tasks | Time
// 100 | 10 | 20 | 10000 | 2.02 sec
// 10 | 10 | 20 | 10000 | 1.01 sec
// 150 | 10 | 20 | 10000 | 4.03 sec
// 150 | 100 | 20 | 10000 | 3.04 sec

const int numberOfThreads = 150;
const int numberOfProducts = 3;
const int numberOfTask = 10000;
const int numberOfWarehouses = 2;
const int randomizerUpperBound = 100;

int [,] warehousesGoods = new int[numberOfWarehouses, numberOfProducts];
int [] initialStock = new int[numberOfProducts];

Mutex [,] mutexes = new Mutex[numberOfWarehouses, numberOfProducts];

List<Thread> threads = new List<Thread>();

void InitializeWarehouses()
{
    Random randomizer = new Random();
        
    for (int columnIndex = 0; columnIndex < numberOfProducts; columnIndex++)
    {
        for (int rowIndex = 0; rowIndex < numberOfWarehouses; rowIndex++)
        {
            int randomQuantity = randomizer.Next(randomizerUpperBound);
            warehousesGoods[rowIndex, columnIndex] = randomQuantity;
                
            initialStock[columnIndex] += randomQuantity;
        }
    }
}

void InitializeMutexes()
{
    for (int rowIndex = 0; rowIndex < numberOfWarehouses; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < numberOfProducts; columnIndex++)
        {
            mutexes[rowIndex, columnIndex] = new Mutex();
        }
    }
}

void InitializeThreads()
{
    for (int index = 0; index < numberOfThreads; index++)
    {
        int threadId = index;
            
        Thread workThread = new Thread(() => WorkThread());
            
        threads.Add(workThread);
    }
}

int[] CalculateStock()
{
    int[] newStock = new int[numberOfProducts];
    
    for (int j = 0; j < numberOfProducts; j++)
    {
        for (int i = 0; i < numberOfWarehouses; i++)
        {
            mutexes[i, j].WaitOne();
        }
    }
    
    for (int j = 0; j < numberOfProducts; j++)
    {
        for (int i = 0; i < numberOfWarehouses; i++)
        {
            newStock[j] += warehousesGoods[i, j];
            mutexes[i, j].ReleaseMutex();
        }
    }
        
    return newStock;
}

void WorkThread()
{
    Random randomizer = new Random();
        
    for (int i = 0; i < numberOfTask; i++)
    {
        int sendingWarehouse = randomizer.Next(numberOfWarehouses);
        int receivingWarehouse = randomizer.Next(numberOfWarehouses);

        while (sendingWarehouse == receivingWarehouse)
        {
            receivingWarehouse = randomizer.Next(numberOfWarehouses);
        }
        
        int randomProduct = randomizer.Next(numberOfProducts);
        
        int firstLockedWarehouse, secondLockedWarehouse;
            
        if (receivingWarehouse < sendingWarehouse)
        {
            firstLockedWarehouse = receivingWarehouse;
            secondLockedWarehouse = sendingWarehouse;
        }
        else
        {
            firstLockedWarehouse = sendingWarehouse;
            secondLockedWarehouse = receivingWarehouse;
        }
            
        mutexes[firstLockedWarehouse, randomProduct].WaitOne();
        mutexes[secondLockedWarehouse, randomProduct].WaitOne();

        if (warehousesGoods[sendingWarehouse, randomProduct] == 0)
        {
            mutexes[secondLockedWarehouse, randomProduct].ReleaseMutex();
            mutexes[firstLockedWarehouse, randomProduct].ReleaseMutex();
            continue;
        }
        
        int randomQuantity = randomizer.Next(warehousesGoods[firstLockedWarehouse, randomProduct]);
            
        warehousesGoods[firstLockedWarehouse, randomProduct] -= randomQuantity;
        warehousesGoods[secondLockedWarehouse, randomProduct] += randomQuantity;
            
        mutexes[secondLockedWarehouse, randomProduct].ReleaseMutex();
        mutexes[firstLockedWarehouse, randomProduct].ReleaseMutex();
    }
}

void InspectorThread()
{
    DateTime startTime = DateTime.Now;
    
    bool areWorkersDone = false;
    
    while (!areWorkersDone)
    {
        Thread.Sleep(1000);
            
        areWorkersDone = true;
        threads.ForEach(thread =>
        {
            if (thread.IsAlive)
            {
                areWorkersDone = false;
            }
        });
            
        int[] newStock = CalculateStock();

        for (int i = 0; i < numberOfProducts; i++)
        {
            if (initialStock[i] != newStock[i])
            {
                System.Console.WriteLine("Something is not right! " + initialStock[i] + " != " + newStock[i]);
            }
        }
    }
    System.Console.WriteLine("Done in " + (DateTime.Now - startTime).TotalSeconds + " seconds");
}

void Main()
{
    if (numberOfWarehouses < 2)
    {
        return;
    }
    
    InitializeWarehouses();
    InitializeMutexes();
    InitializeThreads();
    
    threads.ForEach(thread => thread.Start());

    Thread inspectorThread = new Thread(() => InspectorThread());
    inspectorThread.Start();
    
    threads.ForEach(thread => thread.Join());
    inspectorThread.Join();
}

Main();