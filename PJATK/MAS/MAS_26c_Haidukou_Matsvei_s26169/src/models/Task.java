package models;

import java.io.Serializable;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Task implements Serializable {

	private String name;
	private String description;

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	private LocalDate StartDate;
	private LocalDate EndDate;

	private enum TaskStatus {
		NOTSTARTED, INPROGRESS, COMPLETED;
	}

	private Project project;
	private List<Comment> Comments = new ArrayList<>();

	public List<Comment> getComments() {
		return Comments;
	}

	public Project getProject() {
		return project;
	}

	public Task() {
		addTask(this);
	}

	public void setProject(Project project) {
		if (this.project != project) {
			this.project = project;
			if (project != null && !project.getTasks().contains(this)) {
				project.addTask(this);
			}
		}
	}

	public void addComment(Comment comment) {
		if (!Comments.contains(comment)) {
			Comments.add(comment);

			if (comment.getTask() != this) {
				comment.setTask(this);
			}
		}
	}

	public static void setInstances(ArrayList<Task> extent) {
		Task.extent = extent;
	}

	public static ArrayList<Task> getInstances() {
		return (ArrayList<Task>) extent;
	}

	private static List<Task> extent = new ArrayList<>();

	private static void addTask(Task Task) {
		extent.add(Task);
	}

	private static void removeTask(Task Task) {
		extent.remove(Task);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

}
