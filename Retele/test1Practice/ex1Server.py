import socket
import threading

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
ip = "127.0.0.1"
port = 8888

s.bind((ip, port))



def handle_client(conn, addr):
    try:
        data = conn.recv(1024)
        data = data.decode()
        print(data)
        n, op = data.split()
        n = int(n)

        print(f"received {n} from {addr}")

        print(f"received {op} from {addr}")
        nr = -1
        if op == "SUM":
            nr = 0
            for i in range(1, n  +1):
                nr += i
        elif op == "FACT":
            nr = 1
            for i in range(1, n +1):
                nr = nr * i


        conn.sendall(str(nr).encode())
        print(f"sent {nr} to {addr}")
    except Exception as ex:
        print(f"exception occured {ex}")
    finally:
        conn.close()


s.listen()
while True:
    conn, addr = s.accept()
    print(f"Connected by {addr}")
    threading.Thread(target=handle_client, args=(conn, addr)).start()

s.close()
