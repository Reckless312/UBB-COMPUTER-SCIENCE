using System.Net.Sockets;

namespace Laboratory_4;

public class SocketState(Socket socket, CountdownEvent? countdownEvent, int id)
{
    public Socket socket = socket;
    public CountdownEvent? CountdownEvent = countdownEvent;
    public int id = id;
    
    public byte[] buffer = new byte[1024];
    public Dictionary<string, string> headers = new();
    
    public string receivedBuffer = "";
    
    public bool foundAllHeaders;
    public int contentLength = -1;
}

public static class EventDriven
{
    private static readonly string url = "http://demo.borland.com/testsite/stadyn_largepagewithimages.html";
    private static readonly Uri uri = new (url);
    public static string host = uri.Host;
    public static int port = 80;
    private static readonly string path = uri.AbsolutePath;

    public static void OnConnect(IAsyncResult ar)
    {
        if (ar.AsyncState == null)
        {
            return;
        }
        
        SocketState socketState = (SocketState)ar.AsyncState;
        socketState.socket.EndConnect(ar);

        string request = $"GET {path} HTTP/1.1 \r\nHost: {host}\r\nConnection: close\r\n\r\n";
        byte[] requestInBytes = System.Text.Encoding.ASCII.GetBytes(request);
        
        socketState.socket.BeginSend(requestInBytes, 0, requestInBytes.Length, SocketFlags.None,  OnSend, socketState);
    }

    private static void OnSend(IAsyncResult ar)
    {
        if (ar.AsyncState == null)
        {
            return;
        }
        
        SocketState socketState = (SocketState)ar.AsyncState;
        socketState.socket.EndSend(ar);
        
        socketState.socket.BeginReceive(socketState.buffer, 0, socketState.buffer.Length, SocketFlags.None, OnReceive,  socketState);
    }
    
    private static void OnReceive(IAsyncResult ar)
    {
        if (ar.AsyncState == null)
        {
            return;
        }
        
        SocketState socketState = (SocketState)ar.AsyncState;
        int bytesRead = socketState.socket.EndReceive(ar);
        
        if (bytesRead == 0)
        {
            socketState.socket.Close();
            PrintHeadersToFile(socketState);
            return;
        }

        string received = System.Text.Encoding.ASCII.GetString(socketState.buffer, 0, bytesRead);
        
        socketState.receivedBuffer += received;
        
        if (!socketState.foundAllHeaders)
        {
            int headerEndIndex = socketState.receivedBuffer.IndexOf("\r\n\r\n", StringComparison.Ordinal);

            if (headerEndIndex >= 0)
            {
                string headerLines = socketState.receivedBuffer.Substring(0, headerEndIndex);
                socketState.receivedBuffer = socketState.receivedBuffer.Substring(headerEndIndex + 4);

                foreach (string line in headerLines.Split("\r\n"))
                {
                    int separatorIndex = line.IndexOf(':');

                    if (separatorIndex > 0)
                    {
                        string headerName = line.Substring(0, separatorIndex).Trim();
                        string headerValue = line.Substring(separatorIndex + 1).Trim();
                        
                        socketState.headers[headerName] = headerValue;
                    }
                }
                socketState.foundAllHeaders = true;
                
                socketState.contentLength = int.Parse(socketState.headers["Content-Length"]);
            }
        }

        if (socketState.contentLength == -1)
        {
            socketState.socket.BeginReceive(socketState.buffer, 0, socketState.buffer.Length, SocketFlags.None, OnReceive, socketState);
            return;
        }

        if (socketState.receivedBuffer.Length < socketState.contentLength)
        {
            socketState.socket.BeginReceive(socketState.buffer, 0, socketState.buffer.Length, SocketFlags.None, OnReceive, socketState);
            return;
        }
        
        EventDriven.PrintHeadersToFile(socketState);
    }

    public static void PrintHeadersToFile(SocketState socketState)
    {
        FileStream fs = new FileStream($"headers_{socketState.id}.txt", FileMode.Create);
        StreamWriter sw = new StreamWriter(fs);
        
        foreach (KeyValuePair<string, string> header in socketState.headers)
        {
            sw.WriteLine($"{header.Key}: {header.Value}");
        }

        sw.Close();
        
        Console.WriteLine($"Headers saved to file headers_{socketState.id}.txt");
        
        socketState.CountdownEvent?.Signal();
    }
}