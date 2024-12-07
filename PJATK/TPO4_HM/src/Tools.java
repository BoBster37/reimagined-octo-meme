/**
 *
 *  @author Haidukou Matsvei S26169
 *
 */


import org.yaml.snakeyaml.Yaml;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.List;
import java.util.Map;

public class Tools {
    public static Options createOptionsFromYaml(String fileName) throws FileNotFoundException {
    Yaml yaml = new Yaml();

        InputStream input = new FileInputStream(new File(fileName));
        Map<String, Object> object = (Map<String, Object>) yaml.load(input);
        Map<String, List<String>> map = (Map<String, List<String>>) object.get("clientsMap");
        String host = (String) object.get("host");
        int port = (int) object.get("port");
        boolean concurMode = (boolean) object.get("concurMode");
        boolean showSendRes = (boolean) object.get("showSendRes");
        Options opt = new Options(host,port,concurMode,showSendRes,map);
        return opt;
    }
}
