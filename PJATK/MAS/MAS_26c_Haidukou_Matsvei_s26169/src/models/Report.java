package models;

import java.io.Serializable;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Report implements Serializable {

	private int reportId;
	private String name;
	private String content;
	private LocalDateTime date;
	private Client client;
	private Project project;

	public Project getProject() {
		return project;
	}

	private Report(Client client, String name, String content, LocalDateTime date) {
		this.client = client;
		this.name = name;
		this.content = content;
		this.date = date;
	}

	public void setProject(Project project) {
		if (this.project != project) {
			this.project = project;

			if (project != null && !project.getReports().contains(this)) {
				project.addReport(this);
			}
		}
	}

	public static Report createReport(Client client, String name, String content, LocalDateTime date) throws Exception {
		if (client == null) {
			throw new Exception("The given Client does not exist!");
		}
		Report report = new Report(client, name, content, date);
		client.addReport(report);
		return report;
	}

	public int getReportId() {
		return reportId;
	}

	public String getName() {
		return name;
	}

	public String getContent() {
		return content;
	}

	public LocalDateTime getDate() {
		return date;
	}

	public Client getClient() {
		return client;
	}

	private static List<Report> extent = new ArrayList<>();

	private static void addReport(Report report) {
		extent.add(report);
	}

	private static void removeReport(Report report) {
		extent.remove(report);
	}
}