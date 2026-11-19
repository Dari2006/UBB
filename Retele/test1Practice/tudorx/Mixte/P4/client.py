import socket
import struct

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(('127.0.0.1',3663))

udp = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

n = input("N = ")
n = int(n)

data = struct.pack("!i",n)
sock.sendall(data)

# Get port
port = sock.recv(4,socket.MSG_WAITALL)
port = struct.unpack("!i",port)[0]

server = ('127.0.0.1',port)

sock.close()

while(1):
    print("Make guess : ")
    x = input('x = ')
    x = int(x)
    
    data = struct.pack("!i",x)
    udp.sendto(data,server)
    
    data, addr = udp.recvfrom(8)
    status = struct.unpack("!ii",data)[0]    
    hint = struct.unpack("!ii",data)[1]
    
    match status:
        case 0:
            print(f"Hint : {hint}")
        case 1:
            print("Bomb defused")
            udp.close()
            exit(0)
        case 2:
            print("Out of guesses")
            udp.close()
            exit(0)
        case 3:
            print("Out of time")
            udp.close()
            exit(0)
