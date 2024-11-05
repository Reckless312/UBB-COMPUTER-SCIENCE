import socket
import struct

if __name__ == '__main__':
    try:
        my_socket = socket.create_connection(('localhost', 1234))
    except socket.error as msg:
        print("Error: ", msg.strerror)
        exit(1)

    data = my_socket.recv(1024)
    print(data.decode("ascii"))

    file_path = input("Insert file path: ")

    try:
        my_socket.sendall(file_path.encode('ascii'))
    except socket.error as msg:
        print("Error: ", msg.strerror)
        my_socket.close()
        exit(2)

    file_length = struct.unpack('!I', my_socket.recv(4))[0]

    if file_length != -1:
        file_name = file_path.split('/')[-1]
        with open(file_name + "-copy.txt", 'wb') as f:
            try:
                content = my_socket.recv(file_length)
                f.write(content)
            except socket.error as msg:
                print("Error: ", msg.strerror)
                my_socket.close()
                exit(3)

    print("File has been copied successfully! Closing the connection...")

    my_socket.close()