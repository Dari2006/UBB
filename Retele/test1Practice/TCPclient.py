import socket
import sys

c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

c.connect(('127.0.0.1', 8888))

c.send("mesaj".encode())

data = c.recv(1024)
print(data.decode())
