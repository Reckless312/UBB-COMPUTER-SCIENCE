import socket
import multiprocessing as mp
import os
import struct
client_count = 0

def client(client_socket):
    print("Client #", client_count, "from: ", client_socket.getpeername())
    message = 'Hello client #' + str(client_count) + '! Send us your file path to find'
    client_socket.sendall(bytes(message, 'ascii'))
    file_path = client_socket.recv(1024)
    if os.path.isfile(file_path) is False:
        try:
            client_socket.sendall(struct.pack('!I', -1))
        except socket.error as msg:
            print(msg)
            client_socket.close()
            exit(1)
    else:
        file_length = os.path.getsize(file_path)
        try:
            client_socket.sendall(struct.pack('!I', file_length))
            with open(file_path, 'rb') as file:
                file_content = file.read()
                client_socket.sendall(file_content)
        except socket.error as msg:
            print(msg)
            client_socket.close()
            exit(2)
    client_socket.close()

if __name__ == '__main__':
    try:
        new_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        new_socket.bind(('0.0.0.0', 1234))
        new_socket.listen(5)
    except socket.error as msg:
        print(msg.sterror)
        exit(1)

    print("Server listening on port 1234")
    client_processes = []

    try:
        while True:
            client_socket, client_address = new_socket.accept()
            client_process = mp.Process(target=client, args=(client_socket,))
            client_count+=1
            client_process.start()
            client_processes.append(client_process)
    except KeyboardInterrupt:
        for client_process in client_processes:
            client_process.join()

    new_socket.close()
