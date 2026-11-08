import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class TCPClientandler implements Runnable{
    Socket s;

    public TCPClientandler(Socket s) {
        this.s = s;
    }

    @Override
    public void run() {
        handle_client();
    }

    private void handle_client(){
        System.out.println("connected");
        try(
                Socket c = s;
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(c.getOutputStream()));
            BufferedReader in = new BufferedReader(new InputStreamReader(c.getInputStream()));
        )
        {
            String text = in.readLine();
            System.out.println("received " + text + "from " + c.getPort());

            out.write("ms de mes fra");
            out.newLine();
            out.flush();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
