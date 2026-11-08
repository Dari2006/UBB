import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;

public class UDPClient {
    public static void main(String[] args){
        try (DatagramSocket s = new DatagramSocket()){
            String mes ="pipi";

            InetAddress serverAddress = InetAddress.getByName("localhost");

            DatagramPacket pachet = new DatagramPacket(mes.getBytes(), 0, mes.getBytes().length, serverAddress, 8888);

            s.send(pachet);

            byte[] buffer = new  byte[1024];
            DatagramPacket p = new DatagramPacket(buffer, 0, buffer.length);

            s.receive(p);

            String text = new String(p.getData(), 0, p.getLength());
            System.out.println(text);


        } catch (SocketException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
