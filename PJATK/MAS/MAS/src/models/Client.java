package models;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

public class Client extends Person implements Serializable {

	private int clientId;
	private List<Report> reports = new ArrayList<>(); // Список отчетов

	public void addReport(Report report) {
		if (!reports.contains(report)) {
			reports.add(report);
		}
	}

	public List<Report> getReports() {
		return reports;
	}

	private static List<Client> extent = new ArrayList<>();

	private static void addClient(Client client) {
		extent.add(client);
	}

	private static void removeClient(Client client) {
		extent.remove(client);
		uniquePesels.remove(client.getPesel()); // Удаляем pesel из уникального множества
	}
}
