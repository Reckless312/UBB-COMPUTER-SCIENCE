# 5) Write an UDP broadcast application that serves as client and server at the same time.
#    The application is started with the network broadcast address (<NBCAST>) as argument in the command line.
#
# 1. Upon launching the application listens on UDP port 7777.
# 2. Every 3 seconds the application sends a UDP broadcast message to NBCAST port 7777 with the format: TIMEQUERY\0 (string)
# 3. Whenever the application receives a TIMEQUERY demand it answers to the source IP:
#     port with a string message: TIME HH:MM:SS\0 (current time) using unicast.
# 4. Every 10 seconds the application sends a UDP broadcast message to NBCAST port 7777 with the format:  DATEQUERY\0 (string)
# 5. Whenever the application receives a DATEQUERY demand it answers to the source IP:port with a string message:
#     DATE DD:MM:YYYY\0 (current date) using unicast.
# 6. The application will keep a list of peers (that answer to broadcast – IP:portno) and
#     update the information anytime a unicast message is received upon a broadcast.
# 7. When an entry in a list does not have any answer for 3 consecutive broadcasts it will be removed from the list.
# 8. The list will be displayed (ip, date, time) on the screen upon each update
#     (using a screen positioning api like conio or by erasing the screen before each update).
# 9. Every malformed request/response received will be counted and displayed at the end of a screen update.
#     You will have a list of malformed messages displayed with their source IP address.
#     The list should be limited in size and implemented as a queue.
#     Recent messages are added to the head and old messages are moving towards the tail.
import re
import socket
import threading
import datetime
from time import sleep

PORT = 7777
MAX_FAILED_ATTEMPTS = 3

peers = {}
lock = threading.Lock()

DATE_QUERY = "DATEQUERY"
TIME_QUERY = "TIMEQUERY"
BROADCAST_ADDR = "255.255.255.255"

def send_queries(socket):
    seconds_passed = 0
    while True:
        seconds_passed+=1
        if seconds_passed % 3 == 0:
            socket.sendto(TIME_QUERY.encode("utf-8"), (BROADCAST_ADDR, PORT))
            with lock:
                for peer in list(peers.keys()):
                    peers[peer][0] -= 1

        if seconds_passed % 10 == 0:
            socket.sendto(DATE_QUERY.encode("utf-8"), (BROADCAST_ADDR, PORT))
            with lock:
                for peer in list(peers.keys()):
                    peers[peer][0] -= 1
        sleep(1)

def handle_messages(socket):
    time_pattern = re.compile(r"TIME \d{2}:\d{2}:\d{2}")
    date_pattern = re.compile(r"DATE \d{2}:\d{2}:\d{4}")

    while True:
        data, addr = socket.recvfrom(250)
        data = data.decode("utf-8")
        ip = addr[0]
        if data == "TIMEQUERY":
            current_time = datetime.datetime.now().strftime("TIME %H:%M:%S")
            socket.sendto(current_time.encode("utf-8"), addr)
        elif re.match(time_pattern, data):
            with lock:
                peers[ip] = [MAX_FAILED_ATTEMPTS, data]
        elif data == "DATEQUERY":
            current_date = datetime.datetime.now().strftime("DATE %d:%m:%Y")
            socket.sendto(current_date.encode("utf-8"), addr)
        elif re.match(date_pattern, data):
            with lock:
                peers[ip] = [MAX_FAILED_ATTEMPTS, data]

def display():
    while True:
        with lock:
            if peers:
                for ip, (attempt, data) in peers.items():
                    print(f"{ip}: {data} - {attempt}")
            else:
                print("No peers")
        sleep(2)


if __name__ == '__main__':
    my_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    my_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    my_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    my_socket.bind(('0.0.0.0', PORT))
    query_thread = threading.Thread(target=send_queries, args=(my_socket,))
    display_thread = threading.Thread(target=display, args=())
    query_thread.start()
    display_thread.start()
    handle_messages(my_socket)
    query_thread.join()
    display_thread.join()
