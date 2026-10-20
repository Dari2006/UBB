#Un client trimite unui server un sir de caractere si un caracter. Serverul va returna clientului toate pozitiile pe care caracterul primit se regaseste in sir.
import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

ip = "127.0.0.1"
port = 8888

s.bind((ip, port))

s.listen(5)

while(1):
    client, addr = s.accept()
    print("conectat")

    sir = client.recv(1024).decode()
    print("am primit" + sir)
    n = client.recv(1024).decode()
    print("am primit" + n)

    poz = []

    i = 0
    for c in sir:
        if c == n:
            poz.append(str(i))
        i+=1
    print(poz)
    client.send(str(poz).encode())
    client.close()

s.close()