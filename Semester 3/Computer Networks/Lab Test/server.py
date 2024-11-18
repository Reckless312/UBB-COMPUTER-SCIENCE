import socket
import threading
import struct
from time import sleep

active_clients = []

def client_behavior(client_socket, client_count, addr):
    try:
        message = "Connected to the server!"
        client_socket.sendall(message.encode())
        udp_port = struct.unpack("!I", client_socket.recv(4))[0]
        client_operator = struct.unpack("!c", client_socket.recv(1))[0].decode()
        print(f"Received from client {client_count} the udp port: {udp_port}, operator: {client_operator}")
        active_clients.append((client_socket, udp_port, client_operator, addr))
    except Exception as e:
        print(e)
        exit(2)

def check_clients():
    global active_clients
    changed_flag = False
    while True:
        for _,_, _, addr in active_clients:
            result = server_socket.connect_ex(addr)
            if result != 0:
               changed_flag = True
        if changed_flag is True:
            new_active_clients = []
            for client_socket, port, operator, addr in active_clients:
                is_open = server_socket.connect_ex(addr)
                if is_open == 0:
                    new_active_clients.append((client_socket, port, operator, addr))
        for client_socket, port, operator, addr in active_clients:
            client_socket.send(struct.pack("!I", len(active_clients)))

        sleep(10)

if __name__ == "__main__":
    try:
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind(("127.0.0.1", 1234))
        server_socket.listen(5)
        print("Server started")

        client_count = 0

        while True:
            client_socket, addr = server_socket.accept()
            client_count = client_count + 1
            print(f"Connection from client {client_count} from ip: {addr}")
            client_thread = threading.Thread(target=client_behavior, args=(client_socket, client_count, addr))
            client_thread.start()
    except Exception as e:
        print(e)
        exit(3)
