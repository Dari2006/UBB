#Un client trimite unui server un sir de caractere si un caracter. Serverul va returna clientului toate pozitiile pe care caracterul primit se regaseste in sir.

import socket

c = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip = "127.0.0.1"
port = 8888

c.connect((ip, port))
print("conectat")

text = input("text: ")

n = input("caracter: ")

c.send(text.encode())
print("am trim" + text)

c.send(n.encode())
print("am trim" + n)

res = (c.recv(1024).decode())
print(res)