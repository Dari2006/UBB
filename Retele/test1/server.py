import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip = "127.0.0.1"
port = 6767

s.bind((ip, port))



def handle_client(conn, addr):
    print("Connected by", addr)



s.listen()

while True:
    conn, addr = s.accept()
    thread = threading.Thread(target=handle_client, args=(conn, addr))
    thread.start()


s.close()


