#Un client trimite unui server un numar. Serverul va returna clientului sirul divizorilor acestui numar.

import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip = "127.0.0.1"
port = 8888

client.connect((ip, port))
print("m am conectat")

n = input("numar: ")

client.send(str(n).encode())
print("am trim")

res = int(client.recv(1024).decode())

print(res)