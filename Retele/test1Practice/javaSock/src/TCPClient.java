import java.io.*;
import java.net.Socket;

public class TCPClient {
    public static void main(String[] args){
        try(Socket c = new Socket("127.0.0.1", 8888)) {
            System.out.println("connected to server");
            BufferedReader in = new BufferedReader(new InputStreamReader(c.getInputStream()));

            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(c.getOutputStream()));

            String text = "sal";
            out.write(text);
            out.newLine();
            out.flush();
            String mes = in.readLine();
            System.out.println(mes);

        } catch (IOException e) {
            throw new RuntimeException(e);
        }


    }
}
