import socket
import struct

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(('127.0.0.1',3663))

udp = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

user = input("Username = ")
passw = input("Password = ")

userLen = len(user)
passLen = len(passw)

data = struct.pack("!i",userLen)
sock.sendall(data)
sock.sendall(user.encode())
data = struct.pack("!i",passLen)
sock.sendall(data)
sock.sendall(passw.encode())

data = sock.recv(4)
status = struct.unpack("!i",data)[0]

if status >= 4000 :
    print("Access granted!")
    sock.close()
    server = ('127.0.0.1',status)
    
    n = input("N = ")
    n = int(n)
    data = struct.pack("!i",n)
    udp.sendto(data,server)
    
    for i in range(n):
        x = input(f"X{i} = ")
        x = int(x)
        data = struct.pack("!i",x)
        udp.sendto(data,server)
        
    data, addr = udp.recvfrom(4)
    min = struct.unpack("!i",data)[0]
    data, addr = udp.recvfrom(4)
    max = struct.unpack("!i",data)[0]
    
    print(f"Maxim : {max}")
    print(f"Minim : {min}")
else:
    print("Access denied")
    sock.close()