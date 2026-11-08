import socket
from threading import Thread

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip = "127.0.0.1"
port = 8080
s.bind((ip, port))

votes = {"pizza": 0,
         "burger": 0}



def handle_client(conn, addr):
    print(f"connected {addr}")
    udpSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udpSock.bind((ip, 0))
    #trimitem la client portul pt socket ul udp
    udpSock_port = udpSock.getsockname()[1]
    print(f"sending port {udpSock_port}")
    conn.sendall(f"{str(udpSock_port)}\n".encode())

    data, addr = udpSock.recvfrom(1024)
    choice = data.decode()
    while choice != "pizza" and choice != "burger":
        print(f"received {choice}")
        udpSock.sendto("not a valid choice".encode(), addr)
        data, addr = udpSock.recvfrom(1024)
        choice = data.decode()
    udpSock.sendto("noice".encode(), addr)
    print(f"received {choice}, noice")
    udpSock.close()
    conn.close()
    votes[choice] += 1

s.listen()
while True:
    conn, addr = s.accept()
    Thread(target=handle_client, args=(conn, addr)).start()



s.close()