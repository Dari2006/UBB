import socket
import threading

ip = "127.0.0.1"
port = 8880

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((ip, port))
s.listen()


def handle_client(conn, addr):
    try:
        while True:
            data = conn.recv(1024)
            if(not data):
                print(f"Client {addr} disconnected")
                break
            print(data.decode())
            conn.sendall("bile".encode())
    except Exception as e:
        print(e)
    finally:
        conn.close()



while True:
    try:
        conn, addr = s.accept()
        print(addr)
    except Exception as e:
        print(e)

    thread = threading.Thread(target=handle_client, args=(conn, addr))
    thread.start()

