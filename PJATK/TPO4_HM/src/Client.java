

import java.io.*;
import java.nio.charset.Charset;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.nio.channels.SocketChannel;
import java.nio.CharBuffer;
import java.net.InetSocketAddress;

public class Client{

    SocketChannel socketClient;
    public String id;
    public String host;
    public int port;

    public Client() {
    }

    public final Charset charset = StandardCharsets.UTF_8;

    public Client(String host, int port, String id){
        this.id=id;
        this.port=port;
        this.host=host;
    }
    public String send(String str){
        ByteBuffer buffer = ByteBuffer.allocateDirect(str.getBytes().length);
        try {
            buffer.put(charset.encode(str));
            buffer.flip();
            socketClient.write(buffer);

        }
        catch (IOException e) {
            System.out.println(e);
        }
        ByteBuffer buffer1 = ByteBuffer.allocateDirect(1024);
        StringBuilder sbr = new StringBuilder();
        try {
            int numb;
            while(true) {
                if ((numb = socketClient.read(buffer1)) >= 1)
                    break;
            }
            while( numb > 0){
                numb = socketClient.read(buffer1);
                buffer1.flip();
                CharBuffer charBuffer = charset.decode(buffer1);

                sbr.append(charBuffer);
            }

        }catch (IOException e){
            System.out.println(e);
        }

        return sbr.toString();
    }
    public void connect(){
        try {
            socketClient = SocketChannel.open();
            socketClient.connect(new InetSocketAddress(host,port));
            socketClient.configureBlocking(false);

            while (true) {
                if (socketClient.finishConnect())

                    break;
            }
        }catch(IOException e){
            System.out.println(e);
        }
    }




}