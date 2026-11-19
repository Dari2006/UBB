import socket
import sys
try:
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
except socket.error as err:
    print(err)
    sys.exit(1)


ip = "127.0.0.1"
port = 8888

s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

s.bind((ip, port))

s.listen(5)

while True:
    conn, addr = s.accept()
    print(f"conencted to: {addr}")
    try:
        data = conn.recv(1024).decode()
        if not data:
            conn.close()
            continue
        print(data)
        conn.sendall("ok".encode())
    except Exception as e:
        print(e)
    finally:
        conn.close()


