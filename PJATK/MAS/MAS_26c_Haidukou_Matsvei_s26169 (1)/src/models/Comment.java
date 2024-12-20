package models;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;

public class Comment {

	private String content;
	private LocalDate date;

	private Task task;
	private Contractor contractor;

	public Contractor getContractor() {
		return contractor;
	}

	public Task getTask() {
		return task;
	}

	public Comment() {
		addComment(this);
	}

	public void setTask(Task task) {
		if (this.task != task) {
			this.task = task;
			if (task != null && !task.getComments().contains(this)) {
				task.addComment(this);
			}
		}
	}

	public void setContractor(Contractor contractor) {
		if (this.contractor != contractor) {
			this.contractor = contractor;
			if (contractor != null && !contractor.getComments().contains(this)) {
				contractor.addComment(this);
			}
		}
	}

	private static List<Comment> extent = new ArrayList<>();

	public LocalDate getDate() {
		return date;
	}

	public void setDate(LocalDate date) {
		this.date = date;
	}

	private static void addComment(Comment Comment) {
		extent.add(Comment);
	}

	private static void removeComment(Comment Comment) {
		extent.remove(Comment);
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

}
