using System.Net.Sockets;

namespace Laboratory_4;

public static class AsyncWay
{
    private static readonly string url = "http://demo.borland.com/testsite/stadyn_largepagewithimages.html";
    private static readonly Uri uri = new (url);
    public static string host = uri.Host;
    public static int port = 80;
    private static readonly string path = uri.AbsolutePath;

    public static Task Connect(SocketState socketState)
    {
        TaskCompletionSource<bool> tcs = new TaskCompletionSource<bool>();
        
        socketState.socket.BeginConnect(EventDriven.host, EventDriven.port, ar =>
        {
            socketState.socket.EndConnect(ar);
            tcs.SetResult(true);
        }, null);
        
        return tcs.Task;
    }

    private static Task Send(SocketState socketState, byte[] buffer)
    {
        TaskCompletionSource<bool> tcs = new TaskCompletionSource<bool>();
        
        socketState.socket.BeginSend(buffer, 0, buffer.Length, SocketFlags.None, ar =>
        {
            socketState.socket.EndSend(ar);
            tcs.SetResult(true);
        }, null);
        
        return tcs.Task;
    }

    private static Task<int> Receive(SocketState socketState)
    {
        TaskCompletionSource<int> tcs = new TaskCompletionSource<int>();
        
        socketState.socket.BeginReceive(socketState.buffer, 0, socketState.buffer.Length, SocketFlags.None, ar =>
        {
            int bytesRead = socketState.socket.EndReceive(ar);
            tcs.SetResult(bytesRead);
        }, null);
        
        return tcs.Task;
    }

    public static async Task Run(SocketState socketState)
    {
        await Connect(socketState);
        
        string request = $"GET {path} HTTP/1.1 \r\nHost: {host}\r\nConnection: close\r\n\r\n";
        byte[] requestInBytes = System.Text.Encoding.ASCII.GetBytes(request);
        
        await Send(socketState, requestInBytes);

        while (true)
        {
            int bytesReceived = await Receive(socketState);
            
            if (bytesReceived == 0)
            {
                socketState.socket.Close();
                break;
            }

            string received = System.Text.Encoding.ASCII.GetString(socketState.buffer, 0, bytesReceived);
        
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

            if (socketState.receivedBuffer.Length >= socketState.contentLength)
            {
                break;
            }
        }
        EventDriven.PrintHeadersToFile(socketState);
    }
}