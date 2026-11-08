import java.io.*;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class ex1Client {
    public static void main(String[] args){
        try(Socket s = new Socket("127.0.0.1", 8888);
            BufferedReader in = new BufferedReader(new InputStreamReader(s.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(s.getOutputStream()));
        ){

            BufferedReader ink = new BufferedReader(new InputStreamReader(System.in));
            String n = ink.readLine();


            String op = ink.readLine();
            out.write(n  + " "  + op);
            out.newLine();
            out.flush();

            String nr = in.readLine();
            System.out.println(nr);

        } catch (UnknownHostException e) {
            throw new RuntimeException(e);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
