// For queue size = 1 -> around 719 ms
// For queue size = 10 -> around 97 ms
// For queue size = 100 -> around 38 ms
// No further improvements for the vector size (100.000); 100 seems to be the sweet spot

int vectorSize = 100000;
int queueSize = 100;
int randomizerUpperBound = 100;

int[] firstVector = new int[vectorSize];
int[] secondVector = new int[vectorSize];

Queue<int> queue = new Queue<int>(queueSize);

void InitializeVector(int[] vector)
{
    Random randomizer = new Random();
    
    for (int i = 0; i < vectorSize; i++)
    {
        vector[i] = randomizer.Next(randomizerUpperBound);
    }
}

void Producer()
{
    for (int i = 0; i < vectorSize; i++)
    {
        int product = firstVector[i] * secondVector[i];
        
        lock (queue)
        {
            while (queue.Count == queueSize)
            {
                Monitor.Wait(queue);
            }
            
            queue.Enqueue(product);
            Monitor.Pulse(queue);
        }
    }
}

void Consumer()
{
    int sum = 0;
    for (int i = 0; i < vectorSize; i++)
    {
        lock (queue)
        {
            while (queue.Count == 0)
            {
                Monitor.Wait(queue);
            }

            int receivedProduct = queue.Dequeue();
            sum += receivedProduct;
            Monitor.Pulse(queue);
        }
    }
    Console.WriteLine("Final sum: " + sum);
}

int Main()
{
    InitializeVector(firstVector);
    InitializeVector(secondVector);

    Thread producer = new Thread(Producer);
    Thread consumer = new Thread(Consumer);
    
    DateTime startTime = DateTime.Now;
    
    producer.Start();
    consumer.Start();
    
    producer.Join();
    consumer.Join();
    
    DateTime endTime = DateTime.Now;
    
    Console.WriteLine("Time elapsed: " + (endTime - startTime).TotalMilliseconds + " ms");
    
    return 0;
}

Main();
