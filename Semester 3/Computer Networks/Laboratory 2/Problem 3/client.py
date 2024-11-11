import socket
import struct

if __name__ == "__main__":
    my_socket = socket.create_connection(("localhost", 1234))
    data = my_socket.recv(1024)
    print(data.decode("ascii"))

    number = float (input("Choose a number: "))

    my_socket.sendall(struct.pack("!f", number))

    message = my_socket.recv(1024)
    print(message.decode("ascii"))

    my_socket.close()
