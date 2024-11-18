import socket
import struct
import random
import threading
import statistics
import math

clients = []
lock = threading.Lock()

BROADCAST_ADDR = "255.255.255.255"

def updates(server_socket):
    global clients
    try:
        while True:
            length = struct.unpack("!I", server_socket.recv(4))[0]
            new_clients = []
            for i in range(0, length):
                new_udp_port = struct.unpack("!I", server_socket.recv(4))[0]
                new_operation = struct.unpack("!c", server_socket.recv(1))[0].decode()
                new_clients.append((new_udp_port, new_operation))
            with lock:
                clients = new_clients
    except Exception as e:
        print(e)

def do_operation(udp_socket, operator):
    port = struct.unpack("!I", udp_socket.recv(4))[0]
    length = struct.unpack("!I", udp_socket.recv(4))[0]
    numbers = []
    for i in range(0, length):
        nr = struct.unpack("!f", udp_socket.recv(4))[0]
        numbers.append(nr)
    if operator == 'm':
        result = statistics.mean(numbers)
        udp_socket.sendto(struct.pack("!f", result), (BROADCAST_ADDR, port))
    elif operator == '+':
        result = sum(numbers)
        udp_socket.sendto(struct.pack("!f", result), (BROADCAST_ADDR, port))
    elif operator == '*':
        result = math.prod(numbers)
        udp_socket.sendto(struct.pack("!f", result), (BROADCAST_ADDR, port))


if __name__ == "__main__":
    try:
        try:
            tcp_socket = socket.create_connection(("127.0.0.1", 1234))
        except (ConnectionRefusedError, ExceptionGroup) as e:
            print(e)
            exit(1)

        message = tcp_socket.recv(1024).decode()
        print(message)

        udp_port = int(input("Provide udp port: "))

        udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        udp_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        udp_socket.bind(("0.0.0.0", udp_port))

        tcp_socket.send(struct.pack("!I", udp_port))

        operations = [b'm', b'+', b'*']

        update_thread = threading.Thread(target=updates, args=(tcp_socket,))
        update_thread.start()

        while True:
            client_operator = random.choice(operations)
            tcp_socket.send(struct.pack("!c", client_operator))
            do_op_thread = threading.Thread(target=do_operation, args=(udp_socket, client_operator.decode()))
            do_op_thread.start()
            print(f"Operator: {client_operator.decode()}")
            n = random.randint(0, 5)
            numbers = []
            for i in range(0, 100):
                numbers.append(random.uniform(-100, 100))
            print(f"List: {numbers} of length: {n}")
            port = -1
            while port == -1:
                with lock:
                    for udp_p, op in clients:
                        if op == client_operator:
                            port = udp_p
                            break
            udp_socket.sendto(struct.pack("!I", len(numbers)), (BROADCAST_ADDR, udp_p))
            for number in numbers:
                udp_socket.sendto(struct.pack("f", number), (BROADCAST_ADDR, udp_p))
            result = struct.unpack("!f", udp_socket.recv(4))
            print(f"Result is: {result}")
    except Exception as e:
        print(e)
        exit(2)


