public class Laboratory
{
    private static int randomizerUpperBound = 100;
    private static int numberOfTask = 10000;
    private static int numberOfThreads = 100;
    private static int numberOfProducts = 200;
    
    private static void Main()
    {
        /* Solution:
         * For simplicity the values for the threads / products / tasks are hardcoded
         * A worker thread is a warehouse
         * Each warehouse has an array of products (matrix cause OOP is ugly)
         * Matrix of mutexes for concurrency control
         */
        
        int [,] warehousesGoods = new int[Laboratory.numberOfThreads, Laboratory.numberOfProducts];
        int [] initialStock = new int[Laboratory.numberOfProducts];
        
        Mutex [,] mutexes = new Mutex[Laboratory.numberOfThreads, Laboratory.numberOfProducts];
        
        List<Thread> threads = new List<Thread>();

        
        // No point to move from the same warehouse to the same warehouse or nothing to nothing :>
        if (numberOfThreads < 2)
        {
            return;
        }
        
        InitializeRandomlyTheWarehouses(warehousesGoods, initialStock);
        InitializeMutexes(mutexes);
        InitializeThreads(threads, warehousesGoods, mutexes);
        
        threads.ForEach(thread => thread.Start());
        
        Thread inspectorThread = new Thread(() => InspectorThread(warehousesGoods, initialStock, threads, mutexes));
        inspectorThread.Start();
        
        try
        {
            threads.ForEach(thread => thread.Join());
            inspectorThread.Join();
        }
        catch (Exception e)
        {
            System.Console.WriteLine(e);
        }
    }

    public static void InitializeRandomlyTheWarehouses(int [,] warehousesGoods, int[] initialStock)
    {
        Random randomizer = new Random();
        
        for (int columnIndex = 0; columnIndex < Laboratory.numberOfProducts; columnIndex++)
        {
            for (int rowIndex = 0; rowIndex < Laboratory.numberOfThreads; rowIndex++)
            {
                int randomQuantity = randomizer.Next(Laboratory.randomizerUpperBound);
                warehousesGoods[rowIndex, columnIndex] = randomQuantity;
                
                initialStock[columnIndex] += randomQuantity;
            }
        }
    }

    public static void InitializeMutexes(Mutex[,] mutexes)
    {
        for (int rowIndex = 0; rowIndex < numberOfThreads; rowIndex++)
        {
            for (int columnIndex = 0; columnIndex < numberOfProducts; columnIndex++)
            {
                mutexes[rowIndex, columnIndex] = new Mutex();
            }
        }
    }

    public static void InitializeThreads(List<Thread> threads, int[,] warehousesGoods, Mutex[,] mutexes)
    {
        for (int index = 0; index < numberOfThreads; index++)
        {
            int threadId = index;
            
            Thread workThread = new Thread(() => WorkThread(threadId, warehousesGoods, mutexes));
            
            threads.Add(workThread);
        }
    }

    public static int[] GetNewTotalStock(int[,] warehousesGoods, Mutex[,] mutexes)
    {
        int[] newStock = new int[numberOfProducts];
        
        // Locking everything so no thread has access to some of the stock
        for (int j = 0; j < numberOfProducts; j++)
        {
            for (int i = 0; i < numberOfThreads; i++)
            {
                mutexes[i, j].WaitOne();
            }
        }
        
        // Both adding and releasing should be fine since the threads will only work with what is unlocked
        for (int j = 0; j < numberOfProducts; j++)
        {
            for (int i = 0; i < numberOfThreads; i++)
            {
                newStock[j] += warehousesGoods[i, j];
                mutexes[i, j].ReleaseMutex();
            }
        }
        
        return newStock;
    }

    public static void WorkThread(int threadId, int[,] warehousesGoods, Mutex [,] mutexes)
    {
        int numberRows = warehousesGoods.GetLength(0);
        int numberColumns = warehousesGoods.GetLength(1);
        
        Random randomizer = new Random();
        
        for (int i = 0; i < Laboratory.numberOfTask; i++)
        {
            int randomWarehouse = randomizer.Next(numberRows);

            while (randomWarehouse == threadId)
            {
                randomWarehouse = randomizer.Next(numberRows);
            }
            
            int randomProduct = randomizer.Next(numberColumns);
            
            // Locking in an increasing order of id to avoid deadlocks
            int firstLockedThread, secondLockedThread;
            
            if (threadId < randomWarehouse)
            {
                firstLockedThread = threadId;
                secondLockedThread = randomWarehouse;
            }
            else
            {
                firstLockedThread = randomWarehouse;
                secondLockedThread = threadId;
            }
            
            mutexes[firstLockedThread, randomProduct].WaitOne();
            mutexes[secondLockedThread, randomProduct].WaitOne();

            if (warehousesGoods[threadId, randomProduct] == 0)
            {
                // Nothing to do
                mutexes[secondLockedThread, randomProduct].ReleaseMutex();
                mutexes[firstLockedThread, randomProduct].ReleaseMutex();
                continue;
            }
            
            warehousesGoods[firstLockedThread, randomProduct]--;
            warehousesGoods[secondLockedThread, randomProduct]++;
            
            mutexes[secondLockedThread, randomProduct].ReleaseMutex();
            mutexes[firstLockedThread, randomProduct].ReleaseMutex();
        }
    }
    
    public static void InspectorThread(int[,] warehousesGoods, int[] initialStock, List<Thread> threads, Mutex[,] mutexes)
    {
        bool areWorkersDone = false;
        DateTime startTime = DateTime.Now;
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
            
            int[] newStock = GetNewTotalStock(warehousesGoods, mutexes);

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
}