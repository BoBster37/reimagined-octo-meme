package models;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Material implements Serializable {

	private int materialId;
	private String name;

	private double quantity;
	private String unit;

	private double cost;
	private List<ProjectMaterial> Orders = new ArrayList<>();

	public List<ProjectMaterial> getOrders() {
		return Orders;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public void addOrder(ProjectMaterial project) {
		Orders.add(project);
		if (project.getMaterial() != this) {
			project.setMaterial(this);
		}
	}

	public Material(String name, double quantity, String unit) {
		this.name = name;
		this.quantity = quantity;
		this.unit = unit;
		addMaterial(this);
	}

	private static List<Material> extent = new ArrayList<>();

	private static void addMaterial(Material Material) {
		extent.add(Material);
	}

	private static void removeMaterial(Material Material) {
		extent.remove(Material);
	}

	@Override
	public String toString() {
		return String.format("%s: %.2f %s", name, quantity, unit);
	}

	public int getMaterialId() {
		return materialId;
	}

	public void setMaterialId(int materialId) {
		this.materialId = materialId;
	}

	public double getCost() {
		return cost;
	}

	public void setCost(double cost) {
		this.cost = cost;
	}

}
