import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPserver {
    public static void main(String[] args){
        try (ServerSocket s = new ServerSocket(8888)){
            System.out.println("server pornit");

            while(true){
                try(Socket c = s.accept();
                BufferedReader in = new BufferedReader(new InputStreamReader(c.getInputStream()));
                BufferedWriter out = new BufferedWriter(new OutputStreamWriter(c.getOutputStream()));) {
                    System.out.println("client conectat");
                    String text = in.readLine();
                    System.out.println("mesaj de la client: " + text);
                    out.write("sal fin sv");
                    out.newLine();
                    out.flush();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();

        }


    }

}
