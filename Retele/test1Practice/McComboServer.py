import socket
import threading


def handle_client_tcp(conn, addr):
    try:
        while True:
            data = conn.recv(1024)
            if not data:
                print(f"Client {addr} disconnected")
                break
            data = data.decode()
            print(f"received {data} from {addr}")
            conn.send("Hello World".encode())
    except Exception as e:
        print(e)
    finally:
        conn.close()


def handle_client_udp():
    try:
        while True:
            data, addr = s_udp.recvfrom(1024)

            print(f"received {data.decode()} from {addr}")
            s_udp.sendto("hi, udp".encode(), addr)
    except Exception as e:
        print(e)
    finally:
        s_udp.close()

s_tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s_udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

ip = "127.0.0.1"
port = 8888

s_tcp.bind((ip, port))
s_udp.bind((ip, port))

s_tcp.listen()

threading.Thread(target=handle_client_udp, args=()).start()
while True:
    conn, addr = s_tcp.accept()
    threading.Thread(target=handle_client_tcp, args=(conn, addr)).start()

