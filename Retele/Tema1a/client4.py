import socket

ip = "127.0.0.1"
port = 8888

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

client.connect((ip, port))
print("conectat")
text1 = input("'text: ")
text2 = input("'text: ")
client.send(text1.encode())
print("am trimis 1")
client.send(text2.encode())
print("am trim 2")
res=client.recv(1024).decode()

print(res)