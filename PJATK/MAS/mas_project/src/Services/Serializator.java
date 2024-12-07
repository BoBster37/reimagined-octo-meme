package Services;


import Models.*;

import java.io.IOException;
import java.util.ArrayList;
import java.io.*;

public class Serializator {

    public static void save() {
        //saveData(Client.getInstances(),"Client");
        ;
    }

//    public static  void saveGroups() {
//
//        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("src/main/resources/GroupClass.ser"))) {
//            out.writeObject(GroupClass.getInstances());
//            System.out.println("Serialized data is saved in " +"src/main/resources/"+ GroupClass.getInstances().getClass().getSimpleName() + ".ser");
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
    private static <T extends Serializable> void saveData(ArrayList<T> instanceToSave,String name) {

        try (ObjectOutputStream out = new ObjectOutputStream(new FileOutputStream("src/main/resources/"+name + ".ser"))) {
            out.writeObject(instanceToSave);
            System.out.println("Serialized data is saved in " +"src/main/resources/"+ name + ".ser");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void readData() {
     //   readData(Client.class);
       
    }

    private static <T extends Serializable> void readData(Class<T> clazz) {
        String filePath = "src/main/resources/"+clazz.getSimpleName() + ".ser";
        try (ObjectInputStream in = new ObjectInputStream(new FileInputStream(filePath))) {
            ArrayList<T> deserializedList = (ArrayList<T>) in.readObject();
            invokeSetInstancesMethod(clazz, deserializedList);
            System.out.println("Deserialized data from " + filePath);
        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    private static <T extends Serializable> void invokeSetInstancesMethod(Class<T> clazz, ArrayList<T> instances) {
        try {
            // Используем рефлексию для вызова статического метода setInstances(ArrayList<T> instances)
            clazz.getMethod("setInstances", ArrayList.class).invoke(null, instances);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
