package models;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Contract {

	private int contractId;
	private String type;
	private String content;
	private LocalDateTime dateSigned;
	private Project project;

	public void setDateSigned(LocalDateTime dateSigned) {
		this.dateSigned = dateSigned;
	}

	public void setContractId(int contractId) {
		this.contractId = contractId;
	}

	public int getContractId() {
		return contractId;
	}

	public Project getProject() {
		return project;
	}

	public LocalDateTime getDateSigned() {
		return dateSigned;
	}

	public Contract() {
		addContract(this);
	}

	public void setProject(Project project) {
		if (this.project != project) {
			this.project = project;
			if (project != null && !project.getContracts().contains(this)) {
				project.addContract(this);
			}
		}
	}

	public String getType() {
		return type;
	}

	public void setType(String type) {
		this.type = type;
	}
	
	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}


	private static List<Contract> extent = new ArrayList<>();

	private static void addContract(Contract Contract) {
		extent.add(Contract);
	}

	private static void removeContract(Contract Contract) {
		extent.remove(Contract);
	}

}
