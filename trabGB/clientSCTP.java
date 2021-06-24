import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;

import com.sun.nio.sctp.MessageInfo;
import com.sun.nio.sctp.SctpChannel;
import java.util.*;

public class SctpClient {
    static Scanner scan = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
        try {
            //Porta e IP
            System.out.print("Port: ");
            int port = Integer.parseInt(scan.nextLine()); 
            System.out.print("\nIp: ");
            String ip = scan.nextLine();
            	
            //ByteBuffer
            ByteBuffer byteBuffer = ByteBuffer.allocate(64000);
            //SCTP channel
            SctpChannel sctpChannel = SctpChannel.open(new InetSocketAddress
            (ip, port), 0, 0);
            
            System.out.println("\nStart sending messages:\n");
            while(true)
            {
            	String message = scan.nextLine();
            	MessageInfo info = MessageInfo.createOutgoing(null, 0);
            	
            	byteBuffer.put(message.getBytes());
            	byteBuffer.flip();
            	
            	sctpChannel.send(byteBuffer, info);
            	
            	byteBuffer.clear();
            }

        } catch (Exception e) {
		System.out.println("Exception 2");
            	e.printStackTrace();
        }
    }
}
