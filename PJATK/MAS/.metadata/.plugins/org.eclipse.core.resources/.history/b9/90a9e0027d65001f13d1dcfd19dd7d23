package Models;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class ProjectMaterial {

	private LocalDate orderDate;
	private Project project;
	private Material material;

	public ProjectMaterial(LocalDate orderDate) {
		this.orderDate = orderDate;
		addProjectMaterial(this);
	}

	public LocalDate getOrderDate() {
		return orderDate;
	}

	public void setOrderDate(LocalDate orderDate) {
		this.orderDate = orderDate;
	}

	public Material getMaterial() {
		return material;
	}

	public void setMaterial(Material material) {
		this.material = material;
		if (material != null && !material.getOrders().contains(this)) {
			material.addOrder(this);
		}
	}

	public Project getProject() {
		return project;
	}

	public void setProject(Project project) {
		this.project = project;
		if (project != null && !project.getMaterials().contains(this)) {
			project.addMaterial(this);
		}
	}

	private static List<ProjectMaterial> extent = new ArrayList<>();

	private static void addProjectMaterial(ProjectMaterial projectMaterial) {
		extent.add(projectMaterial);
	}

	private static void removeProjectMaterial(ProjectMaterial projectMaterial) {
		extent.remove(projectMaterial);
	}
}
