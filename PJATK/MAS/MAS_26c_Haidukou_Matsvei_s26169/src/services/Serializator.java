package services;

import models.*;

import java.io.IOException;
import java.util.ArrayList;
import java.io.*;

public class Serializator {

	public static void save() {
		saveData(Manager.getInstances(), "Manager");
		saveData(Task.getInstances(), "Task");
		saveData(Project.getInstances(), "Project");

		;
	}

	private static <T extends Serializable> void saveData(ArrayList<T> instanceToSave, String name) {

		try (ObjectOutputStream out = new ObjectOutputStream(
				new FileOutputStream("src/resources/" + name + ".ser"))) {
			out.writeObject(instanceToSave);
			System.out.println("Serialized data is saved in " + "src/main/resources/" + name + ".ser");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void readData() {
		readData(Manager.class);
		readData(Task.class);
		readData(Project.class);

	}

	private static <T extends Serializable> void readData(Class<T> clazz) {
		String filePath = "src/resources/" + clazz.getSimpleName() + ".ser";
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
			clazz.getMethod("setInstances", ArrayList.class).invoke(null, instances);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
