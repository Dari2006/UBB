import javax.xml.crypto.Data;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.charset.StandardCharsets;

public class UDPClientHandler implements Runnable{
    private DatagramSocket s;

    public UDPClientHandler(DatagramSocket s) {
        this.s = s;
    }

    @Override
    public void run() {
        handle_client();
    }

    private void handle_client(){
        try(DatagramSocket c = s){
            while(true){
                byte[] buffer = new byte[1024];

                DatagramPacket packet = new DatagramPacket(buffer, 0, buffer.length);
                c.receive(packet);
                String data = new String(packet.getData(), 0, packet.getLength());

                String mes = "mue";

                DatagramPacket p = new DatagramPacket(mes.getBytes(StandardCharsets.UTF_8), 0, mes.length(), packet.getAddress(), packet.getPort());

                c.send(p);

                System.out.println(data);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
