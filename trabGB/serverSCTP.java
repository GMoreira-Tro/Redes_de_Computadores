import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;

import com.sun.nio.sctp.MessageInfo;
import com.sun.nio.sctp.SctpChannel;
import com.sun.nio.sctp.SctpServerChannel;
import java.util.*;

public class SctpServer {
    static Scanner scan = new Scanner(System.in);

    public static void main(String[] args) throws IOException {
    	System.out.print("Port: ");
    	int port = Integer.parseInt(scan.nextLine());

	    	 
	SocketAddress serverSocketAddress = new InetSocketAddress(port);
	SctpServerChannel sctpServerChannel = SctpServerChannel.open();
	sctpServerChannel.bind(serverSocketAddress);
	ByteBuffer byteBuffer = ByteBuffer.allocate(64000);

	
        SctpChannel sctpChannel = sctpServerChannel.accept();
        System.out.println("\nStart receiving messages:\n");
        while (true) 
        {
            byteBuffer = ByteBuffer.allocate(64000);
            MessageInfo messageInfo = sctpChannel.receive(byteBuffer, null, null);
            System.out.println("Client from address: " + messageInfo.address());
            System.out.println(new String(byteBuffer.array(), "UTF-8"));
            
            byteBuffer.clear();
        }
    }
}
