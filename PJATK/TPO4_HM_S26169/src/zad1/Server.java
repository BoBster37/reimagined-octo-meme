/**
 *
 *  @author Haidukou Matsvei S26169
 *
 */

package zad1;


import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.channels.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.time.LocalTime;
import java.util.*;


public class Server {
    private ServerSocketChannel serverSocketChannel = null;
    private Selector selector = null;

    boolean flague;
    Map<SocketChannel,String> clientNames = new HashMap<>();

    StringBuilder log = new StringBuilder();
    volatile boolean serverStatus;
    Map<SocketChannel,String> clientLogs = new HashMap<>();





    Server(String host,int port) {


        try {
            serverSocketChannel = ServerSocketChannel.open();
            serverSocketChannel.configureBlocking(false);
            serverSocketChannel.socket().bind(new InetSocketAddress(host,port));
            selector = Selector.open();

            serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);
            log = new StringBuilder();
        } catch (Exception exc) {
            exc.printStackTrace();
            System.exit(1);
        }

    }
    public void startServer(){

        new Thread(()-> {
            boolean serverIsRunning = true;

            while(serverIsRunning) {
                try {

                    selector.select();
                    Set<SelectionKey> keys = selector.selectedKeys();


                    Iterator<SelectionKey> iter = keys.iterator();

                    while (iter.hasNext()){

                        SelectionKey key = iter.next();
                        iter.remove();

                        if(key.isAcceptable()){

                            SocketChannel clientChannel = this.serverSocketChannel.accept();;
                            clientChannel.configureBlocking(false);
                            clientChannel.register(selector,SelectionKey.OP_READ);
                            continue;
                        }
                        if(key.isReadable()){
                            SocketChannel cc = (SocketChannel) key.channel();
                            serviceRequest(cc);
                            continue;
                        }

                    }

                }catch (Exception exc){

                }

            }

        }).start();

    }

    private static Charset charset = StandardCharsets.UTF_8;





    public String getServerLog() {

        return log.toString();
    }

    private void serviceRequest(SocketChannel socketChannel) {

        if (!socketChannel.isOpen()) return;
        StringBuilder str = new StringBuilder();
        ByteBuffer byteBuffer = ByteBuffer.allocateDirect(1024);
        byteBuffer.clear();

        try {
            for (int bytesRead = socketChannel.read(byteBuffer); bytesRead > 0; bytesRead = socketChannel.read(byteBuffer)) {
                byteBuffer.flip();
                CharBuffer charBuffer = charset.decode(byteBuffer);
                str.append(charBuffer);
            }
            handleRequest(socketChannel, str.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void handleRequest(SocketChannel socketChannel, String request) throws IOException {
        StringBuilder response = new StringBuilder();

        if (request.contains("login")) {
            String clientName = request.substring(request.indexOf(' ') + 1);
            clientNames.put(socketChannel, clientName);
            log.append(clientName + " logged in at " + LocalTime.now() + '\n');
            clientLogs.put(socketChannel, "=== " + clientName + " log start ===" + '\n' + "logged in" + '\n');
            response.append("logged in");
        } else if (request.equals("bye")) {
            String clientName = clientNames.get(socketChannel);
            log.append(clientName + " logged out at " + LocalTime.now() + '\n');
            clientLogs.put(socketChannel, clientLogs.get(socketChannel) + "logged out\n" + "=== " + clientName + " log end ===" + '\n');
            clientNames.remove(socketChannel);
            response.append("logged out");
        } else if (request.equals("bye and log transfer")) {
            String clientName = clientNames.get(socketChannel);
            clientLogs.put(socketChannel, clientLogs.get(socketChannel) + "logged out\n" + "=== " + clientName + " log end ===" + '\n');
            log.append(clientName + " logged out at " + LocalTime.now() + '\n');
            response.append(clientLogs.get(socketChannel));
            clientNames.remove(socketChannel);
        } else {
            String result = Time.passed(request.substring(0, request.indexOf(' ')), request.substring(request.indexOf(' ') + 1));
            String clientName = clientNames.get(socketChannel);
            log.append(clientName + " request at " + LocalTime.now() + ": \"" + request + "\"\n");
            clientLogs.put(socketChannel, clientLogs.get(socketChannel) + "Request: " + request + '\n' + "Result: \n" + result + '\n');
            response.append(result);
        }

        ByteBuffer out = charset.encode(response.toString());
        socketChannel.write(out);
    }

    public void stopServer() {

        serverStatus = false;

    }
}