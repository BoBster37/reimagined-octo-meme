package models;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Milestone {

	private String description;
	private LocalDate dateOfAchievement;
	private Project project;

	public Project getProject() {
		return project;
	}

	public Milestone() {
		addMilestone(this);
	}

	public void setProject(Project project) {
		if (this.project != project) {
			this.project = project;

			if (project != null && !project.getMilestones().contains(this)) {
				project.addMilestone(this);
			}
		}
	}

	private static List<Milestone> extent = new ArrayList<>();

	private static void addMilestone(Milestone Milestone) {
		extent.add(Milestone);
	}

	private static void removeMilestone(Milestone Milestone) {
		extent.remove(Milestone);
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	public LocalDate getDateOfAchievement() {
		return dateOfAchievement;
	}

	public void setDateOfAchievement(LocalDate dateOfAchievement) {
		this.dateOfAchievement = dateOfAchievement;
	}

}
