import java.io.*;
import java.net.*;
import java.nio.Buffer;
import java.nio.charset.StandardCharsets;

public class ex3Client {
    public static void main(String[] args){
        try(Socket s = new Socket(InetAddress.getByName("localhost"), 8080);
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
            BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
            BufferedReader ink = new BufferedReader((new InputStreamReader(System.in)))
        ){
            String udp_sock_sv = in.readLine();
            System.out.println(udp_sock_sv);

            DatagramSocket udpSock = new DatagramSocket();
            String mes = "not a valid choice";

            while(mes.equals("not a valid choice")){
                String choice = ink.readLine();

                DatagramPacket p = new DatagramPacket(choice.getBytes(StandardCharsets.UTF_8), 0, choice.length(), InetAddress.ofLiteral("127.0.0.1"), Integer.valueOf(udp_sock_sv));
                System.out.println("sending " + choice);
                udpSock.send(p);

                byte[] buffer = new byte[1024];
                DatagramPacket p2 = new DatagramPacket(buffer, 0, buffer.length);
                udpSock.receive(p2);

                mes = new String(p2.getData(), 0, p2.getLength());
                System.out.println(mes);
            }


        } catch (UnknownHostException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
