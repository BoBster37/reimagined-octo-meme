
import java.util.concurrent.FutureTask;
import java.util.List;
import java.util.concurrent.Callable;

public class ClientTask extends FutureTask<String> {

    public ClientTask(Callable<String> stringCallable) {

        super(stringCallable);

    }


    public static ClientTask create(Client c, List<String> reqs, boolean showSendRes){
        Callable<String> callable = () -> {
            StringBuilder logBuilder = new StringBuilder();
            c.connect();
            c.send("login " + c.id);
            for (String request : reqs) {
                String sent = c.send(request);
                if (showSendRes) {
                    System.out.println(sent);
                }
            }
            logBuilder.append(c.send("bye and log transfer"));
            return logBuilder.toString();
        };
        return new ClientTask(callable);
    }
}
