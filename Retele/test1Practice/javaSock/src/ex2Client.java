import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class ex2Client {
    public static void main(String[] args){
        try (Socket tcpSock = new Socket("127.0.0.1", 8080);
             BufferedReader in = new BufferedReader(new InputStreamReader(tcpSock.getInputStream()));
             BufferedWriter out = new BufferedWriter(new OutputStreamWriter(tcpSock.getOutputStream()));
             BufferedReader ink = new BufferedReader(new InputStreamReader(System.in));
        ){
            String udp_port_server = in.readLine();
            System.out.println("received port: " + udp_port_server);
            DatagramSocket udpSock = new DatagramSocket();



            String asd = Integer.toString(udpSock.getLocalPort());
            out.write(asd);
            out.newLine();
            out.flush();





            byte[] buffer = new byte[1024];
            String mes = "";
            while(!mes.equals("YOU WIN!")){
                DatagramPacket packet = new DatagramPacket(buffer, 0, buffer.length);
                udpSock.receive(packet);

                mes = new String(packet.getData(), 0, packet.getLength());
                System.out.println(mes);

                String guess = ink.readLine();


                byte[] bufferGuess;
                bufferGuess = guess.getBytes(StandardCharsets.UTF_8);

                InetAddress addr = InetAddress.getByName("localhost");

                DatagramPacket pToSend = new DatagramPacket(bufferGuess, 0, bufferGuess.length, addr, Integer.parseInt(udp_port_server));
                udpSock.send(pToSend);

                udpSock.receive(packet);

                mes = new String(packet.getData(), 0, packet.getLength());
                System.out.println(mes);

            }


        } catch (IOException e) {
            throw new RuntimeException(e);
        }


    }
}
