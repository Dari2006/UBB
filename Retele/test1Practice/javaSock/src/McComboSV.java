import java.io.IOException;
import java.net.DatagramSocket;
import java.net.ServerSocket;
import java.net.Socket;

public class McComboSV {
    public static void main(String[] args){
        try(ServerSocket s = new ServerSocket(8888);
            DatagramSocket s_udp = new DatagramSocket(8888)){

            new Thread(new UDPClientHandler(s_udp)).start();

            while(true){
                Socket c = s.accept();
                new Thread(new TCPClientandler(c)).start();
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
