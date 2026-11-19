import socket
import struct

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(('127.0.0.1',3663))

udp = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

n = input("N = ")
n = int(n)

# Send N
data = struct.pack("!i",n)
sock.sendall(data)

# Connect to UDP
data = sock.recv(4)
port = struct.unpack("!i",data)[0]

print(port)

if port >= 4000:
    sock.close()
    udpServer = ('127.0.0.1',port)
    
    for i in range(n):
        op = input("Operation(+,-,*,/) : ")
        a = input("Number 1 : ")
        b = input("Number 2 : ")
        
        a = int(a)
        b = int(b)
        
        if op == '+':
            op = 1
        elif op == '-':
            op = 2
        elif op == '*':
            op = 3
        elif op == '/':
            op = 4
        else:
            op = 0
        
        data = struct.pack("!iii",op,a,b)
        udp.sendto(data,udpServer)
        
        print("Trimis")
        
        data, addr = udp.recvfrom(8)
        stat,rez = struct.unpack("!ii",data)[0],struct.unpack("!ii",data)[1]
        
        if stat == 1:
            print("Error with operation")
        elif stat == 2:
            print("Divizion by 0 error")
        else:
            print(f"Result : {rez}")
            
    udp.close()
else:
    sock.close()