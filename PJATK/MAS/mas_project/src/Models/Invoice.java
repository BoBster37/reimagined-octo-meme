package Models;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Invoice {

	private int invoiceId;
	private double amount;
	private LocalDateTime dateOfIssue;
	private LocalDateTime dateOfPayment;
	private Project project;

	public Project getProject() {
		return project;
	}

	public Invoice() {
		addInvoice(this);
	}

	public void setProject(Project project) {
		if (this.project != project) {
			this.project = project;
			if (project != null && !project.getInvoices().contains(this)) {
				project.addInvoices(this);
			}
		}
	}

	private static List<Invoice> extent = new ArrayList<>();

	private static void addInvoice(Invoice Invoice) {
		extent.add(Invoice);
	}

	private static void removeInvoice(Invoice Invoice) {
		extent.remove(Invoice);
	}

}
