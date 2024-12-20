package models;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Manager extends Person implements Serializable {

	private List<Project> Projects = new ArrayList<>();

	public Manager(String name, String surname, int pesel) throws Exception {
		setName(name);
		setSurname(surname);
		setPesel(pesel);
		addManager(this);
	}

	public List<Project> getProjects() {
		return Projects;
	}

	public void addProject(Project newProject) {
		if (!Projects.contains(newProject)) {
			Projects.add(newProject);
			if (newProject.getManager() != this) {
				newProject.setManager(this);
			}
		}
	}

	public void removeProject(Project project) {
		Projects.remove(project);
	}

	private static List<Manager> extent = new ArrayList<>();

	public static void setInstances(ArrayList<Manager> extent) {
		Manager.extent = extent;
	}

	public static ArrayList<Manager> getInstances() {
		return (ArrayList<Manager>) extent;
	}

	private static void addManager(Manager manager) {
		extent.add(manager);
	}

	private static void removeManager(Manager manager) {
		extent.remove(manager);
	}
}
