import socket
import struct
import threading
import random

threads = []
client_counter = 0
number = random.uniform(0, 100)
e = threading.Event()
e.clear()
lock = threading.Lock()
winner = (-1, -1)
clients_sockets = []

def guesser(my_socket):
    global client_counter, winner, clients_sockets
    thread_id = client_counter
    clients_sockets.append((my_socket, thread_id))
    print("Client #", thread_id, "from: ", my_socket.getpeername())
    message = "Welcome to the game guessing game!"
    my_socket.sendall(bytes(message, 'ascii'))
    guess = struct.unpack("!f",my_socket.recv(4))[0]
    lock.acquire()
    if abs(guess - number) < winner[1] or winner[1] == -1:
        winner = (thread_id, abs(guess - number))
    lock.release()


def finish():
    global winner, clients_sockets, number
    while True:
        e.wait()
        for (client, client_id) in clients_sockets:
            if client_id == winner[0]:
                client.sendall(bytes("YOU WIN!", 'ascii'))
            else:
                client.sendall(bytes("YOU LOSE!", 'ascii'))
        for thread in threads:
            thread.join()
        winner = (-1, -1)
        clients_sockets.clear()
        number = random.uniform(0, 100)



if __name__ == "__main__":

    try:
        my_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        my_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        my_socket.bind(('0.0.0.0', 1234))
        my_socket.listen(5)
    except socket.error as msg:
        print(msg)
        exit(1)

    print("Server listening on port 1234")

    announcer = threading.Thread(target=finish, daemon=True)
    announcer.start()
    my_socket.settimeout(10)

    while True:
        try:
            client_socket, addr = my_socket.accept()
            t = threading.Thread(target=guesser,args=(client_socket,))
            threads.append(t)
            client_counter += 1
            t.start()
        except socket.timeout:
            print("Socket timeout")
            e.set()
        except socket.error as msg:
            print(msg)
            exit(2)
        except KeyboardInterrupt:
            my_socket.close()