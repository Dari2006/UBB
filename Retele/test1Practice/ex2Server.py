import socket
import threading
import random

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ip = "127.0.0.1"
port = 8080
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, True)
s.bind((ip, port))

def handle_client(conn, addr):
    n = random.randint(1, 101)
    udpSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udpSock.bind((ip, 0))
    udp_port = udpSock.getsockname()[1]
    print(f"sending {udp_port}")
    conn.send(f"{str(udp_port)}\n".encode())

    udp_port_client = conn.recv(1024).decode()
    print(f"received {udp_port_client}")

    udp_port_client = int(udp_port_client)

    guess = -1
    while guess != n:
        mes = "Enter guess: "
        udpSock.sendto("Enter guess:".encode(), (ip, udp_port_client))

        data, addr = udpSock.recvfrom(1024)
        try:
            guess = int(data.decode())
            print(f"guess: {guess}")

            if(guess < n):
                udpSock.sendto("Higher".encode(), (ip, udp_port_client))
            elif(guess > n):
                udpSock.sendto("Lower".encode(), (ip, udp_port_client))
        except Exception as e:
            print(e)

    udpSock.sendto("YOU WIN!".encode(), (ip, udp_port_client))
    udpSock.close()


s.listen()
while True:
    conn, addr = s.accept()
    print(conn, addr)
    thread = threading.Thread(target=handle_client, args=(conn, addr)).start()

    conn.close()
