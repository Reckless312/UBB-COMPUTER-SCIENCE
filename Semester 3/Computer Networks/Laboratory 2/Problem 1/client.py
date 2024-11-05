__author__ = 'dadi'
import socket, struct, random,sys, time


if __name__ == '__main__':
    try:
        s = socket.create_connection( ('localhost',1234))
    except socket.error as msg:
        print("Error: ",msg.strerror)
        exit(-1)

    data=s.recv(1024)
    print(data.decode('ascii'))

    command = input("Enter command: ")

    try:
        s.sendall(struct.pack('!I', len(command)))
        s.sendall(command.encode('ascii'))
    except socket.error as msg:
        print("Error: ",msg.strerror)
        s.close()
        exit(-2)

    try:
        message_length = s.recv(4)
        message_length = struct.unpack('!I', message_length)[0]
        message = s.recv(message_length)
        exit_code = struct.unpack('!I', s.recv(4))[0]
        print(f"Message returned: {message.decode('ascii')}")
        print(f"Exit code: {exit_code}")
    except socket.error as msg:
        print("Error: ",msg.strerror)
        s.close()
        exit(-3)

    s.close()