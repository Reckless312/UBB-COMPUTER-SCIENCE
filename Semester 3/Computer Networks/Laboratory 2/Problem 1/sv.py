__author__ = 'dadi'

import socket
import threading
import random
import struct
import sys
import time
import subprocess


start=1; stop=2**17-1
my_num= random.randint(start,stop)
print('Server number: ',my_num)
mylock = threading.Lock()
threads = []
client_count=0

def worker(cs):
    global mylock, my_num, client_count

    my_idcount=client_count
    print('client #',client_count,'from: ',cs.getpeername(), cs )
    message='Hello client #'+str(client_count)+' ! Send us your command to be executed!'
    cs.sendall(bytes(message,'ascii'))

    try:
        command_length = cs.recv(4)
        command_length = struct.unpack('!I', command_length)[0]
        command = cs.recv(command_length)
        output = subprocess.run(command, shell=True, capture_output=True, text=True)
        full_output = output.stdout + output.stderr
        output_length = len(full_output)
        cs.sendall(struct.pack('!I', output_length))
        cs.sendall(full_output.encode('ascii'))
        cs.sendall(struct.pack('!I', output.returncode))
    except socket.error as msg:
        print("Error:", msg.strerror)

    time.sleep(1)
    cs.close()
    print("Worker Thread ",my_idcount, " end")



if __name__=='__main__':
    try:
        rs=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        rs.bind( ('0.0.0.0',1234) )
        rs.listen(5)
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)
    while True:
        client_socket,addrc = rs.accept()
        t = threading.Thread(target=worker, args=(client_socket,) )
        threads.append(t)
        client_count+=1
        t.start()