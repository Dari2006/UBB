void main() {
    try(Socket s = new Socket(InetAddress.getByName("localhost"), 8023);
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
        BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
        BufferedReader ink = new BufferedReader((new InputStreamReader(System.in)))
    ){

        String udp_sock_sv = in.readLine();
        System.out.println(udp_sock_sv);

        DatagramSocket udpSock = new DatagramSocket();

        String port = String.valueOf(udpSock.getLocalPort());
        out.write(port);
        out.newLine();
        out.flush();

        int portUDP = Integer.valueOf(udp_sock_sv);

        byte[] buffer = new byte[1024];
        DatagramPacket p = new DatagramPacket(buffer, 0, buffer.length);
        udpSock.receive(p);
        String cuv = new String(p.getData(), 0, p.getLength());
        System.out.println("received: " + cuv);

        //p = new DatagramPacket(buffer, 0, buffer.length);
        //udpSock.receive(p);
        //cuv = new String(p.getData(), 0, p.getLength());
        //System.out.println("received frist word: " + cuv);



        cuv = "";
        while(!cuv.equals("STOP")){


            p = new DatagramPacket(buffer, 0, buffer.length);
            udpSock.receive(p);
            cuv = new String(p.getData(), 0, p.getLength());
            if(!cuv.equals("STOP"))
                System.out.println("received word: " + cuv);
            else{
                System.out.println(cuv);
                break;
            }

            System.out.println("enter word: ");
            cuv = ink.readLine();
            p = new DatagramPacket(cuv.getBytes(StandardCharsets.UTF_8), 0, cuv.length(), InetAddress.getByName("localhost"),
                        portUDP);
            udpSock.send(p);


        }

    udpSock.close();

    } catch (UnknownHostException e) {
        throw new RuntimeException(e);
    } catch (IOException e) {
        throw new RuntimeException(e);
    }


}
