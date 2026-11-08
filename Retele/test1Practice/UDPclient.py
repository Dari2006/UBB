import socket

c = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

ip = "127.0.0.1"
port = 8889

#c.bind((ip, port))
c.sendto("Hello World!".encode(), (ip, 8888))

data, addr= c.recvfrom(1024)
print(data.decode())

for byte in b"ok":
    print(byte)