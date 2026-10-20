import socket

ip = "127.0.0.1"
port = 8888

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((ip, port))

s.listen(5)

while(1):
    conn, addr = s.accept()
    print(addr)
    s1 = conn.recv(1024).decode()
    print(s1)
    s2 = conn.recv(1024).decode()
    print(s2)
    i = j = k = 0;
    res = ""

    while(i < len(s1) and j < len(s2)):
        if s1[i] < s2[j]:
            res+= s1[i]
            i+=1
        else:
            res+= s2[j]
            j+=1
        k+=1

    while(i < len(s1)):
        res+= s1[i]
        i+=1
        k+=1
    
    while(j < len(s2)):
        res+= s2[j]
        j+=1
        k+=1
    print(res)
    conn.send(res.encode())

    conn.close()
s.close()
