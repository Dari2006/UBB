import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPConcurent {

    public static void main(String[] args){
        try(ServerSocket s = new ServerSocket(8888)){

            while(true){
                Socket c = s.accept();

                new Thread(new TCPClientandler(c)).start();
            }

        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
