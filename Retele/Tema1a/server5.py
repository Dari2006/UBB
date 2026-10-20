#Un client trimite unui server un numar. Serverul va returna clientului sirul divizorilor acestui numar.

import socket

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip = "127.0.0.1"
port = 8888

server.bind((ip, port))

server.listen(5)

while(1):
    client, addr = server.accept()
    print("conmecat")

    n = int(client.recv(1024).decode())

    print(n)

    sum = 1 + n
    for i in range(2, n//2 + 1):
        sum+= i

    client.send(str(sum).encode())
    print(sum)
    client.close()

server.close()
