package models;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public class Project implements Serializable {

	private int projectId;
	private String name;
	private double budget;
	private double budgetRemaining;

	private String description;

	private String location;

	private List<Milestone> Milestones = new ArrayList<>();
	private List<Invoice> Invoices = new ArrayList<>();
	private List<Task> Tasks = new ArrayList<>();
	private List<Contract> Contracts = new ArrayList<>();
	private List<ProjectMaterial> Orders = new ArrayList<>();
	private List<Report> Reports = new ArrayList<>();
	private Manager manager;

	private enum ProjectStatus {
		NEW, INPROGRESS, ONHOLD, COMPLETED, CANCELED;
	}

	public Manager getManager() {
		return manager;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public List<Report> getReports() {
		return Reports;
	}

	public List<ProjectMaterial> getMaterials() {
		return Orders;
	}

	public List<Contract> getContracts() {
		return Contracts;
	}

	public List<Task> getTasks() {
		return Tasks;
	}

	public List<Invoice> getInvoices() {
		return Invoices;
	}

	public List<Milestone> getMilestones() {
		return Milestones;
	}

	public Project() {
		addProject(this);
	}

	public void addMilestone(Milestone milestone) {
		if (!Milestones.contains(milestone)) {
			Milestones.add(milestone);

			if (milestone.getProject() != this) {
				milestone.setProject(this);
			}
		}
	}

	public void addReport(Report report) {
		if (!Reports.contains(report)) {
			Reports.add(report);

			if (report.getProject() != this) {
				report.setProject(this);
			}
		}
	}

	public void addMaterial(ProjectMaterial material) {
		Orders.add(material);
		if (material.getProject() != this) {
			material.setProject(this);
		}
	}

	public void addContract(Contract contract) {
		if (!Contracts.contains(contract)) {
			Contracts.add(contract);
			Collections.sort(Contracts, Comparator.comparing(Contract::getDateSigned));
			if (contract.getProject() != this) {
				contract.setProject(this);
			}
		}

	}

	public void setDescription(String description) {
		this.description = description;
	}

	public void addTask(Task task) {
		if (!Tasks.contains(task)) {
			Tasks.add(task);
			if (task.getProject() != this) {
				task.setProject(this);
			}
		}
	}

	public void addInvoices(Invoice invoice) {
		if (!Invoices.contains(invoice)) {
			Invoices.add(invoice);
			if (invoice.getProject() != this) {
				invoice.setProject(this);
			}
		}
	}

	public void setManager(Manager manager) {
		if (this.manager != manager) {
			if (this.manager != null) {
				this.manager.removeProject(this);
			}
			this.manager = manager;

			if (manager != null) {
				manager.addProject(this);
			}

		}
	}

	private static List<Project> extent = new ArrayList<>();

	public static ArrayList<Project> getInstances() {
		return (ArrayList<Project>) extent;
	}

	public static void setInstances(ArrayList<Project> extent) {
		Project.extent = extent;
	}

	private static void addProject(Project Project) {
		extent.add(Project);
	}

	private static void removeProject(Project Project) {
		extent.remove(Project);
	}

	public double getBudgetRemaining() {
		return budgetRemaining;
	}

	public void setBudgetRemaining(double budgetRemaining) {
		this.budgetRemaining = budgetRemaining;
	}

	public String getDetails() {
		return description;
	}

	public int getProjectId() {
		return projectId;
	}

	public void setProjectId(int projectId) {
		this.projectId = projectId;
	}

	public double getBudget() {
		return budget;
	}

	public void setBudget(double budget) {
		this.budget = budget;
	}

	public String getLocation() {
		return location;
	}

	public void setLocation(String location) {
		this.location = location;
	}

}
