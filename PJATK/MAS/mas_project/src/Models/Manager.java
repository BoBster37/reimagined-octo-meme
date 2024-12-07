package Models;

import java.util.ArrayList;
import java.util.List;

public class Manager extends Person {

    private List<Project> Projects = new ArrayList<>();

    public Manager(String name, String surname, int pesel) throws Exception {
        super(name, surname, pesel);
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

    private static void addManager(Manager manager) {
        extent.add(manager);
    }

    private static void removeManager(Manager manager) {
        extent.remove(manager);
    }
}
