import socket
import threading

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip = "127.0.0.1"
port = 8023
s.bind((ip, port))



def handle_client(conn, addr):
    print(f"connected {addr}")
    udpSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udpSock.bind((ip, 0))
    # trimitem la client portul pt socket ul udp
    udpSock_port = udpSock.getsockname()[1]
    print(f"sending port {udpSock_port}")
    conn.sendall(f"{str(udpSock_port)}\n".encode())

    port_client = conn.recv(1024)
    port_client = int(port_client.decode())

    udpSock.sendto("connected".encode(), (addr[0], port_client))

    conn.close()

    cuv_sv = input("first word: ")
    udpSock.sendto(cuv_sv.encode(), (addr[0], port_client))


    mes = ""
    while mes != "STOP":
        cuv_client = udpSock.recv(1024).decode()
        print(f"received {cuv_client}")

        a = cuv_sv[-2:]
        if a[0] != cuv_client[0] or a[1] != cuv_client[1]:
            mes = "STOP"
            break

        cuv_sv = input("enter word: ")
        udpSock.sendto(cuv_sv.encode(), (addr[0], port_client))

        b = cuv_client[-2:]
        if b[0] != cuv_sv[0] or b[1] != cuv_sv[1]:
            mes = "STOP"
            break


    udpSock.sendto(mes.encode(), (addr[0], port_client))
    print("STOP")
    udpSock.close()



s.listen()

while True:
    conn, addr = s.accept()
    Thread = threading.Thread(target=handle_client, args=(conn, addr))
    Thread.start()


s.close()