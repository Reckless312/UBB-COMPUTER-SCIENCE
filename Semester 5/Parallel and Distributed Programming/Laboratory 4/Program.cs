using System.Net.Sockets;

namespace Laboratory_4;

public static class Program
{
    static async Task Main()
    {
        int nrRequests = 100;
        CountdownEvent done = new CountdownEvent(nrRequests);

        for (int i = 0; i < nrRequests; i++)
        {
            Socket connectionSocket =  new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            
            SocketState socketState = new SocketState(connectionSocket, done, i);
            
            connectionSocket.BeginConnect(EventDriven.host, EventDriven.port, (EventDriven.OnConnect), socketState);
        }
        
        done.Wait();

        await RunAsyncRequests(nrRequests);
    }

    public static async Task RunAsyncRequests(int nrRequests)
    {
        Task[] tasks = new Task[nrRequests];

        for (int i = 0; i < nrRequests; i++)
        {
            Socket connectionSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

            SocketState socketState = new SocketState(connectionSocket, null, i + nrRequests);

            tasks[i] = AsyncWay.Run(socketState);
        }
        
        await Task.WhenAll(tasks);
    }
}