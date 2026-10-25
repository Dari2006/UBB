package Config;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

public class Config {
    private final Properties properties;

    public Config(){
        properties = new Properties();

        try(InputStream in = getClass().getClassLoader().getResourceAsStream("config.properties")){
            properties.load(in);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public Properties getProperties() {
        return properties;
    }
}
