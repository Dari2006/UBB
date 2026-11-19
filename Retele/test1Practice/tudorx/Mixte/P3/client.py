import socket
import struct

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
sock.connect(('127.0.0.1',3663))

# Recv Status
data = sock.recv(4)
status = struct.unpack("!i",data)[0]

match status:
    case 200:
        # Server Case
        print("I am active 1")
        port = input("Input the port : ")
        port = int(port)
        
        udp_sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        udp_sock.bind(('127.0.0.1',port))
        
        data = struct.pack("!i",port)
        sock.sendall(data)
        
        data = sock.recv(4, socket.MSG_WAITALL)
        peer_port = struct.unpack("!i",data)[0]
                
        print(f"My port will be : {port}")
        print(f"Other port will be : {peer_port}\n")
        sock.close()
        
        server = ('127.0.0.1',peer_port)
        
        msg = "Whats your name?\n"
        ln = struct.pack("!i", len(msg))
        udp_sock.sendto(ln,server)
        udp_sock.sendto(msg.encode(),server)
        
        ln, addr = udp_sock.recvfrom(4)
        ln = struct.unpack("!i",ln)[0]
        
        name, addr = udp_sock.recvfrom(ln)
        name = name.decode()
        
        if name == 'Neo':
            msg = 'Follow the white rabbit'
        else:
            msg = 'Nice to meet you! This is Trinity'    
        
        ln = struct.pack("!i", len(msg))
        udp_sock.sendto(ln,server)
        udp_sock.sendto(msg.encode(),server)
        
        udp_sock.close()

    case 500:
        # Client Case
        print("I am active 2")
        
        port = input("Input the port : ")
        port = int(port)
        
        udp_sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        udp_sock.bind(('127.0.0.1',port))
                
        data = struct.pack("!i",port)
        sock.sendall(data)
        
        data = sock.recv(4)
        peer_port = struct.unpack("!i",data)[0]
        
        print(f"My port will be : {port}")
        print(f"Other port will be : {peer_port}\n")
        sock.close()
        # Making UDP
        
        server = ('127.0.0.1',peer_port)
        
        ln, addr = udp_sock.recvfrom(4)
        ln = struct.unpack("!i",ln)[0]
                
        msg, addr = udp_sock.recvfrom(ln)
        msg = msg.decode()
        
        name = input(msg)
        
        ln = struct.pack("!i",len(name))
        udp_sock.sendto(ln, server)
        udp_sock.sendto(name.encode(),server)
        
        ln, addr = udp_sock.recvfrom(4)
        ln = struct.unpack("!i",ln)[0]
                        
        msg, addr = udp_sock.recvfrom(ln)
        msg = msg.decode()
        
        print(msg)

    case _:
        print("Smth went worng")
        sock.close()