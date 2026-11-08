import javax.xml.crypto.Data;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.ServerSocket;

public class UDPServer {
    public static void main(String[] args){
        try(DatagramSocket s = new DatagramSocket(8888);
        ){
            while(true){
                byte[] buffer = new byte[1024];
                DatagramPacket packet = new DatagramPacket(buffer, buffer.length);

                s.receive(packet);

                String data = new String(packet.getData(), 0, packet.getLength());

                System.out.println("received " + data + " from " + packet.getPort());
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
