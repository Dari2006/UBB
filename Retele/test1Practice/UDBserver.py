import socket
import sys

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

ip = "127.0.0.1"
port = 8888

s.bind((ip, port))

while True:
    data, addr = s.recvfrom(1024)
    data = data.decode()
    print(data)
    print(addr)

    s.sendto("ok".encode(), addr)

